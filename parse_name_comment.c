/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name_comment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 17:14:23 by vurrigon          #+#    #+#             */
/*   Updated: 2019/10/06 11:33:38 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/corewar.h"

void	write_name(t_player *player, char *line)
{
	char	*tmp;
	int		length;

	if (skip_tab_space(player, line, STOP_BEFORE_QUOTE) != QUOTE)
		error_file("Syntax error", player->num_col + 1, player->num_row);
	player->num_col++;
	tmp = ft_strchr(&line[player->num_col], '"');
	if (!tmp)
		error_file("Invalid name", player->num_col + 1, player->num_row);
	length = tmp - &line[player->num_col];
	if (length > PROG_NAME_LENGTH)
 		error("Champion name too long (Max length 128)");
 	tmp = &line[player->num_col];
 	player->num_col += length + 1;
 	if (skip_tab_space(player, line, STOP_BEFORE_QUOTE) && !is_comment(line[player->num_col]))
 		error_file("Syntax error", player->num_col + 1, player->num_row);
 	player->name = ft_strndup(tmp, length);
	line += player->num_col;
 	//printf("[%s]\n", player->name);
}

void	write_comment(t_player *player, char *line)
{
	char	*tmp;
	int		length;

	if (skip_tab_space(player, line, STOP_BEFORE_QUOTE) != QUOTE)
		error_file("Syntax error", player->num_col + 1, player->num_row);
	player->num_col++;
	tmp = ft_strchr(&line[player->num_col], '"');
	if (!tmp)
		error_file("Invalid comment", player->num_col + 1, player->num_row);
	length = tmp - &line[player->num_col];
	if (length > COMMENT_LENGTH)
		error("Champion comment too long (Max length 2048)");
 	tmp = &line[player->num_col];
 	player->num_col += length + 1;
 	if (skip_tab_space(player, line, STOP_BEFORE_QUOTE) && !is_comment(line[player->num_col]))
 		error_file("Syntax error", player->num_col + 1, player->num_row);
 	player->comment = ft_strndup(tmp, length);
	line += player->num_col;
 	//printf("[%s]\n", player->comment);
}

int		check_command(char *line, t_player *player)
{	
	if (!ft_strncmp(line, NAME_CMD_STRING, OFFSET_CMD_NAME) &&
	(line[OFFSET_CMD_NAME] == '\t' || line[OFFSET_CMD_NAME] == ' ' || line[OFFSET_CMD_NAME] == '"'))
	{
		player->num_col += OFFSET_CMD_NAME;
		write_name(player, line);
		return (1);
	}
	else if (!ft_strncmp(line, COMMENT_CMD_STRING, OFFSET_CMD_COMMENT) &&
	(line[OFFSET_CMD_COMMENT] == '\t' || line[OFFSET_CMD_COMMENT] == ' ' || line[OFFSET_CMD_COMMENT] == '"'))
	{
		player->num_col += OFFSET_CMD_COMMENT;
		write_comment(player, line);
		return (1);
	}
	return (0);

}

void	search_comment_name(t_player *player, char *line)
{
	while (line[player->num_col])
	{
		if (is_comment(line[player->num_col]))
			return ;
		else if (line[player->num_col] == '.')
		{
			if (!check_command(&line[player->num_col], player))
				error_file("Unknown command", player->num_col + 1, player->num_row);
			return ;
		}
		else if (line[player->num_col] != ' ' && line[player->num_col] != '\t')
			error_file("Syntax error", player->num_col + 1, player->num_row);		
		player->num_col++;
	}
}

int		check_name_comment(int fd, t_player *player)
{
	char	*line;

	while (get_next_line(fd, &line) == 1)
	{
		player->num_row++;
		search_comment_name(player, line);
		if (player->comment && player->name)
		{
			player->num_col = 0;
			free(line);
			return (1);
		}
		player->num_col = 0;
		free(line);
	}
	return (0);
}
