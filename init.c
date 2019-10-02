/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 12:03:05 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/25 13:20:10 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/corewar.h"

t_player	*init_player(int fd)
{
	t_player *player;

	if (!(player = malloc(sizeof(t_player))))
		return (NULL);
	player->name = NULL;
	player->comment = NULL;
	player->fd = fd;
	player->num_row = 0;
	player->num_col = 0;
	player->instr = NULL;
	player->last_instr = NULL;
	player->sum_size_exec_code = 0;
	player->current_bit = 0;
	player->last_label = NULL;
	player->labels = NULL;
	player->flag_lable_exist = NULL;
	return (player);
}

t_instruction	*init_instr(char *instr)
{
	t_instruction *op;
	if (!(op = malloc(sizeof(t_instruction))))
		return (NULL);
	op->instr = instr;
	op->code_op = 0;
	op->label = NULL;
	op->tokens = NULL;
	op->size_exec_code = 0;
	op->next = NULL;
	return (op);
}

t_label	*init_lable(char *label)
{
	t_label *new;
	if (!(new = malloc(sizeof(t_label))))
		return (NULL);
	new->instr = NULL;
	new->l_name = label;
	new->next = NULL;
	new->prev = NULL;
	new->sum_size_exec_code = 0;
	return (new);
}

t_tokens		*init_tokens(t_type type)
{
	t_tokens *token;
	if (!(token = malloc(sizeof(t_tokens))))
		return (NULL);
	token->type = type;
	token->data = NULL;
	token->size = -1;
	token->data_int = -1;
	return (token);
}
