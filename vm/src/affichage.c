/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 14:12:41 by joeyplev          #+#    #+#             */
/*   Updated: 2017/07/03 20:28:03 by joeyplevy        ###   ########.fr       */
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

void		put_info(t_global *all, int period)
{
	int		i;
	int		procs;
	int		offset;
	int		j;
	
	offset = period;
	offset = 3 + (all->nb_pl * 5);
	werase(all->info);
	mvwprintw(all->info, 1, 2, "CONTESTANTS:");
	mvwprintw(all->info, 3, 3, SEPARATOR);
	procs = count_procs(all);
	i = -1;
	while (++i < all->nb_pl)
		put_player(all->info, (all->players)[i], 4 + (i * 5), 4);
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
		mvwprintw(all->info, offset + 17, 3 +  j, "-");
		wattroff(all->info, COLOR_PAIR(all->livescol[j]));
	}
	mvwprintw(all->info, offset + 17, 61, "|");
	box(all->info, 0, 0);
	wrefresh(all->info);
}

void		box_put_arena(t_global *all, struct timespec speed, int period)
{
	int		i;
	int		x;
	int		y;
	short	col;

	i = -1;
	while (++i < MEM_SIZE)
	{
		x = i % TAB_WIDTH;
		y = i / TAB_WIDTH;
		wmove(all->box, y + 1, (x * 3) + 2);
		col = ((all->col[i] & 0xF) == ((all->col[i] & 0xF0) >> 4)) ?
		all->col[i] & 0xF : all->col[i];
		wattron(all->box, COLOR_PAIR(col));
		wprintw(all->box, "%02x", all->arena[i]);
		wattroff(all->box, COLOR_PAIR(col));
	}
	put_info(all, period);
	wrefresh(all->box);
	nanosleep(&speed, &speed);
}

void		end_ncurses(t_global *all)
{
	int			i;
	int			offset;
	t_player	*winner;

	offset = 23 + (all->nb_pl * 5);
	i = -1;
	winner = (all->last_id) ? (all->players)[-(all->last_id) - 1] : NULL;
	wattron(all->info, COLOR_PAIR((all->last_id) ? (-(all->last_id)) << 4 : 0));
	while (++i < 15)
		mvwprintw(all->info, offset + i, 2, "%s", game_over[i]);
	wattroff(all->info, COLOR_PAIR((all->last_id) ? (-(all->last_id)) << 4 : 0));
	if (winner)
	{
		mvwprintw(all->info, offset + (++i), 2, \
			"And the winner is : %s!\n", winner->name);
		mvwprintw(all->info, offset + (++i), 2, \
			"-Sir, do you have anything to say to your fans ?\n");
		mvwprintw(all->info, offset + (++i), 2, \
			"-%s\n", (winner->comment) + 2);
	}
	else
		mvwprintw(all->info, offset + (++i), 2,"No winner for this match!\n");
	mvwprintw(all->info, 64, 22,"press any key to exit");
	box(all->info, 0, 0);
	wrefresh(all->info);
	getch();
	delwin(all->box);
	delwin(all->info);
	endwin();
}

void		color_init(t_global *all)
{
	int		i;
	int		p;
	int		mnp;
	int		imnp;

	if (!(all->col = (ft_memalloc(MEM_SIZE * sizeof(short)))))
		return ;
	i = -1;
	mnp = MEM_SIZE / all->nb_pl;
	while (++i < MEM_SIZE)
	{
		imnp = i / mnp;
		p = (i == imnp * mnp) ? ((imnp + 1) << 4)
			| (imnp + 1) : (imnp + 1) << 4;
		if (imnp < all->nb_pl && \
			i >= imnp * mnp && i < imnp * mnp + all->players[imnp]->size)
			all->col[i] = p;
		else
			all->col[i] = (7 << 4);
	}
}

void		init_ncurses(t_global *all)
{
	short	txt;
	short	fond;

	color_init(all);
	if (all->show != 1)
		return ;
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	refresh();
	start_color();
	txt = -1;
	while (++txt < 8)
	{
		fond = -1;
		while (++fond < 8)
			init_pair((txt << 4) | fond, txt, fond);
	}
	all->box = newwin(TAB_HEIGHT + 2, (TAB_WIDTH * 3) + 3, 0, 0);
	all->info = newwin(TAB_HEIGHT + 2, 65, 0, (TAB_WIDTH * 3) + 4) ;
	box(all->box, 0, 0);
}

void		ft_putbinary(char *str, int size)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		ft_printf("%02x ", str[i] & 0xFF);
		if ((i + 1) % TAB_WIDTH == 0)
			ft_putchar('\n');
	}
}
