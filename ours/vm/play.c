/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 20:50:10 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/04/23 17:55:49 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			treat_all_procs(t_global *global)
{
	t_list		*tmp;

	tmp = global->procs;
	while (tmp != NULL)
		
	{
		if (ACCESS(tmp, wait))
	}
}

void			play(t_global *global)
{
	int			cycles;

	cycles = -1;
	while (++cycles != global->dump + 1 && global->procs != NULL)
	{
		treat_procs(global);
		if (cycles > 0 && cycles % global->ctd)
			check_lives(global);
	}
	if (global->dump > 0)
		dump_arena(global->arena);
	else
		show_winner(global);
}
