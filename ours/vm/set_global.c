/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_global.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 21:31:47 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/04/25 23:25:25 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static int		check_double(t_player **players)
{
	int			i;
	int			j;

	i = -1;
	while (players[++i] != NULL)
	{
		j = i;
		while ((players[i])->id != 0 && players[++j] != NULL)
			if ((players[j])->id == (players[i])->id)
				return (0);
	}
	return (1);
}

int				set_players_id(t_player **players)
{
	int			i;
	int			j;
	int			pid;

	if (!check_double(players))
		return (0);
	i = -1;
	pid = 1;
	while (players[++i] != NULL)
		if (!(players[i])->id)
		{
			j = -1;
			while (players[++j] != NULL)
				if (i != j && (players[j])->id == pid)
				{
					pid++;
					j = -1;
				}
			(players[i])->id = pid;
		}
	return (1);
}

int				get_player(t_global *global, int pid, t_list *list)
{
	int			i;
	t_parg		*arg;

	arg = (t_parg*)(list->content);
	if (arg->fd <= 0 || pid <= 0)
		return(0);
	//	return(open_error(arg));
	i = 0;
	while ((global->players)[i] != NULL)
		i++;
	if (((global->players)[i] = malloc(sizeof(t_player))) == NULL)
	{
		close(arg->fd);
		return (0);
	}
	//	return (malloc_err());
	((global->players)[i])->id = pid;
	if (!get_info_player(arg->fd, (global->players)[i]))
	{
		close(arg->fd);
		return (0);
	}
	close(arg->fd);
	return (1);
}

int			set_global(t_list *args, t_global *gb)
{
	t_list	*a;

	a = args;
	while (a != NULL)
	{
		if (((t_parg*)(a->content))->type == opt)
		{
			if (ft_strequ(((t_parg*)a->content)->opt, "dump") && (a = a->next))
				gb->dump = ((t_parg*)a->content)->val;
			else if (ft_strequ(((t_parg*)a->content)->opt, "n"))
				gb->show = 1;
			else if (++(gb->nb_pl) > MAX_PLAYERS || !get_player(gb, \
						((t_parg*)(a->next->content))->val, a->next->next) || \
						!(a = a->next->next))
				return (0);
		}
		else if (++(gb->nb_pl) > MAX_PLAYERS || !get_player(gb, 0, a))
			return (0);
		a = a->next;
	}
	if (!set_players_id((t_player**)gb->players) || !load_players(gb))
		return (0);
	return (1);
}
