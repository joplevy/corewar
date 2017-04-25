/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 20:50:10 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/04/25 23:35:19 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			check_lives(t_global *global, int *cycles)
{
	t_list		*tmp;

	tmp = global->procs;
	while (tmp != NULL)
		if (!ACC(tmp, live))
			delete_process(global->procs, tmp);
	if (global->lives > NBR_LIVE || global->checks == MAX_CHECKS)
	{
		global->ctd -= CYCLE_DELTA;
		global->checks = 0;
		*cycles = 0;
	}
	global->lives = 0;
}

void			treat_all_procs(t_global *global)
{
	t_list		*tmp;

	tmp = global->procs;
	while (tmp != NULL)
	{
		if (ACC(tmp, wait) == 1)
		{
			exec_instruction(tmp, global);
			go_to_next((t_player*)(tmp->content), global->arena);
		}
		else if (ACC(tmp, wait) > 0)
			ACC(tmp, wait) -= 1;
		tmp = tmp->next;
	}
}

void			play(t_global *global)
{
	int			cycles;

	cycles = -1;
	while (++cycles != global->dump + 1 && global->procs != NULL)
	{
		treat_procs(global);
		if (cycles > 0 && !(cycles % global->ctd))
			check_lives(global, &cycles);
	}
	if (global->dump > 0)
		dump_arena(global->arena);
	else
		show_winner(global);
}
