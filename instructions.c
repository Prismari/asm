//
// Created by Asafoetida Estella on 2019-09-27.
//

#include "includes/corewar.h"
extern  	t_func_pointer f_funk_array[5];

void	link_lable_to_instr(t_instruction *instr, t_label *lable)
{
	t_label *tmp;

	lable->instr = instr;
	instr->label = lable;
	tmp = lable;
	while (tmp->prev && tmp->prev->instr == NULL)
	{
//		printf("lable %s links to %s\n", tmp->l_name, instr->instr);
		tmp = tmp->prev;
		tmp->instr = instr;
	}
}

int 	is_instruction(t_player *player, char *line)
{
	int len_token;
	int i;
	char *instr;

	i = 0;
	len_token = search_length_token(player, line);
	instr = ft_strsub(line, player->num_col, len_token);
	while (i++ < 16)
		if (!ft_strcmp(instr, g_ins[i - 1].name))
			break ;
	if (i <= 16)
	{
		player->num_col += len_token;
		check_instruction(player, instr, &(line[player->num_col]), i);
		return (len_token);
	}

	return (0);
}

void	ft_link_new_instr(t_instruction *new_instr, t_player *player)
{
	if (player->instr == NULL)
	{
		player->instr = new_instr;
		player->last_instr = new_instr;
	}
	else
	{
		player->last_instr->next = new_instr;
		player->last_instr = player->last_instr->next;
	}
	if (player->flag_lable_exist)
	{
		link_lable_to_instr(new_instr, player->flag_lable_exist);
		player->flag_lable_exist = NULL;
	}
}

void	check_instruction(t_player *player, char *instr, char *line, int i)
{
	t_instruction *new_instr;

	if (!(new_instr = init_instr(instr))
		|| !(new_instr->args = (t_tokens**)malloc(sizeof(t_tokens*) * (g_ins[i - 1].args_num + 1) )))
		error("Memory allocation error");
	ft_link_new_instr(new_instr, player);
	player->last_instr->code_op = g_ins[i - 1].code;
	player->last_instr->count_args = g_ins[i - 1].args_num;
	player->last_instr->args[g_ins[i - 1].args_num] = NULL;
	check_arguments(player, line);
}

void	del_comment(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != '#')
		i++;
	line[i] = '\0';
}

void	check_separator_char(int *sep, int *i, char *c, t_player *player)
{
	if (*c != SEPARATOR_CHAR)
		error_file("Syntax error", player->num_col, player->num_row);
	else
	{
		free(c);
		(*sep)++;
		(*i)++;
	}
}

void 	check_arg_num(char **args, t_instruction *instr, t_player *player)
{
	int i;
	int num;
	int separ;
	t_type	type;

	i = 0;
	separ = 0;
	while (args[i])
	{
		if (i % 2 == 1)
			check_separator_char(&separ, &i, args[i], player);
		if (i - separ >=  g_ins[instr->code_op - 1].args_num)
			error_name("Invalid parameter count for instruction", instr->instr);
		if (args[i] == NULL)
			error_file("Syntax error", player->num_col, player->num_row);//TODO: НЕТ ПОДСЧЕТА НОМЕРА ЭЛЕМЕНТА СТРОКИ ДЛЯ ВЫВОДА ОШИБОК
		if (!(type = know_type(args[i])))
			error_type(instr->instr, type, separ + 1);
		check_type_arg(type, g_ins[instr->code_op - 1].args_types[separ], instr, separ);
		f_funk_array[type - 1](instr->args[separ], args[i], instr->code_op);
		i++;
	}
	if (i - separ !=  g_ins[instr->code_op - 1].args_num)
		error_name("Invalid parameter count for instruction", instr->instr);
}

int 	calculate_size(t_instruction *instr)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (i < g_ins[instr->code_op - 1].args_num)
	{
		size += (int)instr->args[i]->size;
		i++;
	}
	size += (1 + g_ins[instr->code_op - 1].arg_type_code);
	return (size);
}

int 	check_arguments(t_player *player, char *arg_line)
{
	char **args;
	int i;

	i = 0;
	del_comment(arg_line);
	args = ft_split_argument(arg_line);
	if (args == NULL)
		error_name("No arguments for instruction", player->last_instr->instr);
	else
	{
		check_arg_num(args, player->last_instr, player);
		//args = NULL;
		player->last_instr->size_exec_code = calculate_size(player->last_instr);
	}
	while (player->last_instr->args[i]!= NULL)
	{
		printf("arg - %s\n", player->last_instr->args[i]->data);
		i++;
	}
	return (0);
}