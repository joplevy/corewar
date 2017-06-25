/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 03:41:34 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/25 20:56:08 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void				ft_lldi(t_list *p, t_global *gb)
{
	int		nxt;
	int		adr;
	int		res;

	if ((nxt = ft_get_params(gb->arena, ADR(p), p)))
	{
		if (PAR(p)[0].type == T_IND)
		{
			adr = get_relative(ADR(p), (short)PAR(p)[0].val, 0);
			PAR(p)[0].val = (short)ft_get_int(gb->arena, adr, 2);
		}
		adr = get_relative(ADR(p), (short)PAR(p)[0].val + \
			(short)PAR(p)[1].val, 0);
		res = ft_get_int(gb->arena, adr, 4);
		CARRY(p) = (res == 0) ? 1 : 0;
		ft_reg_write(p, PAR(p)[2].reg, res);
		NEXT(p) = (nxt) % MEM_SIZE;
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
}
