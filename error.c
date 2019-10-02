/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:53:24 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/19 17:24:41 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/corewar.h"

void	error(char *str)
{
	ft_putendl(str);
	exit(1);
}

void	error_file(char *str, int col, int row)
{
	ft_printf("[%d:%d] %s\n", row, col, str);
	exit(1);
}

void 	error_name(char *str, char *name)
{
	ft_printf("%s %s\n", str, name);
	exit(1);
}

void	error_type(char *instr, t_type type, int arg)
{
	if (type == INDIRECT || type == INDIRECT_LABEL)
		ft_printf("Invalid parameter %d type indirect for instruction %s \n", arg, instr);
	else if (type == DIRECT || type == DIRECT_LABEL)
		ft_printf("Invalid parameter %d type direct for instruction %s \n", arg, instr);
	else if (type == REGISTER)
		ft_printf("Invalid parameter %d type register for instruction %s \n", arg, instr);
	else
		ft_printf("Invalid parameter %d for instruction %s \n", arg, instr);
	exit(1);
}