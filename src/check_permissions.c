/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_permissions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 00:57:13 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/09 00:58:59 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The following flags are defined for the st_mode field:
//
//   S_IFMT     0170000   bitmask for the file type bitfields
//   S_IFSOCK   0140000   socket
//   S_IFLNK    0120000   symbolic link
//   S_IFREG    0100000   regular file
//   S_IFBLK    0060000   block device
//   S_IFDIR    0040000   directory
//   S_IFCHR    0020000   character device
//   S_IFIFO    0010000   FIFO
//   S_ISUID    0004000   set UID bit
//   S_ISGID    0002000   set-group-ID bit (see below)
//   S_ISVTX    0001000   sticky bit (see below)
//   S_IRWXU    00700     mask for file owner permissions
//   S_IRUSR    00400     owner has read permission
//   S_IWUSR    00200     owner has write permission
//   S_IXUSR    00100     owner has execute permission
//   S_IRWXG    00070     mask for group permissions
//   S_IRGRP    00040     group has read permission
//   S_IWGRP    00020     group has write permission
//   S_IXGRP    00010     group has execute permission
//   S_IRWXO    00007     mask for permissions for others (not in group)
//   S_IROTH    00004     others have read permission
//   S_IWOTH    00002     others have write permission
//   S_IXOTH    00001     others have execute permission


#include "ft_ls.h"

char check_type(mode_t mode)
{
	char perm;

	perm = '-';
	if (S_ISDIR(mode))
		perm = 'd';
	else if (S_ISREG(mode))
		perm = '-';
	else if (S_ISLNK(mode))
		perm = 'l';
	else if (S_ISBLK(mode))
		perm = 'b';
	else if (S_ISCHR(mode))
		perm = 'c';
	else if (S_ISSOCK(mode))
		perm = 's';
	else if (S_ISFIFO(mode))
		perm = 'p';
	return (perm);
}

char *check_permissions(mode_t mode)
{
	char *perm;

	perm = ft_strnew(10);
	perm = ft_memset(perm, '-', 10);
	perm[0] = check_type(mode);
	if (S_IRUSR & mode)
		perm[1] = 'r';
	if (S_IWUSR & mode)
		perm[2] = 'w';
	if (S_IXUSR & mode)
		perm[3] = 'x';
	if (S_IRGRP & mode)
		perm[4] = 'r';
	if (S_IWGRP & mode)
		perm[5] = 'w';
	if (S_IXGRP & mode)
		perm[6] = 'x';
	if (S_IROTH & mode)
		perm[7] = 'r';
	if (S_IWOTH & mode)
		perm[8] = 'w';
	if (S_IXOTH & mode)
		perm[9] = 'x';
	return(perm);
}
