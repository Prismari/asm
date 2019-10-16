/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name_comment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 17:14:23 by vurrigon          #+#    #+#             */
/*   Updated: 2019/10/08 12:51:15 by vurrigon         ###   ########.fr       */
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
	{
		player->is_finished_name = 0;
		player->name = ft_strdup(&line[player->num_col]);
		player->name = ft_strjoin(player->name, "\n");
		return ;
	}
	length = tmp - &line[player->num_col];
	if (length > PROG_NAME_LENGTH)
 		error("Champion name too long (Max length 128)");
 	tmp = &line[player->num_col];
 	player->num_col += length + 1;
 	if (skip_tab_space(player, line, STOP_BEFORE_QUOTE) && !is_comment(line[player->num_col]))
 		error_file("Syntax error", player->num_col + 1, player->num_row);
 	player->name = ft_strndup(tmp, length);
	line += player->num_col;
// 	printf("[%s]\n", player->name);
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
	{
		player->is_finished_com = 0;
		player->comment = ft_strdup(&line[player->num_col]);
		player->comment = ft_strjoin(player->comment, "\n");
		return ;
	}
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
	int	len_name;
	int len_comment;

	len_name = ft_strlen(NAME_CMD_STRING);
	len_comment = ft_strlen(COMMENT_CMD_STRING);
	if (!ft_strncmp(&(line[player->num_col]), NAME_CMD_STRING, len_name) &&
	(line[len_name + player->num_col] == '\t' || line[len_name + player->num_col] == ' ' || line[len_name + player->num_col] == '"'))
	{
		player->num_col += len_name;
		write_name(player, line);
		return (1);
	}
	else if (!ft_strncmp(&(line[player->num_col]), COMMENT_CMD_STRING, len_comment) &&
	(line[len_comment + player->num_col] == '\t' || line[len_comment + player->num_col] == ' ' || line[len_comment + player->num_col] == '"'))
	{
		player->num_col += len_comment;
		write_comment(player, line);
		return (1);
	}
	return (0);
}

void check_after_quote(t_player *player, char *line)
{
	int i;

	i = 1;
	while (line[i])
	{
		if (is_whitespace(line[i]))
		{
			i++;
			continue;
		}
		if (is_comment(line[i]))
			break;
		if (line[i] != '\0')
			error_file("Syntax error", player->num_col + i, player->num_row);
		i++;
	}
}

void search_continue(t_player *player, char *line)
{
	char *quote;

	quote = ft_strchr(line, '"');
	if (!player->is_finished_com && !quote)
	{
		player->comment = ft_strjoin(player->comment, line);
		player->comment = ft_strjoin(player->comment, "\n");
	}
	else if (!player->is_finished_name && !quote)
	{
		player->name = ft_strjoin(player->name, line);
		player->name = ft_strjoin(player->name, "\n");
	}
	else if (!player->is_finished_com)
	{
		player->comment = ft_strjoin(player->comment, ft_strsub(line, 0, quote - line));
		player->is_finished_com = 1;
	}
	else if (!player->is_finished_name)
	{
		player->name = ft_strjoin(player->name, ft_strsub(line, 0, quote - line));
		player->is_finished_name = 1;
	}
	if (quote)
	{
		player->num_col += quote - line;
		check_after_quote(player, quote);
	}
}

void	search_comment_name(t_player *player, char *line)
{
	while (line[player->num_col])
	{
		if (is_whitespace(*line))
			skip_tab_space(player, line, SKIP_QUOTE);
		if (is_comment(line[player->num_col]))
			return ;
		else if (line[player->num_col] == '.')
		{
			if (!check_command(line, player))
				error_file("Unknown command", player->num_col + 1, player->num_row);
			return ;
		}
		else if (line[player->num_col] != ' ' && line[player->num_col] != '\t')
			error_file("Syntax error", player->num_col + 1, player->num_row);		
		player->num_col++;
	}
}

void	check_len_name_com(t_player *player)
{
	if (ft_strlen(player->name) > PROG_NAME_LENGTH)
		error("Champion name too long (Max length 128)");
	else if (ft_strlen(player->comment) > COMMENT_LENGTH)
		error("Champion comment too long (Max length 2048)");
}

int		check_name_comment(int fd, t_player *player)
{
	char	*line;

	while (get_next_line(fd, &line) == 1)
	{
		player->num_row++;
		if (!player->is_finished_name || !player->is_finished_com)
			search_continue(player, line);
		else
		{
			search_comment_name(player, line);
			if (player->comment && player->name && player->is_finished_com && player->is_finished_name)
			{
				player->num_col = 0;
				check_len_name_com(player);
				free(line);
				return (1);
			}
		}
		player->num_col = 0;
		free(line);
	}
	return (0);
}
