/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 21:02:48 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/05/13 18:16:13 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <corewar.h>
#include <stdlib.h>

void	box_put_arena(t_global  *all, WINDOW *box)
{
	int		i;
	int		x;
	int		y;

	i = -1;
	while (++i < MEM_SIZE)
	{
		x = i % TAB_WIDTH;
		y = i / TAB_WIDTH;
		wmove(box, y + 1, (x * 3) + 2);
		wattron(box, COLOR_PAIR(all->col[i]));
		wprintw(box, "%02x", all->arena[i]);
		wattroff(box, COLOR_PAIR(all->col[i]));
	}
	wrefresh(box);
}

t_col	*color_init()
{
	t_col	*ret;
	int		i;

	if (!(ret = (ft_memalloc(MEM_SIZE * sizeof(t_col)))))
		return (NULL);
	i = -1;
	while (++i < MEM_SIZE)
		ret[i] = yellow_b;
	return (ret);
}

int		main()
{
	t_global	*all;
	WINDOW		*box;

	all = (t_global*)malloc(sizeof(t_global));
	all->arena = ft_memalloc(MEM_SIZE);
	all->arena[5] = 7;
	all->arena[7] = 17;
	all->arena[0] = 207;
	all->col = color_init();
	initscr();
	curs_set(0);
	refresh();
	start_color();			/* Start color 			*/
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
	box = newwin(TAB_HEIGHT + 2, (TAB_WIDTH * 3) + 3, 0, 0);
	box(box, 0, 0);
	box_put_arena(all, box);
	// attron(COLOR_PAIR(1));
	// wmove(box, 1, 1);
	// wprintw(box, "%d", 0);
	// wprintw(box, "%d", 1);
	// wprintw(box, "%d", 2);
	// wrefresh(box);
	// attroff(COLOR_PAIR(1));
	getch();
	delwin(box);
	endwin();
	return 0;
}
