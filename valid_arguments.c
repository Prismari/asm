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

	if (!(instr->args[num] = (t_tokens*)malloc(sizeof(t_tokens))))
		exit(1);
	instr->args[num]->type = type;
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