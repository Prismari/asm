//
// Created by Asafoetida Estella on 2019-09-27.
//

#include "includes/corewar.h"

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
//	printf("instr [%s]\n", instr);
	t_instruction *new_instr;

	if (!(new_instr = init_instr(instr)))
		error("Memory allocation error");
	ft_link_new_instr(new_instr, player);
	player->last_instr->code_op = g_ins[i - 1].code;
	player->last_instr->count_args = g_ins[i - 1].args_num;
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

void 	check_arg_num(char **args, t_instruction *instr)
{
	int i;
	int separ;
	t_type	type;



	i = 0;
	separ = 0;
	while (args[i])
	{
		if (i % 2 == 1 && args[i][0] != SEPARATOR_CHAR)
			exit(1); // TODO: ВЫВЕСТИ ОШИБКУ - НЕТ ЗАПЯТОЙ МЕЖДУ АРГУМЕНТАМИ
		else
		{
			separ++;
			i++;
		}
		type = know_type(args[i]);

	}
	if (i - separ !=  g_ins[instr->code_op - 1].args_num)
		exit(1); // TODO: ВЫВЕСТИ ОШИБКУ - НЕ ВЕРНОЕ КОЛИЧЕСТВО АРГУМЕНТОВ
}

int 	check_arguments(t_player *player, char *arg_line)
{
	char **args;

	del_comment(arg_line);
	args = ft_split_argument(arg_line);
	if (args == NULL)
		error("No arguments"); // TODO: обработать ошибку - нет аргументов
	else
	{
		check_arg_num(args, player->last_instr);
		//TODO: проверить есть ли между аргументами запятая
		// совпадает ли количество аргументов
		// верны ли типы аргументов

	}
	while (*args != NULL)
	{
		printf("arg - %s\n", *args);
		args++;
	}
	return (0);
}