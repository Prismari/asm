//
// Created by Asafoetida Estella on 2019-10-01.
//

#include "./includes/corewar.h"

t_func_pointer f_funk_array[5] = {
		check_reg,
		check_dir,
		check_dir_label,
		check_indir,
		check_indir_label
};

void	check_type_arg(t_type type, int needed_type, t_instruction *instr, int num)
{
	if (type == DIRECT_LABEL || type == INDIRECT_LABEL)
	{
		if (((type - 1) & needed_type) != (type - 1))
			error_type(instr->instr, type, num);
	}
	else if ((type & needed_type) != type)
		error_type(instr->instr, type, num);
	if (!(instr->args[num] = init_tokens(type)))
		exit(1);
}

void 		check_reg(t_tokens *token, char *name, unsigned short ignored)
{
	ignored += 0;
	token->data = name;
	token->size = 1;
}

void 		check_dir(t_tokens *token, char *name, unsigned short instr)
{
	token->data = name;
	token->size = g_ins[instr - 1].t_dir_size;
}

void		check_dir_label(t_tokens *token, char *name, unsigned short instr)
{
	token->data = name;
	token->size = g_ins[instr - 1].t_dir_size;
}

void		check_indir(t_tokens *token, char *name, unsigned short ignored)
{
	ignored += 0;
	token->data = name;
	token->size = 2;
}

void		check_indir_label(t_tokens *token, char *name, unsigned short ignored)
{
	ignored += 0;
	token->data = name;
	token->size = 2;
}

int		arg_to_int(t_tokens *arg)
{
	char	*str;
	int		i;

	i = 0;
	str = arg->data;
	if (arg->type != INDIRECT)
		i++;
	if (str[i] == '-')
		i++;
	while (str[i])
		if (!(isdigit(str[i++])))
			error("Syntax error"); // TODO: ПРОВЕРИТЬ ФОРМУЛИРОВКУ
	if (arg->type != INDIRECT)
			return (ft_atoi(&(str[1])));
	return (ft_atoi(str));
}

void		lable_to_int(t_label *lables, t_instruction *instr, int arg_num)
{
	t_label *tmp;
	char 	*str_label;
	int 	i;

	tmp = lables;
	while (tmp)
	{
		i = 1;
		str_label = instr->args[arg_num]->data;
		if (instr->args[arg_num]->type == DIRECT_LABEL)
			i++;
		if (!(ft_strcmp(&(str_label[i]), tmp->l_name)))
		{
//			printf("LAble_start [%d], instr_start [%d]\n", tmp->instr->start_bit, instr->start_bit);
			instr->args[arg_num]->data_int = tmp->instr->start_bit - instr->start_bit;
			//instr->args[arg_num]->data_int = tmp->instr->start_bit;
		}
		tmp = tmp->next;
	}
	if (instr->args[arg_num]->data_int == -1)
		error("Lable not exist"); // TODO: ПРОВЕРИТЬ ФОРМУЛИРОВКУ
}

void		check_arg_is_digit(t_player *player)
{
	t_instruction *instr;
	int i;

	instr = player->instr;
	while (instr)
	{
		i = 0;
//		ft_printf("instr : %s\n", instr->instr);
		while (i < instr->count_args)
		{
			if (instr->args[i]->type == DIRECT_LABEL || instr->args[i]->type == INDIRECT_LABEL)
				lable_to_int(player->labels, instr, i);
			else
				instr->args[i]->data_int = arg_to_int(instr->args[i]);
//			ft_printf("\t -%8s -> %4d\n", instr->args[i]->data, instr->args[i]->data_int);
			i++;
		}
		 instr = instr->next;
	}
}