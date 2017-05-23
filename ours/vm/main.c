/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 17:00:57 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/05/23 19:16:42 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>
#include <stdio.h>

t_opt		*opt_tab(void)
{
	t_opt		*ret;

	if ((ret = (t_opt*)malloc(sizeof(t_opt) * 4)) == NULL)
		return (NULL);
	(ret[0]).name = "p";
	(ret[0]).args = "if";
	(ret[1]).name = "n";
	(ret[1]).args =  "";
	(ret[2]).name = "dump";
	(ret[2]).args = "i";
	(ret[3]).name = "";
	(ret[3]).args = "";
	return (ret);
}

t_global	*init_global()
{
	t_global	*ret;
	int			i;

	if (!(ret = (t_global*)malloc(sizeof(t_global))))
		return (NULL);
	if (!(ret->arena = ft_memalloc(MEM_SIZE)))
		return (NULL);
	ret->procs = NULL;
	i = -1;
	while (++i < MAX_PLAYERS)
		ret->players[i] = NULL;
	ret->lives = 0;
	ret->last_id = 0;
	ret->ctd = CYCLE_TO_DIE;
	ret->checks = 0;
	ret->dump = -2;
	ret->show = 0;
	ret->nb_arg = 0;
	ret->nb_pl = 0;
	return (ret);
}

int				load_players(t_global *gb)
{
	int			i;
	int			pos;
	int			modulo;

	pos = -1 * (MEM_SIZE  / gb->nb_pl);
	modulo = MEM_SIZE % gb->nb_pl;
	i = -1;
	while (++i < gb->nb_pl)
	{
		pos += (MEM_SIZE / gb->nb_pl);
		if (modulo && pos)
		{
			pos++;
			modulo--;
		}
		ft_memcpy((void*)(gb->arena + pos), \
					(const void*)((gb->players)[i])->code, \
					(size_t)((gb->players)[i])->size);
	}
 //		i = -1;
 // 	while ((gb->players)[++i] != NULL)
 // 		if (!intit_new_proc((gb->players)[i], &(gb->procs)))
 // 			return (0);
 	return (1);
}

int			main(int ac, char **av)
{
	t_global	*global;
	t_list		*args;
	t_opt		*tab;

	tab = opt_tab();
	if (!(global = init_global()))
		return (0);
	if (!(args = ft_get_args(ac, av, tab, 'f')))
		return (0);
	free(tab);
	if (!set_global(args, global))
		return (0);
	if (global->show == 1)
	{
		init_ncurses(global);
		box_put_arena(global);
		end_ncurses(global->box);
	}
	return (0);
}
