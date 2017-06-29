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

void		box_put_arena(t_global *all)
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
	wrefresh(all->box);
}

void		end_ncurses(WINDOW *box)
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
