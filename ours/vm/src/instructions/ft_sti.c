/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 03:41:12 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/29 22:12:36 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void				ft_sti(t_list *p, t_global *gb)
{
	int		adr;
	int		i;

	adr = get_relative(ADR(p), PAR(p)[1].val + \
		PAR(p)[2].val, 1);
	ft_int_write(gb->arena, adr, PAR(p)[0].val, 4);
	i = -1;
	while (++i < 4)
		gb->col[(adr + i) % MEM_SIZE] = \
		(gb->col[(adr + i) % MEM_SIZE] & 0xF) | (PID(p) << 4);
}
