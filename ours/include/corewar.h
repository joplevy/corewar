/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 21:27:59 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/05/04 23:19:48 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include <errno.h>
# include <limits.h>
# include <fcntl.h>
# include <libft.h>
# include <op.h>
# include <ft_printf.h>
# define ACC(NODE, ELEM) (((t_process*)((NODE)->content))->(ELEM))
# define TAB_HEIGHT 64
# define TAB_WIDTH 64

// ACC("t_process*", glob->procs, "carry");

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
	char			*name;
	char			*comment;
	char			*code;
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
}					t_global;

#endif
