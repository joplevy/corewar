/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 17:00:57 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/06/22 16:17:34 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		{
			ft_lstdelnode(&(global->procs), tmp, NULL);
			// ft_putchar('a');
		}
		else
			LIVE(tmp) = 0;
		tmp = next;
	}
	// ft_putchar('\n');
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
	int			i;

	i = 0;
	tmp = global->procs;
	while (tmp != NULL)
	{
		if (--(TIME(tmp)) == 0)
		{
		//	write(1, "time0\n", 6);
			if (OPC(tmp) > 0 && OPC(tmp) < 17)
			{
		//		write(1, "exec\n", 5);
				instructab[OPC(tmp) - 1](tmp, global);
		//		write(1, "exec\n", 5);
			}
			else
				NEXT(tmp) = (ADR(tmp) + 1) % MEM_SIZE;
		
			global->col[ADR(tmp)] &= 0xF0;
			global->col[NEXT(tmp)] = (global->col[NEXT(tmp)] & 0xF0) | PID(tmp);
			ADR(tmp) = NEXT(tmp);
			OPC(tmp) = global->arena[ADR(tmp)];
			TIME(tmp) = (OPC(tmp) > 0 && OPC(tmp) < 17 ? OP_NBC(OPC(tmp)) : 1);
		//	write(1, "end\n", 4);
		}
		tmp = tmp->next;
		i++;
	}
	// ft_printf("%d\n", i);
}

void			play(t_global *global)
{
	int			cycles;
	int			period;

	cycles = -1;
	period = 0;
	while (++cycles != global->dump && global->procs != NULL)
	{
	//	write(1, "\ntap\n", 5);
		treat_all_procs(global);
	//	write(1, "tap\n", 4);
		if ((++period) >= global->ctd)
		{
	//		write(1, "chk\n", 4);
			check_lives(global);
	//		write(1, "chk\n", 4);
			period = 0;
		}
		if (global->show == 1)
		{
	//		write(1, "show\n", 5);
			box_put_arena(global);
	//		write(1, "show\n", 5);
		}
	}
	if (global->dump == cycles)
	{
		ft_printf("cycles %d\n", cycles);
		ft_putbinary((char *)(global->arena), MEM_SIZE);
	}
	else
	{
		endwin();
		ft_printf("And the winner is : %s !\n\
Sir, do you have anything to say to your fans ?\n-%s\n",\
global->players[-(global->last_id) - 1]->name, \
global->players[-(global->last_id) - 1]->comment);
	}
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
		init_ncurses(global);
	play(global);
	if (global->show == 1)
		end_ncurses(global->box);
	return (0);
}

