/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 17:00:57 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/05/25 21:46:29 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

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
	{
		init_ncurses(global);
		box_put_arena(global);
		end_ncurses(global->box);
	}
	return (0);
}
