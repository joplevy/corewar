/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 03:41:48 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/25 03:53:55 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void				ft_aff(t_list *p, t_global *gb)
{
	int		nxt;

	if ((nxt = ft_get_params(gb->arena, ADR(p), p)))
	{
		ft_putchar((char)(PAR(p)[0].val % 256));
		NEXT(p) = (nxt) % MEM_SIZE;
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
}
