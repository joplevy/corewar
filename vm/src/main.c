/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 17:00:57 by joeyplev          #+#    #+#             */
/*   Updated: 2017/06/30 23:37:31 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int					main(int ac, char **av)
{
	t_global		*global;
	t_list			*args;
	t_opt			*tab;
	struct timespec	speed;

	speed.tv_sec = 0;
	speed.tv_nsec = SPEED;
	tab = opt_tab();
	if (!(global = init_global()))
		exit_msg(global, tab, NULL, E_INIT);
	if (!(args = ft_get_args(ac, av, tab, 'f')))
		exit_msg(global, tab, args, "usg");
	free(tab);
	if (!set_global(args, global))
		exit_msg(global, NULL, args, "usg");
	init_ncurses(global);
	play(global, speed);
	if (global->show == 1)
		end_ncurses(global->box);
	clear_mem(global, NULL, args);
	return (0);
}
