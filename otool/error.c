/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 16:54:08 by droly             #+#    #+#             */
/*   Updated: 2018/03/09 16:54:10 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		exitstr(char *str, int error)
{
	ft_putstr_fd(str, error);
	return (0);
}