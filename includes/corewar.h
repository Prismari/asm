/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 12:29:08 by vurrigon          #+#    #+#             */
/*   Updated: 2019/10/19 15:07:27 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
//# include "libft.h"
//# include "ft_printf.h"
# include "../libft/libft.h" //TODO:УДАЛИТЬ - вернуть то что выше
# include "../libft/ft_printf.h" //TODO:УДАЛИТЬ - вернуть то что выше
# include "op.h"
# include "asm_operations.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
#include <stdio.h>
# define QUOTE 1
# define STOP_BEFORE_QUOTE 1
# define SKIP_QUOTE 0
# define NAME 1
# define COMMENT 2

typedef enum // TODO: переделать в Define
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
	int 			data_int;
	int 			col;
	int 			row;
}					t_tokens;

typedef struct		s_instruction
{
	char					*instr;
	unsigned short			code_op;
	unsigned short			count_args;
	t_tokens				**args;
	struct s_tokens			*tokens;
	struct s_label			*label;
	int 					start_bit;
	int						size_exec_code;
	struct s_instruction	*next; 
}					t_instruction;

typedef struct		s_player
{
	char					*name;
	char					*comment;
	char					*file_name;
	int 					fd;
	int						is_finished_name;
	int						is_finished_com;
	struct s_instruction	*instr;
	struct s_instruction	*last_instr;
	struct s_label			*labels;
	struct s_label			*last_label;
	struct s_label			*flag_lable_exist;
	int 					current_bit;
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
	struct s_label			*prev;
}					t_label;

typedef void (*t_func_pointer)(t_tokens *token, char *name, unsigned short instr, t_player *pl);

/*
** Assembler
*/


char			*ft_strndup(const char *src, int i);
int				is_comment(int chr);
t_player		*init_player(int fd, char *file_name);
int				is_whitespace(int c);
t_instruction	*init_instr(char *label); //??????
t_label			*init_label(char *label);
t_tokens		*init_tokens(t_type type);
int				check_name_comment(int fd, t_player *player);
void			check_comment(int fd, int lpos, char *buf);
void			check_arg_is_digit(t_player *player);
int				skip_tab_space(t_player *player, char *line, int flag);
void			handling_token(t_player *player, int len, char *line);
int 			search_length_token(t_player *player, char	*line);
void			add_instruction(t_player *player, t_instruction *instr);
int 			handling_label(t_player *player, char *line, int len);
int 			is_instruction(t_player *player, char *line);
int 			is_label(char *line, t_player *player, int len);
void			check_instruction(t_player *player, char *instr, char *line, int i);
void			check_lable_links(t_label *labels);
char			**ft_split_argument(char const *s);
int 			check_arguments(t_player *player, char *instr);
t_type			know_type(char *token);
void 			check_reg(t_tokens *token, char *name, unsigned short instr, t_player *pl);
void 			check_dir(t_tokens *token, char *name, unsigned short instr, t_player *pl);
void			check_dir_label(t_tokens *token, char *name, unsigned short instr, t_player *pl);
void			check_indir(t_tokens *token, char *name, unsigned short instr, t_player *pl);
void			check_indir_label(t_tokens *token, char *name, unsigned short instr, t_player *pl);
void			check_type_arg(t_type	type, int needed_type, t_instruction *instr, int num);

void			del_comment(char *line);
void			reading_body_champion(int fd, t_player *player);

/*
**	Error
*/

void			error(char *str);
void			error_file(char *str, int col, int row);
void			error_arg(t_instruction *inst, t_type type, int arg);
void			error_type(char *instr, t_type type, int arg);
void 			error_name(char *str, char *name, int row, int col);

/*
**	Bytecode
*/


int		create_file_bytecode(t_player *player);
void	int32_to_bytecode(unsigned char *bytes, int value, int size);
int		get_code_types(t_tokens **args);
void	translate_to_bytecode(t_player *player, int new_fd);
void	calculate_size_exec_code(t_player *player);

/*
**	Free asm
*/

void	free_asm(t_player *player);
void	free_split(char **str); //Есть в DASM
#endif
