/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 21:27:59 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/05/12 20:17:22 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include <errno.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <libft.h>
# include <op.h>
# include <ft_printf.h>
# define ACC(NODE, ELEM) (((t_process*)((NODE)->content))->(ELEM))
// ACC("t_process*", glob->procs, "carry");
# define TAB_HEIGHT 64
# define TAB_WIDTH 64

typedef enum	e_vmtype
{
	dir = 0,
	ind,
	reg
}

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
	b_white
}				t_col;

typedef struct		s_process
{
	char			player;
	int				carry;
	int				live;
	int				regs[REG_NUMBER];
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
	int				pos;
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

int					get_info_player(int fd, t_player *player);
void				ft_putbinary(char *str, int size);
int					set_global(t_list *args, t_global *gb);
int					load_players(t_global *gb);

#endif
