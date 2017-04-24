#include <ncurses.h>
#include <corewar.h>
#include <stdlib.h>

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		
	wrefresh(local_win);

	return local_win;
}

int		main()
{
	t_global	*all;
	WINDOW		*box;

	all = (t_global*)malloc(sizeof(t_global));
	all->arena= ft_memalloc(MEM_SIZE);
	initscr();
	start_color();			/* Start color 			*/
	init_pair(1, COLOR_RED, COLOR_BLACK);
	refresh();
	box = create_newwin(5, 5, 0, 0);
	wbkgd(box,COLOR_PAIR(1));
	// attron(COLOR_PAIR(1));
	printw("%d\n", 0);
	printw("%d\n", 1);
	printw("%d", 2);
	// attroff(COLOR_PAIR(1));
	printw("%d", 3);
	printw("%d", 4);
	move(4, 0);
	printw("%d", 9);
	getch();
	delwin(box);
	endwin();
	return 0;
}

// int		main()
// {
// 	int ch;

// 	initscr();			/* Start curses mode 		*/
// 	raw();				/* Line buffering disabled	*/
// 	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
// 	noecho();			/* Don't echo() while we do getch */

//     printw("Type any character to see it in bold\n");
// 	while (ch = getch())
// 	{			/* If raw() hadn't been called
// 					 * we have to press enter before it
// 					 * gets to the program 		*/
// 	if(ch == KEY_F(2))
// 	{		/* Without keypad enabled this will */
// 		endwin();			/* End curses mode		  */
// 		exit(0);
// 		// printw("F1 Key pressed");/*  not get to us either	*/
// 					/* Without noecho() some ugly escape
// 					 * charachters might have been printed
// 					 * on screen			*/
// }
// 	else
// 	{	printw("The pressed key is ");
// 		attron(A_BOLD);
// 		printw("%c", ch);
// 		attroff(A_BOLD);
// 	refresh();			/* Print it on to the real screen */
// 	}
// 	}
//     	// getch();			/* Wait for user input */
// 	// endwin();			/* End curses mode		  */
// 	return (0);
// }
