/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 03:37:09 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/30 01:45:53 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void				ft_ld(t_list *p, t_global *gb)
{
	if (gb)
	{
		CARRY(p) = ((PAR(p)[0].val == 0) ? 1 : 0);
		ft_reg_write(p, PAR(p)[1].reg, PAR(p)[0].val);
	}
}
