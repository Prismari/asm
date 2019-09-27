/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 11:50:59 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/25 15:25:45 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/corewar.h"
#include <stdio.h>

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

int search_length_token(t_player *player, char	*line)
{
	int	i;
	int len;

	i = player->num_col;
	len = 0;
	//printf("line [%s]\n", &line[player->num_col]);
	while (line[i] && line[i] != SEPARATOR_CHAR && !is_whitespace(line[i]) &&
			!is_comment(line[i]))
	{
		//printf("OTLADKA == {%c}\n", line[i]);
		if ((line[i] == LABEL_CHAR && line[i - 1] != DIRECT_CHAR))
		{
			len++;
			break ;
		}
		else if (line[i] == DIRECT_CHAR && len)
			break ;
		i++;
		len++;
	}
	//printf("itog == [%s]\n", &line[i]);
	return (len);
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

void	check_label(t_player *player, char *label)
{
	printf("label [%s]\n", label);
	int	i;
	t_instruction	*new_instr;

	i = 0;
	while(label[i])
		if (!ft_strchr(LABEL_CHARS, label[i++]))
			error_file("Invalid label name", player->num_col + 1, player->num_row);
	new_instr = init_instr(label);
	add_instruction(player, new_instr);
	player->last_instr = new_instr;
}

void	check_op(t_player *player, char *op)
{
	int	i;

	i = 0;
	printf("OP == %s\n", op);
	while (i++ < 16)
		if (!ft_strcmp(op, g_ins[i - 1].name))
		{
			player->last_instr->code_op = g_ins[i - 1].code;
			player->last_instr->count_args = g_ins[i - 1].args_num;
			printf("COUNT == %d\n", player->last_instr->count_args);
			printf("CODE == %d\n", i);
			return ;
		}
	error_file("Invalid instruction", player->num_col + 1, player->num_row);
}

t_type	know_type(char *token)
{
	if (token[0] == 'r')
		return (REGISTER);
	else if (token[0] == DIRECT_CHAR && token[1] == LABEL_CHAR)
		return (DIRECT_LABEL);
	else if (token[0] == DIRECT_CHAR)
		return (DIRECT);
	else if (token[0] == LABEL_CHAR)
		return (INDIRECT_LABEL);
	else
		return (INDIRECT);
}

void	check_arg(char *token, t_player *player)
{
	t_type	type;

	type = know_type(token);
	if (type == REGISTER && token++)
	{
		printf("ttt = %s\n", token);
		if (ft_strlen(token) > 2 || (token[0] == '0' && token[1] == '0') ||
			(token[0] == '0' && token[1] == '\0'))
			error_file("Invalid REGISTER", player->num_col + 1, player->num_row);

	}

	printf("type = %u\n", type);
}

void	handling_token(t_player *player, int len, char *line)
{
	if (line[player->num_col + len] == LABEL_CHAR)
		check_label(player, ft_strsub(line, player->num_col, len));
	else if (!player->last_instr)
	{
		player->last_instr = init_instr(NULL);
		add_instruction(player, player->last_instr);
		check_op(player, ft_strsub(line, player->num_col, len + 1));

	}
	else if (!player->last_instr->code_op)
		check_op(player, ft_strsub(line, player->num_col, len + 1));
	else
	{
		player->last_instr->count_args--;
		check_arg(ft_strsub(line, player->num_col, len + 1), player);
		if (!player->last_instr->count_args)
			player->last_instr = NULL;
	}
}

void	search_instruction(t_player *player, char *line)
{
	int		len_token;

	while (line[player->num_col])
	{
		if (is_comment(line[player->num_col]))
			return ;
		if (line[player->num_col] == SEPARATOR_CHAR)
			player->num_col++;
		else if (is_whitespace(line[player->num_col]))
		{
			printf("SKIP\n");
			skip_tab_space(player, line, SKIP_QUOTE);
		}
		else
		{
			len_token = search_length_token(player, line);
			//printf("LEN == %d\n", len_token);
			printf("TOKEN [%s]\n", ft_strsub(line, player->num_col, len_token));
			handling_token(player, len_token - 1, line);
			player->num_col += len_token;
			
		}
		printf("###########################\n");
	}
	if (player->last_instr && player->last_instr->count_args)
		error_file("Invalid count args", player->num_col + 1, player->num_row);
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

void	assemble(int fd)
{
	t_player *header;

	if (!(header = init_player()))
		error("Error allocating header memory");
	if (!check_name_comment(fd, header))
		error("Error reading of name or comment");
	reading_body_champion(fd, header);
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
			assemble(fd);
//		else
//			disassemble(fd);
	}
	return (0);
}
