/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_arg_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestella <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:59:54 by aestella          #+#    #+#             */
/*   Updated: 2019/10/22 19:00:06 by aestella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_func_pointer g_funk_array[5] = {
	check_reg,
	check_dir,
	check_dir_label,
	check_indir,
	check_indir_label
};

void	check_reg(t_tokens *token, char *name, US ignored, t_player *pl)
{
	ignored += 0;
	token->data = name;
	token->size = 1;
	token->col = pl->num_col;
	token->row = pl->num_row;
}

void	check_dir(t_tokens *token, char *name, US instr, t_player *pl)
{
	token->data = name;
	token->size = g_ins[instr - 1].t_dir_size;
	token->col = pl->num_col;
	token->row = pl->num_row;
}

void	check_dir_label(t_tokens *token, char *name, US instr, t_player *pl)
{
	token->data = name;
	token->size = g_ins[instr - 1].t_dir_size;
	token->col = pl->num_col;
	token->row = pl->num_row;
}

void	check_indir(t_tokens *token, char *name, US ignored, t_player *pl)
{
	ignored += 0;
	token->data = name;
	token->size = 2;
	token->col = pl->num_col;
	token->row = pl->num_row;
}

void	check_indir_label(t_tokens *token, char *name, US ignored, t_player *pl)
{
	ignored += 0;
	token->data = name;
	token->size = 2;
	token->col = pl->num_col;
	token->row = pl->num_row;
}
