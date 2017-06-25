/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 03:40:35 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/25 03:48:45 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void				ft_add(t_list *p, t_global *gb)
{
	int		nxt;
	int		res;

	if ((nxt = ft_get_params(gb->arena, ADR(p), p)))
	{
		res = PAR(p)[0].val + PAR(p)[1].val;
		CARRY(p) = (res == 0) ? 1 : 0;
		ft_reg_write(p, PAR(p)[2].reg, res);
		NEXT(p) = (nxt) % MEM_SIZE;
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
}
