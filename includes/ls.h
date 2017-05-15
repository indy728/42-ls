/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 00:30:12 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/15 03:08:53 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include "libft.h"
# include <dirent.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>

typedef struct		s_file
{
	char			*name;
	char			*mode;
	unsigned int	links;
	char			*owner;
	char			*group;
	unsigned int	size;
	time_t			mod_time;
	time_t			acc_time;
	struct s_file	*left;
	struct s_file	*right;
}					t_file;

typedef struct		s_options
{
	char			one;
	char			big_a;
	char			a;
	char			big_c;
	char			c;
	char			d;
	char			f;
	char			big_g;
	char			g;
	char			l;
	char			m;
	char			n;
	char			o;
	char			p;
	char			big_r;
	char			r;
	char			big_s;
	char			s;
	char			big_t;
	char			t;
	char			u;
}					t_options;

void	print_tree(t_file *file, t_options options);
void	insert_elem(t_file **tree_top, t_file *new_leaf, t_options options);

#endif
