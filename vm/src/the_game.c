/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 00:27:24 by jplevy            #+#    #+#             */
/*   Updated: 2017/07/03 18:22:01 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int					is_lastpc(t_list *procs, int adr)
{
	int				n;
	t_list			*tmp;

	n = 0;
	tmp = procs;
	while (tmp != NULL)
	{
		if (ADR(tmp) == adr)
			n++;
		tmp = tmp->next;
	}
	return (n > 1 ? 0 : 1);
}

void				check_lives(t_global *global)
{
	t_list			*tmp;
	t_list			*next;

	tmp = global->procs;
	while (tmp != NULL)
	{
		next = tmp->next;
		if (!LIVE(tmp))
		{
			if (is_lastpc(global->procs, ADR(tmp)))
				global->col[ADR(tmp)] &= 0xF0;
			ft_lstdelnode(&(global->procs), tmp, NULL);
		}
		else
			LIVE(tmp) = 0;
		tmp = next;
	}
	if (global->lives > NBR_LIVE || global->checks == MAX_CHECKS)
	{
		global->ctd -= CYCLE_DELTA;
		global->checks = 0;
	}
	else
		global->checks += 1;
	global->lives = 0;
}

void				treat_all_procs(t_global *global)
{
	t_list			*tmp;

	tmp = global->procs;
	while (tmp != NULL)
	{
		if (--(TIME(tmp)) == 0)
		{
			if (OPC(tmp) > 0 && OPC(tmp) < 17 && NEXT(tmp) \
				!= ((ADR(tmp) + 1) % MEM_SIZE))
				g_instructab[OPC(tmp) - 1](tmp, global);
			if (is_lastpc(global->procs, ADR(tmp)))
				global->col[ADR(tmp)] &= 0xF0;
			global->col[NEXT(tmp)] = (global->col[NEXT(tmp)] & 0xF0) | PID(tmp);
			ADR(tmp) = NEXT(tmp);
			OPC(tmp) = global->arena[ADR(tmp)];
			TIME(tmp) = (OPC(tmp) > 0 && OPC(tmp) < 17 ? OP_NBC(OPC(tmp)) : 1);
			NEXT(tmp) = (OPC(tmp) > 0 && OPC(tmp) < 17) ? \
			ft_get_params(global->arena, tmp) : (ADR(tmp) + 1) % MEM_SIZE;
		}
		tmp = tmp->next;
	}
}

void				play(t_global *global, struct timespec speed)
{
	int				period;

	if (!(global->show))
		introduce((t_player**)(global->players));
	period = 0;
	while (++(global->cycles) != global->dump && global->procs != NULL)
	{
		treat_all_procs(global);
		if ((++period) >= global->ctd)
		{
			check_lives(global);
			period = 0;
		}
		if (global->show == 1)
			box_put_arena(global, speed, period);
	}
	if (global->dump == global->cycles)
		ft_putbinary((char *)(global->arena), MEM_SIZE);
	else if (global->show)
		end_ncurses(global);
	else
		announce_winner(global);
}
