/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 03:41:12 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/25 03:51:24 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void				ft_sti(t_list *p, t_global *gb)
{
	int		nxt;
	int		adr;
	int		i;

	if ((nxt = ft_get_params(gb->arena, ADR(p), p)))
	{
		if (PAR(p)[1].type == T_IND)
		{
			adr = get_relative(ADR(p), (short)PAR(p)[1].val, 1);
			PAR(p)[1].val = (short)ft_get_int(gb->arena, adr, 2);
		}
		adr = get_relative(ADR(p), (short)PAR(p)[1].val + \
			(short)PAR(p)[2].val, 1);
		ft_int_write(gb->arena, adr, PAR(p)[0].val, 4);
		NEXT(p) = (nxt) % MEM_SIZE;
		i = -1;
		while (++i < 4)
			gb->col[(adr + i) % MEM_SIZE] = \
			(gb->col[(adr + i) % MEM_SIZE] & 0xF) | (PID(p) << 4);
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
}
