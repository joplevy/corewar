/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 20:13:14 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/11 20:14:28 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void 				(*instructab[17])(t_list *, t_global *) =
{
	&ft_live, &ft_ld, &ft_st, &ft_add, &ft_sub, &ft_and,
	&ft_or, &ft_xor, &ft_zjmp, &ft_ldi, &ft_sti, &ft_fork,
	&ft_lld, &ft_lldi, &ft_lfork, &ft_aff, NULL
};
