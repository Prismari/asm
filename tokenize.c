/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 17:16:41 by vurrigon          #+#    #+#             */
/*   Updated: 2019/10/19 15:34:06 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "corewar.h"
#include "./includes/corewar.h" // TODO: удалить - это читсо для силайна


int search_length_token(t_player *player, char	*line)
{
    int	i;
    int len;

    i = player->num_col;
    len = 0;
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
    return (len);
}

void	check_op(t_player *player, char *op)
{
    int	i;

    i = 0;
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
    else if (ft_isdigit(token[0]) || (token[0] == '-' && ft_isdigit(token[1])))
        return (INDIRECT);
	else
		return (0);
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
//    if (line[player->num_col + len] == LABEL_CHAR)
//        check_label(player, ft_strsub(line, player->num_col, len));
  //  else
    	if (!player->last_instr)
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