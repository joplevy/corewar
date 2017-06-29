/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 17:00:57 by joeyplev          #+#    #+#             */
/*   Updated: 2017/06/30 01:55:05 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int					main(int ac, char **av)
{
	t_global		*global;
	t_list			*args;
	t_list			*tmp;
	t_opt			*tab;
	struct timespec	speed;

	speed.tv_sec = 0;
	speed.tv_nsec = SPEED;
	tab = opt_tab();
	if (!(global = init_global()))
		return (ft_printf("Error during initialization\n"));
	if (!(args = ft_get_args(ac, av, tab, 'f')))
		return (ft_printf(USAGE, USAGE1, USAGE2));
	free(tab);
	if (!set_global(args, global))
		return (ft_printf(USAGE, USAGE1, USAGE2));
	ft_putstr("Introducing contestants...\n");
	tmp = global->procs;
	init_ncurses(global);
	play(global, speed);
	if (global->show == 1)
		end_ncurses(global->box);
	return (0);
}
