/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 13:53:36 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/03 20:05:51 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ft_ls(t_ls *ls)
{
	(void)ls;
	//char	**tmp;
	//sort files & dirs
	ft_printf("files: ");
	ft_printf(" size: %lu ", sizeof(*ls->files));

	char	*hola = ft_strdup("hola");

	//char	**tmp = malloc(sizeof(char *) * (ls->size_f + 1));
	int pos = 3;

	//ft_memcpy(tmp, ls->files, sizeof(char *) * 1);//pos = 1
	//ft_memcpy(tmp + 1, &hola, sizeof(char **) * 1);
	//ft_memcpy(tmp + 2, ls->files + 1, sizeof(char *) * (ls->size_f - 1));//pos = 1
	//ls->files = tmp;
	ft_memins((void**)&ls->files, &hola, sizeof(char *) * pos,
		(t_sizes){sizeof(char *) * ls->size_f, sizeof(char **)});
	for (size_t i = 0; i < ls->size_f + 1; i++)
	{
		ft_printf("%p "BOLD"%s "E0M, (ls->files + i), *(ls->files + i));
	}
	ft_printf("\n");
}
