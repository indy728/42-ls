/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 00:30:12 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/16 17:16:00 by kmurray          ###   ########.fr       */
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

typedef struct		s_file
{
	char			*name;
	char			*mode;
	unsigned int	links;
	char			*owner;
	char			*group;
	unsigned int	size;
	time_t			mod_time;
	long			mod_ntime;
	time_t			acc_time;
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
//	char			c;  use time when file was last changed for sorting or printing
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
//	char			s; display block size before file info
//	char			big_t; with -l, display complete time information of file
	char			t;
//	char			u; use time of last access for sorting
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
