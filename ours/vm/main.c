/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 17:00:57 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/05/30 20:23:34 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

#include <corewar.h>

void			check_lives(t_global *global)
{
	t_list		*tmp;
	t_list		*next;

	tmp = global->procs;
	while (tmp != NULL)
	{
		next = tmp->next;
		if (!LIVE(tmp))
			ft_lstdelnode(&(global->procs), tmp, NULL);
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

void			treat_all_procs(t_global *global)
{
	t_list		*tmp;
	int 		lenght;

	tmp = global->procs;
	while (tmp != NULL)
	{
		TIME(tmp)--;
		if (TIME(tmp) == 0)
		{
			exec_instruction(tmp, global);
			lenght = get_params_lenght(ADR(tmp), global->arena);
			if (global->show == 1)
			{
				global->col[ADR(tmp)] -= 1;
				global->col[(ADR(tmp) + lenght) % MEM_SIZE] += 1;
			}
			ADR(tmp) = (ADR(tmp) + lenght) % MEM_SIZE;
			OPC(tmp) = global->arena[ADR(tmp)];
			TIME(tmp) = (OPC(tmp) > 0 && OPC(tmp) < 17) ? OP_NBC(OPC(tmp)) : 1;
		}
		tmp = tmp->next;
	}
}

void			play(t_global *global)
{
	int			cycles;
	int			period;

	cycles = -1;
	period = 0;
	while (++cycles != global->dump + 1 && global->procs != NULL)
	{
		period += 1;
		treat_all_procs(global);
		if (period == global->ctd)
		{
			check_lives(global);
			period = 0;
		}
		if (global->show == 1)
			box_put_arena(global);
	}
	if (global->dump > 0)
		ft_putbinary((char *)(global->arena), MEM_SIZE);
	else
		ft_putendl("youpi");
		// show_winner(global);
}

int			main(int ac, char **av)
{
	t_global	*global;
	t_list		*args;
	t_list		*tmp;
	t_opt		*tab;

	tab = opt_tab();
	if (!(global = init_global()))
		return (0);
	if (!(args = ft_get_args(ac, av, tab, 'f')))
		return (0);
	free(tab);
	if (!set_global(args, global))
		return (0);
	tmp = global->procs;

	if (global->show == 1)
		init_ncurses(global);
	play(global);
	if (global->show == 1)
		end_ncurses(global->box);
	return (0);
}

