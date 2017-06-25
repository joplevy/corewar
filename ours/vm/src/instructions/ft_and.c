/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 03:40:44 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/25 03:49:52 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void				ft_and(t_list *p, t_global *gb)
{
	int		nxt;
	int		res;
	int		adr;

	if ((nxt = ft_get_params(gb->arena, ADR(p), p)))
	{
		if (PAR(p)[0].type == T_IND)
		{
			adr = get_relative(ADR(p), (short)PAR(p)[0].val, 1);
			PAR(p)[0].val = ft_get_int(gb->arena, adr, 4);
		}
		if (PAR(p)[1].type == T_IND)
		{
			adr = get_relative(ADR(p), (short)PAR(p)[1].val, 1);
			PAR(p)[1].val = ft_get_int(gb->arena, adr, 4);
		}
		res = PAR(p)[0].val & PAR(p)[1].val;
		CARRY(p) = (res == 0) ? 1 : 0;
		ft_reg_write(p, PAR(p)[2].reg, res);
		NEXT(p) = (nxt) % MEM_SIZE;
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
}
