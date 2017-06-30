/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 03:40:39 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/29 21:48:53 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void				ft_sub(t_list *p, t_global *gb)
{
	int		res;

	if (gb)
	{
		res = PAR(p)[0].val - PAR(p)[1].val;
		CARRY(p) = (res == 0) ? 1 : 0;
		ft_reg_write(p, PAR(p)[2].reg, res);
	}
}