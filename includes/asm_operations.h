
#ifndef ASM_OPEARIONS_H
# define ASM_OPEARIONS_H

typedef struct	s_op
{
	char			*name;
	unsigned char	code;
	unsigned short	args_num;
	short			arg_type_code:2;
	unsigned char	args_types[3];
	short			t_dir_size;
}				t_op;

static int 		i_name[8][7] = {
		{15, 1, 14, 10, 13, 2, -1},	//l
		{4, 6, 16, -1},				//a
		{11, 5, 3, -1},				//s
		{7, -1},	                //o
		{12, -1},					//f
		{8, -1},					//x
		{9, -1},					//z
		{-1}
};

static t_op		g_ins[16] = {
	{
		.name = "live",
		.code = 0x01,
		.args_num = 1,
		.arg_type_code = 0,
		.args_types = {T_DIR, 0, 0},
		.t_dir_size = 4,
	},
	{
		.name = "ld",
		.code = 0x02,
		.args_num = 2,
		.arg_type_code = 1,
		.args_types = {T_DIR | T_IND, T_REG, 0},
		.t_dir_size = 4,
	},
	{
		.name = "st",
		.code = 0x03,
		.args_num = 2,
		.arg_type_code = 1,
		.args_types = {T_REG, T_REG | T_IND, 0},
		.t_dir_size = 4,
	},
	{
		.name = "add",
		.code = 0x04,
		.args_num = 3,
		.arg_type_code = 1,
		.args_types = {T_REG, T_REG, T_REG},
		.t_dir_size = 4,
	},
	{
		.name = "sub",
		.code = 0x05,
		.args_num = 3,
		.arg_type_code = 1,
		.args_types = {T_REG, T_REG, T_REG},
		.t_dir_size = 4,
	},
	{
		.name = "and",
		.code = 0x06,
		.args_num = 3,
		.arg_type_code = 1,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.t_dir_size = 4,
	},
	{
		.name = "or",
		.code = 0x07,
		.args_num = 3,
		.arg_type_code = 1,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.t_dir_size = 4,
	},
	{
		.name = "xor",
		.code = 0x08,
		.args_num = 3,
		.arg_type_code = 1,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.t_dir_size = 4,
	},
	{
		.name = "zjmp",
		.code = 0x09,
		.args_num = 1,
		.arg_type_code = 0,
		.args_types = {T_DIR, 0, 0},
		.t_dir_size = 2,
	},
	{
		.name = "ldi",
		.code = 0x0A,
		.args_num = 3,
		.arg_type_code = 1,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.t_dir_size = 2,
	},
	{
		.name = "sti",
		.code = 0x0B,
		.args_num = 3,
		.arg_type_code = 1,
		.args_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
		.t_dir_size = 2,
	},
	{
		.name = "fork",
		.code = 0x0C,
		.args_num = 1,
		.arg_type_code = 0,
		.args_types = {T_DIR, 0, 0},
		.t_dir_size = 2,
	},
	{
		.name = "lld",
		.code = 0x0D,
		.args_num = 2,
		.arg_type_code = 1,
		.args_types = {T_DIR | T_IND, T_REG, 0},
		.t_dir_size = 4,
	},
	{
		.name = "lldi",
		.code = 0x0E,
		.args_num = 3,
		.arg_type_code = 1,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.t_dir_size = 2,
	},
	{
		.name = "lfork",
		.code = 0x0F,
		.args_num = 1,
		.arg_type_code = 0,
		.args_types = {T_DIR, 0, 0},
		.t_dir_size = 2,
	},
	{
		.name = "aff",
		.code = 0x10,
		.args_num = 1,
		.arg_type_code = 1,
		.args_types = {T_REG, 0, 0},
		.t_dir_size = 4,
	}
};
#endif