/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 02:51:18 by jplevy            #+#    #+#             */
/*   Updated: 2017/07/04 02:59:15 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int			count_procs(t_global *all)
{
	int		ret;
	t_list	*tmp;

	ret = -1;
	while (++ret < all->nb_pl)
		((all->players)[ret])->procs = 0;
	ret = 0;
	tmp = all->procs;
	while (tmp != NULL)
	{
		ret++;
		((all->players)[PID(tmp) - 1])->procs += 1;
		tmp = tmp->next;
	}
	return (ret);
}

void		put_player(WINDOW *info, t_player *pl, int y, int x)
{
	wattron(info, COLOR_PAIR((-(pl->id)) << 4));
	mvwprintw(info, y, x, "PLAYER%d: ", pl->id);
	wattroff(info, COLOR_PAIR((-(pl->id)) << 4));
	wprintw(info, "%s", pl->name);
	mvwprintw(info, y + 1, x + 1, "-size: %d bytes", pl->size);
	mvwprintw(info, y + 2, x + 1, "-processes: %d", pl->procs);
	mvwprintw(info, y + 3, x + 1, "-lives: ");
	wattron(info, COLOR_PAIR((-(pl->id)) << 4));
	wprintw(info, "%d", pl->lives);
	wattroff(info, COLOR_PAIR((-(pl->id)) << 4));
	mvwprintw(info, y + 4, 3, SEPARATOR);
}

void		ft_put_gb_info(t_global *all, int period, int offset)
{
	int		j;
	int		procs;

	procs = count_procs(all);
	mvwprintw(all->info, offset + 3, 2, "Speed limit: %d cycles/sec", SPEED);
	mvwprintw(all->info, offset + 5, 2, "Cycle: %d", all->cycles);
	mvwprintw(all->info, offset + 7, 2, "Total processes: %d", procs);
	mvwprintw(all->info, offset + 9, 2, "Next check in: %d", all->ctd - period);
	mvwprintw(all->info, offset + 11, 2, "CYCLE_TO_DIE: %d", all->ctd);
	mvwprintw(all->info, offset + 13, 2, "CYCLE_DELTA: %d", CYCLE_DELTA);
	mvwprintw(all->info, offset + 15, 2, "LAST PLAYER ALIVE\n   V");
	wattron(all->info, COLOR_PAIR((all->livescol[0]) >> 4));
	mvwprintw(all->info, offset + 15, 21, "  ");
	wattroff(all->info, COLOR_PAIR((all->livescol[0]) >> 4));
	mvwprintw(all->info, offset + 17, 2, "|");
	j = -1;
	while (++j < 59)
	{
		wattron(all->info, COLOR_PAIR(all->livescol[j]));
		mvwprintw(all->info, offset + 17, 3 + j, "-");
		wattroff(all->info, COLOR_PAIR(all->livescol[j]));
	}
	mvwprintw(all->info, offset + 17, 61, "|");
}

void		put_info(t_global *all, int period)
{
	int		i;
	int		offset;

	offset = 3 + (all->nb_pl * 5);
	werase(all->info);
	mvwprintw(all->info, 1, 2, "CONTESTANTS:");
	mvwprintw(all->info, 3, 3, SEPARATOR);
	i = -1;
	while (++i < all->nb_pl)
		put_player(all->info, (all->players)[i], 4 + (i * 5), 4);
	ft_put_gb_info(all, period, offset);
	box(all->info, 0, 0);
	wrefresh(all->info);
}

t_player	*ft_print_go(t_global *gb, int *i, int offset)
{
	t_player	*winner;

	winner = (gb->last_id) ? (gb->players)[-(gb->last_id) - 1] : NULL;
	wattron(gb->info, COLOR_PAIR((gb->last_id) ? (-(gb->last_id)) << 4 : 0));
	while (++(*i) < 15)
		mvwprintw(gb->info, offset + (*i), 2, "%s", g_game_over[*i]);
	wattroff(gb->info, COLOR_PAIR((gb->last_id) ? (-(gb->last_id)) << 4 : 0));
	return (winner);
}
