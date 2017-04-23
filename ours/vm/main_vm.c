/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 21:52:53 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/04/21 19:32:26 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int				main(int argc, char **argv)
{
	t_global		*global;

	if (argc == 1 || (global = init_global()) == NULL || \
		!set_global(argc, argv, global))
		return (main_error(&global));
	play(global);
	clear_main(&global);
	return (0);
}