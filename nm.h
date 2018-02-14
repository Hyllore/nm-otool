/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 11:12:34 by droly             #+#    #+#             */
/*   Updated: 2018/02/14 14:15:16 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct					s_stru
{
	struct symtab_command		*sym;
	struct section_64			*sec;
	unsigned int				i[3];
	struct load_command			*lc;
	char						**secname;
	struct s_nm					*nm;
	off_t						sizefile;
	char						*stringtable;
	struct mach_header_64		*header;
	struct segment_command_64	*seg;
	int							check;
	int							check2;
}								t_stru;

typedef struct					s_nm
{
	char						*name;
	char						type;
	uint32_t					value;
	struct s_nm					*next;
}								t_nm;

char							secto(unsigned int n_sect, char **secname);
int								checkcorrupt(char *tmp, void *ptr, \
		struct s_stru *stru);
void							handle_64(char *ptr, struct s_stru *stru);
int								exitstr(char *str, int error);
void							print_output(struct s_stru *stru, \
		char *ptr);

#endif
