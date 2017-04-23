/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 21:27:59 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/04/20 23:30:25 by joeyplevy        ###   ########.fr       */
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
# define ACCESS(TYPE, NODE, ELEM) (((TYPE)((NODE)->data))->(ELEM))

// ACCESS("t_process*", glob->procs, "carry");

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
	char			*name;
	char			*comment;
	char			*code;
}					t_player;


typedef struct 		s_global
{
	t_list			*procs;
	t_player		*players[MAX_PLAYERS + 1];
	void			*arena;
	int				lives;
	int				last;
	int				ctd;
	int				check;
	int				dump;
	int				show;
}					t_global;

#endif