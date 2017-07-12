/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 19:21:41 by rvan-der          #+#    #+#             */
/*   Updated: 2017/06/30 21:33:58 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void			delete_players(t_player **players)
{
	int			i;

	i = -1;
	while (players[++i] != NULL)
		ft_memdel((void**)(&(players[i])));
}

void			clear_mem(t_global *gb, t_opt *tab, t_list *args)
{
	if (gb != NULL)
	{
		ft_lstfree(&(gb->procs), &ft_memdel);
		ft_memdel((void**)(&(gb->col)));
		delete_players((t_player**)(gb->players));
		free(gb);
	}
	ft_memdel((void**)(&tab));
	ft_lstfree(&args, &ft_memdel);
}
