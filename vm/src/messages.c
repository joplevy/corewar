/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 18:15:32 by rvan-der          #+#    #+#             */
/*   Updated: 2017/07/03 19:40:28 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void				print_usage(void)
{
	ft_printf("./corewar [(-p x) player.cor]...\n");
	ft_printf("-p x\tset next player as x\n");
	ft_printf("\n-n\tset ncurses mode\n-v\tset verbose mode\n");
	ft_printf("-dump x\tdump memory after x cycles\n");
}

void				exit_msg(t_global *gb, t_opt *tab, t_list *ag, char *msg)
{
	clear_mem(gb, tab, ag);
	if (msg != NULL)
	{
		if (ft_strequ(msg, "usg"))
			print_usage();
		else
			ft_printf(msg);
	}
	exit(0);
}

void				introduce(t_player **players)
{
	int				i;

	ft_printf("Introducing contestants...\n");
	i = -1;
	while (players[++i] != NULL)
		ft_printf("Player number %d: %s!\n", i + 1, players[i]->name);
	ft_printf("...\n...\n");
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
		ft_printf("-Sir, do you have anything to say to your fans ?\n");
		ft_printf("-%s\n", (winner->comment) + 2);
	}
}
