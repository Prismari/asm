/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 12:29:08 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/25 15:30:50 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "../includes/op.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define OFFSET_CMD_NAME 5
# define OFFSET_CMD_COMMENT 8
# define QUOTE 1
# define STOP_BEFORE_QUOTE 1
# define SKIP_QUOTE 0

typedef struct	s_op
{
	char			*name;
	unsigned char	code;
	unsigned short	args_num;
	short			arg_type_code:2;
	unsigned char	args_types[3];
	short			t_dir_size;
}				t_op;

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

typedef enum
{
	REGISTER = 1,
	DIRECT,
	DIRECT_LABEL,
	INDIRECT,
	INDIRECT_LABEL,
}	t_type;

typedef struct		s_tokens
{
	unsigned short	size;
	t_type			type;
	char			*data;
}					t_tokens;

typedef struct		s_instruction
{
	char					*label;
	unsigned short			code_op;
	unsigned short			count_args;
	struct s_tokens			*tokens;
	int						size_exec_code;
	struct s_instruction	*next; 
}					t_instruction;

typedef struct		s_player
{
	char					*name;
	char					*comment;
	struct s_instruction	*instr;
	struct s_instruction	*last_instr;
	struct s_label			*labels;
	struct s_label			*last_label;
	struct s_label			*flag_lable_exist;
	int						sum_size_exec_code;
	int						num_row;
	int						num_col;

}					t_player;

typedef struct		s_label
{
    char					*l_name;
    struct s_instruction	*instr;
    int						sum_size_exec_code;
    struct s_label			*next;
}					t_label;


/*
** Assembler
*/

void			error(char *str);
void			error_file(char *str, int col, int row);
char			*ft_strndup(const char *src, int i);
int				is_comment(int chr);
t_player		*init_player(void);
int				is_whitespace(int c);
t_instruction	*init_instr(char *label); //??????
t_label			*init_lable(char *label);
int				check_name_comment(int fd, t_player *player);
int				skip_tab_space(t_player *player, char *line, int flag);
void			handling_token(t_player *player, int len, char *line);
int 			search_length_token(t_player *player, char	*line);
void			add_instruction(t_player *player, t_instruction *instr);
int 			handling_label(t_player *player, char *line, int len);
int 			is_instruction(t_player *player, char *line);

#endif
