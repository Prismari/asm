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
			else
				error_file("Syntax error", player->num_col, player->num_row);
			player->num_col += len_token;
		}
	}
	if (len_token > 0 && player->last_instr)
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

void	assemble(int fd)
{
	t_player *header;

	if (!(header = init_player(fd)))
		error("Error allocating header memory");
	if (!check_name_comment(fd, header))
		error("Error reading of name or comment");
	reading_body_champion(fd, header);
	//printf_struct(header);
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
	}
	return (0);
}
