/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 03:33:49 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/29 21:33:45 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void				ft_live(t_list *p, t_global *gb)
{
	int		id;

	id = PAR(p)[0].val;
	if (id < 0 && id >= (gb->nb_pl * -1))
	{
		((gb->players)[-(id) - 1])->lives += 1;
		gb->last_id = id;
	}
	gb->lives++;
	LIVE(p)++;
}
