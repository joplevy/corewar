/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 21:27:59 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/04/18 22:11:46 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "op.h"
# define ACCESS(TYPE, NODE, ELEM) (((TYPE)((NODE)->data))->(ELEM))

ACCESS("t_process*", glob->procs, "carry");

typedef struct		s_process
{
	int				carry;
	int				live;
	void			regs[REG_NUMBER][REG_SIZE];
	int				current;
	int				cycles;
	int				adress;
	int				params;
}					t_process;

typedef struct		s_player
{
	int				id;
	char			*name;
	char			*comment;
	int				live;
}					t_player;


typedef struct 		s_global
{
	t_list			*procs;
	t_player		players[5];
	void			*arena;
	int				ctd;
	int				lives;
	int				last;
}					t_global;

#endif