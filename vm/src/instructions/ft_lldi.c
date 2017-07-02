/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 03:41:34 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/29 21:36:05 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void				ft_lldi(t_list *p, t_global *gb)
{
	int		adr;
	int		res;

	adr = get_relative(ADR(p), PAR(p)[0].val + PAR(p)[1].val, 0);
	res = ft_get_int(gb->arena, adr, 4);
	CARRY(p) = (res == 0) ? 1 : 0;
	ft_reg_write(p, PAR(p)[2].reg, res);
}
