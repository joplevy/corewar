/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 00:27:24 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/30 01:55:33 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void			print_com(char *comment)
{
	int				i;

	i = 1;
	while (++i && comment[i] != '\0')
		ft_putchar(comment[i]);
	ft_putchar('\n');
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

void				treat_all_procs(t_global *global)
{
	t_list		*tmp;

	tmp = global->procs;
	while (tmp != NULL)
	{
		if (--(TIME(tmp)) == 0)
		{
			if (OPC(tmp) > 0 && OPC(tmp) < 17 && NEXT(tmp) \
				!= ((ADR(tmp) + 1) % MEM_SIZE))
				g_instructab[OPC(tmp) - 1](tmp, global);
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

void				announce_winner(t_global *gb)
{
	int				i;
	t_player		*winner;

	if (gb->show)
		endwin();
	winner = NULL;
	i = -1;
	while (++i < gb->nb_pl)
	{
		if (((gb->players)[i])->id == gb->last_id)
		{
			winner = (gb->players)[i];
			break ;
		}
	}
	if (!winner)
		ft_printf("No winner for this match!\n");
	else
	{
		ft_printf("And the winner is : %s!\n", winner->name);
		ft_printf("Sir, do you have anything to say to your fans ?\n");
		print_com(gb->players[-(gb->last_id) - 1]->comment);
	}
}

void				play(t_global *global, struct timespec speed)
{
	int				cycles;
	int				period;

	cycles = -1;
	period = 0;
	while (++cycles != global->dump && global->procs != NULL)
	{
		treat_all_procs(global);
		if ((++period) >= global->ctd)
		{
			check_lives(global);
			period = 0;
		}
		if (global->show == 1)
		{
			box_put_arena(global);
			nanosleep(&speed, &speed);
		}
	}
	if (global->dump == cycles)
		ft_putbinary((char *)(global->arena), MEM_SIZE);
	else
		announce_winner(global);
}
