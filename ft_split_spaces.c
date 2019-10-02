/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 11:56:43 by djast             #+#    #+#             */
/*   Updated: 2019/03/18 11:24:42 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "includes/corewar.h"

int		is_whitespace(int c)
{
	return (c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == ' ');
}

static int		word_count(char const *s)
{
	int	w;
	int	i;

	w = 0;
	i = 0;
	while (s[i])
	{
		if (!(is_whitespace(s[i])) && (is_whitespace(s[i + 1])
			|| s[i + 1] == '\0' || s[i + 1] == SEPARATOR_CHAR) && s[i] != SEPARATOR_CHAR)
			w++;
		if ( s[i] == SEPARATOR_CHAR)
			w++;
		i++;
	}
	return (w);
}

static int		word_size(const char *s)
{
	int i;

	i = 0;
	while (is_whitespace(*s) && *s != '\0')
		s++;
	if (*s == SEPARATOR_CHAR)
		return (1);
	while (!(is_whitespace(*s)) && *s != '\0')
	{
		if (*s == SEPARATOR_CHAR)
			break;
		s++;
		i++;
	}
	return (i);
}

static char		*word_allocation(char **arr, char *word, int size)
{
	int i;

	i = 0;
	word = (char *)malloc(sizeof(char) * (size + 1));
	if (!word)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
		arr = NULL;
		return (NULL);
	}
	return (word);
}

char			**ft_split_argument(char const *s)
{
	char	**res;
	int		w_count;
	int		i;
	int		j;

	j = 0;
	if (!s)
		return (NULL);
	if (!(w_count = word_count(s)))
		return (NULL);
//	if ((w_count = word_count(s)) > 5) //!= num
//		exit(1);                            // TODO: ВЫВЕСТИ ОШИБКУ - СЛИШКОМ МНОГО АРГУМЕНТОВ
	if (!(res = (char **)malloc(sizeof(char *) * (w_count + 1))))
		return (NULL);
	while (j < w_count)
	{
		i = 0;
		if (!(res[j] = word_allocation(res, res[j], word_size(s))))
			return (NULL);
		while (is_whitespace(*s) && s != '\0')
			s++;
		if (*s == SEPARATOR_CHAR)
		{
			res[j][i++] = *s++;
			res[j][i] = '\0';
			j++;
			continue ;
		}
		while (!(is_whitespace(*s)) && *s && *(s - 1))
		{
			res[j][i++] = *s++;
			if (*s == SEPARATOR_CHAR)
				break;
		}
		res[j][i] = '\0';
		j++;
	}
	res[j] = 0;
	return (res);
}