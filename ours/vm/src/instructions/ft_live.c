/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 03:33:49 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/25 03:35:25 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void				ft_live(t_list *p, t_global *gb)
{
	int		id;

	id = ft_get_int(gb->arena, (ADR(p) + 1) % MEM_SIZE, 4);
	if (id < 0 && id > -5)
		gb->last_id = id;
	gb->lives++;
	LIVE(p)++;
	NEXT(p) = (ADR(p) + 5) % MEM_SIZE;
}
