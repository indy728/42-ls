/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 00:30:12 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/18 00:43:31 by kmurray          ###   ########.fr       */
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
# include <stdio.h>

# define USAGE "usage: ./ft_ls [-ARSTaclnrstu1]\n"
# define OPTIONS "ARSTaclnrstu1"

char				g_nl;

typedef struct		s_file
{
	char			*name;
	char			*mode;
	unsigned int	nlink;
	char			*owner;
	char			*group;
	int				size;
	time_t			time;
	long			ntime;
	char			*link;
	int				blocks;
	struct s_file	*left;
	struct s_file	*right;
}					t_file;

typedef struct		s_params
{
	char			*param;
	struct s_params	*left;
	struct s_params	*right;
}					t_params;

typedef struct		s_options
{
	char			big_a;
	char			a;
	char			c;
//	char			d;	directories are listed as plain files and not searched
//	char			f;	output is not sorted
//	char			g;	suppresses owner name in -l format
	char			l;
//	char			m; stream output format across page, separated by commas (overrerrules/ruled by -l)
	char			n;
//	char			o; list in long format but omit group ID
//	char			p; write "/" after each filename that is a directory
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
char	*check_permissions(mode_t mode);
int		mark_options(int ac, char **av, t_options *options, int i);
void	build_tree(char *path, t_options *options);
size_t	get_attributes(t_file *file, char *path, t_options *options);
void	list_recursive(char *path, t_file *root, t_options options);
void	param_tree(int ac, char **av, int i, t_options *options);
void	destroy_tree(t_file *root);

#endif
