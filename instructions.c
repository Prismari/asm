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

	i = 0;
	len_token = search_length_token(player, line);
	while (i++ < 16)
		if (!ft_strcmp(ft_strsub(line, player->num_col, len_token), g_ins[i - 1].name))
			break ;
	if (i <= 16)
		return (len_token);
	return (0);
}

void	check_instruction(t_player *player, char *instr, char *line)
{
//	printf("instr [%s]\n", instr);
	t_instruction *new_instr;

	if (!(new_instr = init_instr(instr)))
		error("Memory allocation error");
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

int 	check_arguments(t_player *player, char *arg_line)
{
	char **args;

	del_comment(arg_line);
	args = ft_split_spaces(arg_line);
	while (*args != NULL)
	{
		printf("arg - %s\n", *args);
		args++;
	}
	return (0);
}