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

void 		check_reg(t_tokens *token, char *name, unsigned short ignored, t_player *pl)
{
	ignored += 0;
	token->data = name;
	token->size = 1;
	token->col = pl->num_col;
	token->row = pl->num_row;
//	ft_printf("arg [%s] - [%d:%d]\n", name, token->row, token->col);
}

void 		check_dir(t_tokens *token, char *name, unsigned short instr, t_player *pl)
{
	token->data = name;
	token->size = g_ins[instr - 1].t_dir_size;
	token->col = pl->num_col;
	token->row = pl->num_row;
//	ft_printf("arg [%s] - [%d:%d]\n", name, token->row, token->col);
}

void		check_dir_label(t_tokens *token, char *name, unsigned short instr, t_player *pl)
{
	token->data = name;
	token->size = g_ins[instr - 1].t_dir_size;
	token->col = pl->num_col;
	token->row = pl->num_row;
//	ft_printf("arg [%s] - [%d:%d]\n", name, token->row, token->col);
}

void		check_indir(t_tokens *token, char *name, unsigned short ignored, t_player *pl)
{
	ignored += 0;
	token->data = name;
	token->size = 2;
	token->col = pl->num_col;
	token->row = pl->num_row;
//	ft_printf("arg [%s] - [%d:%d]\n", name, token->row, token->col);
}

void		check_indir_label(t_tokens *token, char *name, unsigned short ignored, t_player *pl)
{
	ignored += 0;
	token->data = name;
	token->size = 2;
	token->col = pl->num_col;
	token->row = pl->num_row;
//	ft_printf("arg [%s] - [%d:%d]\n", name, token->row, token->col);
}

int		arg_to_int(t_tokens *arg, t_instruction *instr, int arg_num)
{
	char	*str;
	int		i;

	i = 0;
	str = arg->data;
	if (arg->type != INDIRECT)
		i++;
	if (str[i] == '-')
		i++;
	else if (str[i] == '\0')
		error_arg(instr, instr->args[arg_num]->type, arg_num + 1);
	while (str[i])
		if (!(isdigit(str[i++])))
			error_arg(instr, instr->args[arg_num]->type, arg_num + 1);
	if (arg->type != INDIRECT)
			return (ft_atoi(&(str[1])));
	return (ft_atoi(str));
}

void		lable_to_int(t_label *lables, t_instruction *instr, int arg_num, t_player *pl)
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
			if (!tmp->instr)
				instr->args[arg_num]->data_int = pl->sum_size_exec_code - instr->start_bit;
			else
				instr->args[arg_num]->data_int = tmp->instr->start_bit - instr->start_bit;

			//			printf("LAble_start [%d], instr_start [%d]\n, ", tmp->instr->start_bit, instr->start_bit);
			//instr->args[arg_num]->data_int = tmp->instr->start_bit;
		}
		tmp = tmp->next;
	}
	if (instr->args[arg_num]->data_int == -1)
		error_name("Lable", "not exist", instr->args[arg_num]->row, instr->args[arg_num]->col); // TODO: ПРОВЕРИТЬ ФОРМУЛИРОВКУ
}

void		check_arg_is_digit(t_player *player)
{
	t_instruction *instr;
	int i;

	if (!(instr = player->instr))
		error_file("Syntax error", player->num_row, player->num_col);
	while (instr)
	{
		i = 0;
//		ft_printf("instr : %s\n", instr->instr);
		while (i < instr->count_args)
		{
			if (instr->args[i]->type == DIRECT_LABEL || instr->args[i]->type == INDIRECT_LABEL)
				lable_to_int(player->labels, instr, i, player);

			else
			{
				instr->args[i]->data_int = arg_to_int(instr->args[i], instr, i);
				if (instr->args[i]->type == REGISTER && (instr->args[i]->data_int < 1 || instr->args[i]->data_int > 99))
					error_arg(instr, instr->args[i]->type, i + 1);
			}
//			ft_printf("\t -%8s -> %4d\n", instr->args[i]->data, instr->args[i]->data_int);
			i++;
		}
		 instr = instr->next;
	}
}