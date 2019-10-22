//
// Created by Asafoetida Estella on 2019-10-22.
//

//#include "corewar.h"
#include "./includes/corewar.h" // TODO: удалить - это читсо для силайна


int		is_whitespace(int c)
{
	return (c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == ' ');
}

int 	is_label(char *line, t_player *player, int len)
{
	len--;
	if (line[player->num_col + len] == LABEL_CHAR)
		return (1);
	return (0);
}