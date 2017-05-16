/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 19:14:31 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/16 00:23:13 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int	main(int ac, char **av)
{
	int				i;
	t_options		options;

	ft_bzero(&options, sizeof(t_options));
	i = mark_options(ac, av, &options, 1);
	if (i == ac)
		build_tree(".", &options);
	else
		param_tree(ac, av, i, &options);
	return (0);
}
