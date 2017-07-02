/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 21:10:53 by rvan-der          #+#    #+#             */
/*   Updated: 2017/06/29 21:26:39 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int				is_sorted_players(t_player **players)
{
	int			i;

	i = -1;
	while (players[(++i) + 1] != NULL)
		if (players[i]->id < players[i + 1]->id)
			return (0);
	return (1);
}

void			sort_players(t_player **players)
{
	int			i;
	t_player	*tmp;

	while (!is_sorted_players(players))
	{
		i = -1;
		while (players[(++i) + 1] != NULL)
		{
			if (players[i]->id < players[i + 1]->id)
			{
				tmp = players[i];
				players[i] = players[i + 1];
				players[i + 1] = tmp;
			}
		}
	}
}

int				load_players(t_global *gb)
{
	int			i;
	int			pos;

	sort_players((t_player**)(gb->players));
	pos = (-1 * (MEM_SIZE / gb->nb_pl));
	i = -1;
	while (++i < gb->nb_pl)
	{
		pos += (MEM_SIZE / gb->nb_pl);
		ft_memcpy((void*)(gb->arena + pos), \
				(const void*)((gb->players)[i])->code, \
				(size_t)((gb->players)[i])->size);
		if (!init_new_proc(gb, pos, ((gb->players)[i])->id))
			return (0);
	}
	return (1);
}
