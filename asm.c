/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 11:50:59 by vurrigon          #+#    #+#             */
/*   Updated: 2019/10/19 15:27:52 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "corewar.h"
#include "./includes/corewar.h" // TODO: удалить - это читсо для силайна

int		check_extension(char *filename)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_strsplit(filename, '.');
	while (tmp[i + 1])
		i++;
	if (!ft_strcmp(tmp[i], "s"))
	{
		free_split(tmp);
		return (1);
	}
	else if (!ft_strcmp(tmp[i], "cor"))
	{
		free_split(tmp);
		return (-1);
	}
	free_split(tmp);
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

void	search_instruction(t_player *player, char *line)
{
	int		len_token;

	len_token = 0;
	del_comment(line);
	while (line[player->num_col])
	{
		if (is_comment(line[player->num_col]))
			return ;
		if (line[player->num_col] == SEPARATOR_CHAR)
			player->num_col++;
		else if (is_whitespace(line[player->num_col]))
			skip_tab_space(player, line, SKIP_QUOTE);
		else
		{
			len_token = search_length_token(player, line);
			if (is_label(line, player, len_token))
				handling_label(player, line, len_token - 1);
			else if (!(is_instruction(player, line)))
				error_file("Syntax error", player->num_row, player->num_col + 1);
		}
	}
	if (len_token > 0 && player->last_instr && !player->flag_lable_exist)
	{
		player->last_instr->start_bit = player->current_bit;
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
	char	*tmp;
	int		fd;

	new_name = ft_strstr(player->file_name, ".s");
	tmp = ft_strsub(player->file_name, 0, new_name - player->file_name);
	new_name = ft_strjoin(tmp, ".cor");
	fd = open(new_name, O_WRONLY);
    if (fd == -1)
    {
        open(new_name, O_CREAT);
        fd = open(new_name, O_WRONLY);
    }
    player->file_name = new_name;
    free(tmp);
	return (fd);
}

void	int32_to_bytecode(unsigned char *bytes, int value, int size)
{
	int	i;

	i = 0;
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
		if (args[i]->type == INDIRECT)
			result += offset * (args[i]->type - 1);
		else
			result += offset * args[i]->type;
		offset /= 4;
		i++;
	}
	return (result);
}

void	translate_to_bytecode_arg(t_tokens **args, unsigned char **bytes, int code_op)
{
	int	i;

	i = 0;
	while (args[i])
	{
		//printf("ARG %s\n", args[i]->data);
		if (args[i]->type == T_REG)
		{
			int32_to_bytecode((*bytes), args[i]->data_int, 1);
			(*bytes)++;
		}
		else if (args[i]->type == T_IND || args[i]->type == INDIRECT_LABEL)
		{
			int32_to_bytecode((*bytes), args[i]->data_int, 2);
			*bytes += 2;
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

void	translate_to_bytecode(t_player *player, int new_fd)
{
	int		length;
	unsigned char	*bytes;
	unsigned char	*begin;

	length = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4 +
												player->sum_size_exec_code;
	if (!(bytes = (unsigned char *)malloc((length + 1) * sizeof(unsigned char))))
		error("Failed to initialize byte array");
	ft_bzero(bytes, length);
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

void	check_comment(int fd, int lpos, char *buf)
{
	while (lpos-- > 0)
	{
		lseek(fd, lpos, SEEK_SET);
		read(fd, buf, 1);
		if (*buf == COMMENT_CHAR || *buf == ALT_COMMENT_CHAR)
		{
			lseek(fd, --lpos, SEEK_SET);
			read(fd, buf, 1);
			if (*buf == '\n')
				return;
			else
				error("Syntax error - no newline at the end");
		}
		if (*buf == '\n')
			error("Syntax error - no newline at the end");
	}
}

void 	check_end_file(t_player *player)
{
	char buf[2];
	int lpos;
	int end;

	end = lseek(player->fd, 0, SEEK_END);
	lpos = end;
	//printf("%d\n", lpos);
	while (lpos-- > 0 )
	{
		lseek(player->fd, lpos, SEEK_SET);
		read(player->fd, buf, 1);
//		printf("%s\n", buf);
		if (is_whitespace(*buf))
			continue;
		else if(*buf == '\n')
			return;
		else
		{
			check_comment(player->fd, lpos, buf);
			return;
		}
	}
//	error("Syntax error - no newline at the end");
}

void	assemble(int fd, char *file_name)
{
	t_player *header;
	int			new_fd;

	if (!(header = init_player(fd, file_name)))
		error("Error allocating header memory");
	if (!check_name_comment(fd, header))
		error("Error reading of name or comment");
	reading_body_champion(fd, header);
	calculate_size_exec_code(header);
	check_arg_is_digit(header);
	check_end_file(header);
	new_fd = create_file_bytecode(header);
	translate_to_bytecode(header, new_fd);
	ft_putstr("Writing output program to ");
	ft_putendl(header->file_name);
//	printf("name = [%s]\n", header->name);
//	printf("comment = [%s]\n", header->comment);
//int i;
//	  while (header->instr)
//	  {
//	  	i = 0;
//	  	printf("instr = %s\nargs -> ", header->instr->instr);
//	  	while (header->instr->args[i])
//	  		printf(" %d ", header->instr->args[i++]->data_int);
////	  	printf("size %d\n", header->instr->size_exec_code);
////	  	printf("start %d\n", header->instr->start_bit);
//	  	printf("\n###############################\n");
//	  	header->instr = header->instr->next;
//	  }
	free_asm(header);
	// int i;
	//  while (header->instr)
	//  {
	//  	i = 0;
	//  	while (header->instr->args[i])
	//  	{
	//  		printf("%d\n", header->minstr->args[i++]->data_int);
	//  	}
	//  	header->instr = header->instr->next;
	//  }
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
