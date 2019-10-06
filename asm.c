/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 11:50:59 by vurrigon          #+#    #+#             */
/*   Updated: 2019/10/06 17:17:44 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/corewar.h"


int		check_extension(char *filename)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_strsplit(filename, '.');
	while (tmp[i + 1])
		i++;
	if (!ft_strcmp(tmp[i], "s"))
		return (1);
	else if (!ft_strcmp(tmp[i], "cor"))
		return (-1);
	return (0);
}

void	add_instruction(t_player *player, t_instruction *instr)
{
	t_instruction *tmp;

	tmp = player->instr;
	if (!tmp)
		player->instr = instr;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = instr;
	}
}

// ВОТ ОТСЮДА НАЧИНАЮ МЕНЯТЬ НЕ ТРОГАЯ ТОКЕНИЗАЦИЮ
void	search_instruction(t_player *player, char *line)
{
	int		len_token;

	len_token = 0;
	while (line[player->num_col])
	{
		if (is_comment(line[player->num_col]))
			return ;
		if (line[player->num_col] == SEPARATOR_CHAR) // INSTRACTIONS
			player->num_col++;
		else if (is_whitespace(line[player->num_col]))
			skip_tab_space(player, line, SKIP_QUOTE);
		else
		{
			len_token = search_length_token(player, line);
			if (is_label(line, player, len_token))
				handling_label(player, line, len_token - 1);
			else if ((is_instruction(player, line)))
				;
//			else
//				error_file("Syntax error", player->num_col, player->num_row);
			player->num_col += len_token;
		}
	}
	if (len_token > 0 && player->last_instr)
	{
		player->last_instr->start_bit = player->current_bit;
		printf("[%s] - %d\n", player->last_instr->instr, player->last_instr->start_bit);
		player->current_bit += player->last_instr->size_exec_code;
	}
}

void	printf_struct(t_player *player)
{
	t_label *tmp;
	t_instruction *tmp_i;

	tmp = player->labels;
	tmp_i = player->instr;

	while (tmp_i)
	{
		if (tmp_i->label)
			printf("link with label - %s:\n", tmp_i->label->l_name);
		printf("instr - %s\n", tmp_i->instr);
		tmp_i = tmp_i->next;
	}
	printf("\nLABLES\n\n");
	while (tmp)
	{
		printf("lable - %s link with instr - %s\n", tmp->l_name, tmp->instr->instr);
		tmp = tmp->next;
	}

}

void	reading_body_champion(int fd, t_player *player)
{
	char	*line;

	while (get_next_line(fd, &line) == 1)
	{
		player->num_row++;
		search_instruction(player, line);
		player->num_col = 0;
		free(line);
	}
}

int		create_file_bytecode(t_player *player)
{
	char	*new_name;
	int		fd;

	new_name = ft_strstr(player->file_name, ".s");
	new_name = ft_strsub(player->file_name, 0, new_name - player->file_name);
	new_name = ft_strjoin(new_name, ".cor");
	fd = open(new_name, O_WRONLY);
    if (fd == -1)
    {
        open(new_name, O_CREAT);
        fd = open(new_name, O_WRONLY);
    }
    player->file_name = new_name;
	return (fd);
}

void	int32_to_bytecode(unsigned char *bytes, int value, int size)
{
	int	i;

	i = 0;
	//printf("value = %x, size = %d\n", value, size);
	//printf("BYTES [%p]\n", bytes);
	while (size)
	{
		bytes[size - 1] = (value >> i) & 0xFF;
		i += 8;
		size--;
	}
}

int		get_code_types(t_tokens **args)
{
	int	i;
	unsigned char	result;
	int				offset;

	offset = 64;
	result = 0;
	i = 0;
	while (args[i])
	{
		if (args[i]->type == DIRECT_LABEL)
			args[i]->type = T_DIR;
		else if (args[i]->type == INDIRECT_LABEL)
			args[i]->type = T_IND;
		result += offset * args[i]->type;
		offset /= 4;
		i++;
	}
	//printf("CODE TYPE %x\n", result);
	return (result);
}

void	translate_to_bytecode_arg(t_tokens **args, unsigned char **bytes, int code_op)
{
	int	i;

	i = 0;
	while (args[i])
	{
		//printf("ARG %s\n", args[i]->data);
		if (args[i]->type == T_REG || args[i]->type == T_IND || args[i]->type == INDIRECT_LABEL)
		{
			int32_to_bytecode((*bytes), args[i]->data_int, 1);
			(*bytes)++;
		}
		else if (args[i]->type == T_DIR || args[i]->type == DIRECT_LABEL)
		{
			int32_to_bytecode(*bytes, args[i]->data_int, g_ins[code_op - 1].t_dir_size);
			*bytes += g_ins[code_op - 1].t_dir_size;
		}
		else
			error("Invalid type of argument");
		i++;
	}
}

void	translate_to_bytecode_ins(t_instruction	*instr, unsigned char **bytes)
{
	while (instr)
	{
		int32_to_bytecode(*bytes, instr->code_op, 1);
		(*bytes)++;
		if (g_ins[instr->code_op - 1].arg_type_code)
		{
			int32_to_bytecode(*bytes, get_code_types(instr->args), 1);
			(*bytes)++;
			translate_to_bytecode_arg(instr->args, bytes, instr->code_op);
		}
		else
			translate_to_bytecode_arg(instr->args, bytes, instr->code_op);
		instr = instr->next;
	}
}

void	translate_to_bytecode(t_player *player)
{
	int		new_fd;
	int		length;
	unsigned char	*bytes;
	unsigned char	*begin;

	new_fd = create_file_bytecode(player);
	length = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4 +
												player->sum_size_exec_code;
	if (!(bytes = (unsigned char *)malloc((length + 1) * sizeof(unsigned char))))
		error("Failed to initialize byte array");
	begin = bytes;
	int32_to_bytecode(bytes, COREWAR_EXEC_MAGIC, 4);
	bytes += 4;
	ft_memcpy(bytes, player->name, ft_strlen(player->name));
	bytes += PROG_NAME_LENGTH;
	int32_to_bytecode(bytes, 0, 4);
	bytes += 4;
	int32_to_bytecode(bytes, player->sum_size_exec_code, 4);
	bytes += 4;
	ft_memcpy(bytes, player->comment, ft_strlen(player->comment));
	bytes += COMMENT_LENGTH;
	int32_to_bytecode(bytes, 0, 4);
	bytes += 4;
	translate_to_bytecode_ins(player->instr, &bytes);
	write(new_fd, begin, length);
	free(begin);
}

void	calculate_size_exec_code(t_player *player)
{
	t_instruction	*instr;
	int				size;

	size = 0;
	instr = player->instr;
	while (instr)
	{
		size += instr->size_exec_code;
		instr = instr->next;
	}
	player->sum_size_exec_code = size;
}

void	assemble(int fd, char *file_name)
{
	t_player *header;

	if (!(header = init_player(fd, file_name)))
		error("Error allocating header memory");
	if (!check_name_comment(fd, header))
		error("Error reading of name or comment");
	reading_body_champion(fd, header);
	check_arg_is_digit(header);
	calculate_size_exec_code(header);
	translate_to_bytecode(header);
	ft_putstr("Writing output program to ");
	ft_putendl(header->file_name);
	while (header->instr)
	{
		printf("instr = %s\n", header->instr->instr);
		//printf("size %d\n", header->instr->size_exec_code);
		printf("start %d\n", header->instr->start_bit);
		printf("###############################\n");
		header->instr = header->instr->next;
	}
}

int	main(int argc, char **argv)
{
	int	fd;
	int	exten;

	if (argc != 2)
		error("Usage: ./asm <sourcefile.s> | <sourcefile.cor>");
	else if (!(exten = check_extension(argv[1])))
		error("Invalid file extension");
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			error("File name missing.");
		if (exten == 1)
			assemble(fd, argv[1]);
	}
	return (0);
}
