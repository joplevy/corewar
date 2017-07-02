/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplev <joeyplev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 14:12:41 by joeyplev          #+#    #+#             */
/*   Updated: 2017/06/29 19:33:28 by niludwig         ###   ########.fr       */
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
	mvwprintw(info, y, x, "PLAYER%d: %s", pl->id, pl->name);
	mvwprintw(info, y + 1, x + 1, "-size: %d bytes", pl->size);
	mvwprintw(info, y + 2, x + 1, "-processes: %d", pl->procs);
	mvwprintw(info, y + 3, x + 1, "-lives: %d", pl->lives);
	mvwprintw(info, y + 4, 3, SEPARATOR);
}

void		put_info(t_global *all, int period)
{
	int		i;
	int		procs;
	int		offset;
	
	offset = period;
	offset = 3 + (all->nb_pl * 5);
	mvwprintw(all->info, 1, 2, "CONTESTANTS:");
	mvwprintw(all->info, 3, 3, SEPARATOR);
	procs = count_procs(all);
	i = -1;
	while (++i < all->nb_pl)
		put_player(all->info, (all->players)[i], 4 + (i * 5), 4);
	mvwprintw(all->info, offset + 3, 2, "Speed limit: %d cycles/sec", SPEED);
	mvwprintw(all->info, offset + 5, 2, "Cycle: %d", all->cycles);
	mvwprintw(all->info, offset + 7, 2, "Total processes: %d", procs);
	//mvwprintw(all->info, offset + 9, 2, "Next check in: %d", period);
	mvwprintw(all->info, offset + 11, 2, "CYCLE_TO_DIE: %d", all->ctd);
	mvwprintw(all->info, offset + 13, 2, "CYCLE_DELTA: %d", CYCLE_DELTA);
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

void		end_ncurses(WINDOW *box)
{
	int		ret;
	getch();
	delwin(box);
	ret = endwin();
	if (ret == ERR)
		ft_printf("ERR\n");
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
	box(all->info, 0, 0);
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
