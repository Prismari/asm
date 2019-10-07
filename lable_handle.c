//
// Created by Asafoetida Estella on 2019-09-27.
//

#include "includes/corewar.h"

int 	is_label(char *line, t_player *player, int len)
{
	len--;
	if (line[player->num_col + len] == LABEL_CHAR)
		return (1);
	return (0);
}

void	check_label(t_player *player, char *label)
{
//	printf("label [%s]\n", label);
	int	i;
	t_label *new_label;

	i = 0;
	while(label[i])
		if (!ft_strchr(LABEL_CHARS, label[i++]))
			error_file("Invalid label name", player->num_col + 1, player->num_row);
	if (!(new_label = init_lable(label)))
		error("Memory allocation error");
	if (player->labels == NULL)
	{
		player->labels = new_label;
		player->last_label = new_label;
	}
	else
	{
		player->last_label->next = new_label;
		new_label->prev = player->last_label;
		player->last_label = player->last_label->next;
	}
}

int 	handling_label(t_player *player, char *line, int len)
{
	check_label(player, ft_strsub(line, player->num_col, len));
	player->flag_lable_exist = player->last_label;
	player->num_col += len + 1;
	while (line[player->num_col])
	{
		if (is_comment(line[player->num_col]))
		{
//			printf("nothing after label\n");
			break;
		}
		else if (is_whitespace(line[player->num_col]))
		{
//			printf("SKIP\n");
			skip_tab_space(player, line, SKIP_QUOTE);
		}
		else if (!(is_instruction(player, line)))
		{
			error_file("Syntax error", player->num_col, player->num_row);
//			printf("TOKEN [%s]\n", ft_strsub(line, player->num_col, len));
			//player->num_col += len;
//			printf("instr after label\n");
			//check_instruction(player, ft_strsub(line, player->num_col - len, len), &(line[player->num_col]));
			//ФУНКЦИЯ КОТОРАЯ ЗАПИСЫВАЕТ АРГУМЕНТЫ
			break ;
		}
//		else
//			error_file("Syntax error", player->num_col, player->num_row);
	}
	return (0);
}