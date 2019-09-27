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

int 	is_label(char *line, t_player *player, int len)
{
	len--;
	if (line[player->num_col + len] == LABEL_CHAR)
		return (1);
	return (0);
}

int 	is_instruction(t_player *player, char *line)
{
	int len_token;
	int i;

	i = 0;
	len_token = search_length_token(player, line);
	while (i++ < 16)
		if (!ft_strcmp(ft_strsub(line, player->num_col, len_token), g_ins[i - 1].name))
			break ;
	if (i < 16)
		return (len_token);
	return (0);
}


// ВОТ ОТСЮДА НАЧИНАЮ МЕНЯТЬ НЕ ТРОГАЯ ТОКЕНИЗАЦИЮ
void	search_instruction(t_player *player, char *line)
{
	int		len_token;

	while (line[player->num_col])
	{
		if (is_comment(line[player->num_col]))
			return ;
		if (line[player->num_col] == SEPARATOR_CHAR) // INSTRACTIONS
			player->num_col++;
		else if (is_whitespace(line[player->num_col]))
		{
			printf("SKIP\n");
			skip_tab_space(player, line, SKIP_QUOTE);
		}
		else
		{
			len_token = search_length_token(player, line);
			if (is_label(line, player, len_token))
			{
				printf("is_lable\n");
				handling_label(player, line, len_token - 1);
				printf("TOKEN [%s]\n", ft_strsub(line, player->num_col, len_token));
			}
			else if ((is_instruction(player, line)))
			{
				printf("is_instr\n");
				printf("TOKEN [%s]\n", ft_strsub(line, player->num_col, len_token));
			}

//			    //
			//handling_token(player, len_token - 1, line);                       //      TOKEN
			player->num_col += len_token;                                           //
		}                                                                           //
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
	}
	return (0);
}
