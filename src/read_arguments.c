/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 01:20:00 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/09 01:33:30 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

//function that will concanate only charcaters and skip the dashes in argumets;
void	ft_strskipjoin(char **s1, char **s2)
{
	char *tmp;

	tmp = ft_strjoin(*s1, *s2);
	ft_strdel(s1);
	*s1 = ft_strdup(tmp);
	ft_strdel(&tmp);
}

//check options and argumnets;
void  set_option(char *str, t_posib *option)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'R')
			option->rec = 1;
		if (str[i] == 'a')
			option->a = 1;
		if (str[i] == 'l')
			option->l = 1;
		if (str[i] == 'r')
			option->r = 1;
		if (str[i] == 't')
			option->t = 1;
		++i;
	}
}

char *get_rid_of_dash(char **av, int *ac)
{
	int i;
	int num;
	char *str;
	char *tmp;

	i = 1;
	num = (*ac);
	str = ft_strnew(*ac);
	while (i < num && av[i][0] == '-' && av[i][1] != '\0')
	{
		if (ft_strcmp(av[i], "--") != 0)
		{
			tmp = ft_strdup(&av[i][1]);
			// printf("tmp %s\n", tmp);
			// printf("str %s\n", str);
			ft_strskipjoin(&str, &tmp);
			free(tmp);
		}
		else
		{
			--(*ac);
			break;
		}
		++i;
		--(*ac);
	}
	--(*ac);
	return (str);
}

char *get_argument(int ac, char **av, t_posib *option)
{
	// int i;
	// int j;
	int num; //arguments number
	char *str;

	num = ac;
	str = get_rid_of_dash(av, &ac); // str of all possible choices, ex:-r-l-a str = rla;
	//printf("str in get arg: %s\n", str);
	if ((option->path = (char **)malloc(sizeof(char *) * (((ac) == 0 ? 1 : ac) + 1))) == NULL)
	{
		printf("error in allocating memory\n");
		exit(1);
	}
	if (ac < 1)
	{
		option->path[0] = NULL;
		option->path[0] = ft_strdup(".");
		option->path[1] = NULL;
		option->nb_path++; //nb_path = 1;
		return (str);
	}
	// i = num - ac;
	// j = 0;
	// while (i < num)
	// {
	//   option->path[j] = NULL;
	//   option->path[j] = ft_strdup(av[i]);
	//   j++;
	//   i++;
	//   option->nb_path++;
	// }
	option->path = NULL;
	//printf("here mother");
	return (str);
}
