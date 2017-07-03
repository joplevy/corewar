/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 03:33:49 by jplevy            #+#    #+#             */
/*   Updated: 2017/07/03 20:06:33 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void				ft_live(t_list *p, t_global *gb)
{
	int		id;
	int		i;

	id = PAR(p)[0].val;
	if (id < 0 && id >= (gb->nb_pl * -1))
	{
		((gb->players)[-(id) - 1])->lives += 1;
		gb->last_id = id;
		i = 59;
		while (--i > 0)
			gb->livescol[i] = gb->livescol[i - 1];
		gb->livescol[0] = (-(id)) << 4;
	}
	gb->lives++;
	LIVE(p)++;
}
