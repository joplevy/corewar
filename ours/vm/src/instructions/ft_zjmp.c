/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 03:41:00 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/25 03:51:01 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void				ft_zjmp(t_list *p, t_global *gb)
{
	short			jump;

	if (CARRY(p) == 1)
	{
		jump = (short)ft_get_int(gb->arena, ADR(p) + 1, 2);
		NEXT(p) = get_relative(ADR(p), jump, 1);
	}
	else
		NEXT(p) = (ADR(p) + 3) % MEM_SIZE;
}
