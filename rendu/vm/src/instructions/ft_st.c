/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 03:40:30 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/29 21:38:54 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void				ft_st(t_list *p, t_global *gb)
{
	int		adr;
	int		i;

	if (PAR(p)[1].type == T_REG)
		ft_reg_write(p, PAR(p)[1].reg, PAR(p)[0].val);
	else
	{
		adr = get_relative(ADR(p), PAR(p)[1].reg, 1);
		ft_int_write(gb->arena, adr, PAR(p)[0].val, 4);
		i = -1;
		while (++i < 4)
			gb->col[(adr + i) % MEM_SIZE] = \
		(gb->col[(adr + i) % MEM_SIZE] & 0xF) | (PID(p) << 4);
	}
}
