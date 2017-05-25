/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 14:12:41 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/05/25 20:56:28 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	box_put_arena(t_global  *all)
{
	int		i;
	int		x;
	int		y;

	i = -1;
	while (++i < MEM_SIZE)
	{
		x = i % TAB_WIDTH;
		y = i / TAB_WIDTH;
		wmove(all->box, y + 1, (x * 3) + 2);
		wattron(all->box, COLOR_PAIR(all->col[i]));
		wprintw(all->box, "%02x", all->arena[i]);
		wattroff(all->box, COLOR_PAIR(all->col[i]));
	}
	wrefresh(all->box);
}

void	end_ncurses(WINDOW *box)
{
	getch();
	delwin(box);
	endwin();
}

void		color_init(t_global *all)
{
	int		i;
	int		p;
	int		mnp;
	int		imnp;

	if (!(all->col = (ft_memalloc(MEM_SIZE * sizeof(t_col)))))
		return;
	i = -1;
	mnp = MEM_SIZE / all->nb_pl;
	while (++i < MEM_SIZE)
	{
		imnp = i / mnp;
		p = (i == imnp * mnp) ? 2 : 1;
		if (imnp < all->nb_pl && \
			i >= imnp * mnp && i < imnp * mnp + all->players[imnp]->size)
			all->col[i] = (imnp * 2) + p;
		else
			all->col[i] = white_b;
	}
}

void		init_ncurses(t_global *all)
{

	color_init(all);
	initscr();
	curs_set(0);
	refresh();
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_GREEN);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_BLACK, COLOR_RED);
	init_pair(5, COLOR_BLUE, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_BLUE);
	init_pair(7, COLOR_YELLOW, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, COLOR_YELLOW);
	init_pair(9, COLOR_WHITE, COLOR_BLACK);
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
	all->box = newwin(TAB_HEIGHT + 2, (TAB_WIDTH * 3) + 3, 0, 0);
	box(all->box, 0, 0);
}

void		ft_putbinary(char *str, int size)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		ft_printf("%02x ", str[i] & 0xFF);
		if (i + 1 % TAB_WIDTH == 0)
			ft_putchar('\n');
	}
}
