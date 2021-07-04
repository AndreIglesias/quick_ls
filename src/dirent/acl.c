/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 20:31:31 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/05 00:46:36 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	print_grp(gid_t st_gid, t_ls *ls)
{
	struct group	*grp;

	grp = getgrgid(st_gid);
	if (grp == NULL)
	{
		perror("getgrgid");
		exit_ls(ls, EXIT_FAILURE);
	}
	ft_printf("%s ", grp->gr_name);
}

static void	print_user(uid_t st_uid, t_ls *ls)
{
	struct passwd	*user;

	user = getpwuid(st_uid);
	if (user == NULL)
	{
		perror("getpwuid");
		exit_ls(ls, EXIT_FAILURE);
	}
	ft_printf("%s ", user->pw_name);
}

static void	print_permissions(mode_t st_mode)
{
	static const char	*rwx[8] = {"---", "--x", "-w-", "-wx",
								"r--", "r-x", "rw-", "rwx"};

	ft_printf("%c%s%s%s ", file_type(st_mode),
		rwx[(st_mode >> 6) & 7],
		rwx[(st_mode >> 3) & 7],
		rwx[st_mode & 7]);
}

void	print_element(char *cont, t_u_char *flags, t_ls *ls)
{
	struct stat	buf;

	ft_memset(&buf, 0, sizeof(struct stat *));
	if (lstat(cont, &buf) == -1)
	{
		perror("lstat");
		exit_ls(ls, EXIT_FAILURE);
	}
	if (flags['l'])
	{
		print_permissions(buf.st_mode);
		ft_printf("%lu ", buf.st_nlink);
		print_user(buf.st_uid, ls);
		print_grp(buf.st_gid, ls);
		ft_printf("%lu ", buf.st_size);
		ft_printf("%.12s ", &ctime(&buf.st_mtime)[4]);
	}
	element_color(cont, buf);
}
