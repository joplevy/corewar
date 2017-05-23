/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 21:27:59 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/05/23 18:56:45 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include <errno.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <ncurses.h>
# include <stdlib.h>
# include <libft.h>
# include <op.h>
# define ACC(NODE, ELEM) (((t_process*)((NODE)->content))->(ELEM))
// ACC("t_process*", glob->procs, "carry");
# define TAB_HEIGHT 64
# define TAB_WIDTH 64

typedef enum	e_col
{
	green_b=1,
	b_green,
	red_b,
	b_red,
	blue_b,
	b_blue,
	yellow_b,
	b_yellow,
	white_b,
	b_white,
}				t_col;

typedef struct		s_process
{
	char			player;
	int				carry;
	int				live;
	unsigned char	regs[REG_NUMBER][REG_SIZE];
	int				current;
	int				cycles;
	int				adress;
	int				params;
}					t_process;

typedef struct		s_player
{
	int				id;
	int				live;
	int				size;
	int				entry;
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	char			code[CHAMP_MAX_SIZE];
}					t_player;


typedef struct 		s_global
{
	t_list			*procs;
	t_player		*players[MAX_PLAYERS + 1];
	unsigned char	*arena;
	t_col			*col;
	WINDOW			*box;
	int				lives;
	int				last_id;
	int				ctd;
	int				checks;
	int				period;
	int				dump;
	int				show;
	int				nb_arg;
	int 			nb_pl;
}					t_global;

/*
**	vm
*/
/*
**		get_info.c
*/

int					get_info_player(int fd, t_player *player);

/*
**		affichage.c
*/

void				init_ncurses(t_global *all);
void				end_ncurses(WINDOW *box);
void				box_put_arena(t_global  *all);
void				ft_putbinary(char *str, int size);

/*
**		set_global.c
*/

int					set_global(t_list *args, t_global *gb);

/*
**		load_player.c
*/

int					load_players(t_global *gb);

#endif
