/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:19:34 by droly             #+#    #+#             */
/*   Updated: 2018/03/26 11:54:46 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		handle_32s3(struct s_stru *stru, char *ptr)
{
	size_t i;

	i = -1;
	if (ft_strcmp(stru->sec32->sectname, "__text") == 0)
		ft_printf("\nContents of (__TEXT,__text) section");
	while (++i < stru->sec32->size && ft_strcmp(stru->sec32->sectname,
				"__text") == 0)
		normal32(stru, ptr, i);
	if (ft_strcmp(stru->sec32->sectname, "__text") == 0)
		ft_printf("\n");
	stru->secname[stru->i[1]] = stru->sec32->sectname;
	stru->sec32 = (struct section *)(((void*)stru->sec32) + \
		sizeof(struct section));
	if (checkcorrupt(ptr + stru->sizefile, stru->sec32, stru) == 0)
		return (0);
	stru->i[1]++;
	stru->i[2]++;
	return (1);
}

int		handle_32s2(struct s_stru *stru, struct segment_command *seg,
		int nsects, char *ptr)
{
	if (stru->lc->cmd == LC_SEGMENT)
	{
		seg = (struct segment_command*)stru->lc;
		nsects += seg->nsects;
	}
	stru->lc = (void *)stru->lc + stru->lc->cmdsize;
	if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
		return (nsects);
	stru->i[0]++;
	return (nsects);
}

int		handle_32s(struct s_stru *stru, struct \
		segment_command *seg, char *ptr)
{
	if (stru->lc->cmd == LC_SEGMENT)
	{
		seg = (struct segment_command*)stru->lc;
		stru->sec32 = (struct section*)(seg + sizeof(seg) / sizeof(void*));
		if (checkcorrupt(ptr + stru->sizefile, stru->sec32, stru) == 0)
			return (0);
		while (stru->i[2] < seg->nsects)
		{
			if (handle_32s3(stru, ptr) == 0)
				return (0);
		}
		stru->i[2] = 0;
	}
	if (stru->lc->cmd == LC_SYMTAB)
	{
		stru->check2 = 0;
		stru->sym = (struct symtab_command *)stru->lc;
		return (0);
	}
	stru->lc = (void *)stru->lc + stru->lc->cmdsize;
	if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
		return (0);
	stru->i[0]++;
	return (1);
}

int		initstru32(struct s_stru *stru)
{
	int	nsects;

	stru->lc = stru->lc;
	stru->i[0] = 0;
	stru->i[1] = 0;
	stru->i[2] = 0;
	stru->check2 = 1;
	nsects = stru->seg32->nsects;
	stru->i[2] = nsects;
	if (stru->header32->filetype == MH_OBJECT)
		stru->obj = 0;
	else
		stru->obj = 1;
	return (nsects);
}

void	handle_32(char *ptr, struct s_stru *stru)
{
	int	nsects;

	nsects = initstru32(stru);
	while (stru->i[0] < stru->header32->ncmds)
	{
		nsects = handle_32s2(stru, stru->seg32, nsects, ptr);
		if (stru->check[0] == 1)
			return ;
	}
	stru->i[0] = 0;
	stru->i[2] = 0;
	stru->lc = (void *)ptr + sizeof(*stru->header32);
	if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
		return ;
	stru->secname = (char **)malloc(sizeof(char*) * nsects);
	stru->seg32 = (struct segment_command*)stru->lc;
	while (stru->i[0] < stru->header32->ncmds)
	{
		if (handle_32s(stru, stru->seg32, ptr) == 0)
			break ;
		if (stru->check[0] == 1)
			return ;
	}
	if (stru->check2 == 1)
		stru->check[0] = 1;
}
