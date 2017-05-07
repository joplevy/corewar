/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 14:38:41 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/04/22 16:38:25 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static int		is_sorted_players(t_player **players)
{
	int			i;

	i = -1;
	while (players[(++i) + 1] != NULL)
		if ((players[i])->id > (players[i + 1])->id)
			return (i);
	return (-2);
}

static void		bsort_players(t_player **players)
{
	int			i;
	t_player	*tmp;

	while ((i = is_sorted_players(players)) != -2)
	{
		while (players[(++i) + 1] != NULL)
		{
			if ((players[i])->id > (players[i + 1])->id)
			{
				tmp = players[i];
				players[i] = players[i + 1];
				players[i + 1] = tmp;
			}
		}
	}
}

static int		check_double(t_player **players)
{
	int			i;
	int			j;

	i = -1;
	while (players[++i] != NULL)
	{
		j = i;
		while ((players[i])->id != 0 && players[++j] != NULL)
			if ((players[j])->id == (players[i])->id \
				|| (players[i])->id > MAX_PLAYERS)
				return (0);
	}
	return (1);
}

int				sort_players(t_player **players)
{
	int			i;
	int			j;
	int			pid;

	if (!check_double(players))
		return (0);
	bsort_players(players);
	i = -1;
	pid = 1;
	while (!((players[++i])->id))
	{
		j = -1;
		while (players[++j] != NULL)
			if (i != j && (players[j])->id == pid)
			{
				pid++;
				j = -1;
			}
		(players[i])->id = pid;
	}
	bsort_players(players);
	return (1);
}
