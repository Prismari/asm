//
// Created by Asafoetida Estella on 2019-09-27.
//

#include "includes/corewar.h"

int 	is_instruction(t_player *player, char *line)
{
	int len_token;
	int i;

	i = 0;
	len_token = search_length_token(player, line);
	while (i++ < 16)
		if (!ft_strcmp(ft_strsub(line, player->num_col, len_token), g_ins[i - 1].name))
			break ;
	if (i < 16)
		return (len_token);
	return (0);
}

int 	check_arguments()
{

}