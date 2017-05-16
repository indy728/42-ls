/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 15:51:04 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/15 22:42:47 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int	mark_options(int ac, char **av, t_options *options, int i)
{
	char	*str;
	int		j;

	str = av[i];
	while(i < ac && str[0] == '-')
	{
		j = 0;
		while (str[++j])
		{
			if (str[j] == 'l')
				options->l = 1;
			else if (str[j] == 'R')
				options->big_r = 1;
			else if (str[j] == 'a')
				options->a = 1;
			else if (str[j] == 'r')
				options->r = 1;
			else if (str[j] == 't')
				options->t = 1;
			else if (str[j] == 'S')
				options->big_s = 1;
			else if (str[j] == '1')
				options->l = 0;
			else if (str[j] == 'A')
				options->big_a = 1;
			else if (str[j] == 'n')
			{
				options->n = 1;
				options->l = 1;
			}
		}
		++i;
		str = av[i];
	}
	return (i);
}
