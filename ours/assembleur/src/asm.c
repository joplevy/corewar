/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niludwig <niludwig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 15:10:26 by niludwig          #+#    #+#             */
/*   Updated: 2017/06/20 02:27:36 by niludwig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static void		ft_pars_arg(int ac, char **av)
{
	if (ac == 1)
		ft_exit_msg("Usage: ./asm <sourcefile.s>");
	else if (ac == 2)
	{
		if (av[ac - 1][ft_strlen(av[ac - 1]) - 1] != 's'
			&& av[ac - 1][ft_strlen(av[ac - 1]) - 2] != '.')
			ft_exit_msg("Wrong format files.\nUsage: ./asm <sourcefile.s>");
	}
	else if (ac > 2)
		ft_exit_msg("Too many files.\nUsage: ./asm <sourcefile.s>");
}

int				main(int ac, char **av)
{
	t_asm		*asmb;
	char		*ret;
	int			i;

	ft_pars_arg(ac, av);
	if (!(asmb = (t_asm*)malloc(sizeof(t_asm))))
		ft_exit_msg("Error in malloc");
	if (!(asmb->f_content = ft_get_file_content(av[ac - 1])))
		ft_exit_msg(ft_strjoin("Can't read source file ", av[ac - 1]));
	asmb->labels = NULL;
	asmb->labdirs = NULL;
	if (!(i = asm_parse_header(asmb)))
		ft_exit_msg("Error in header");
	i = asmb->idx;
	if (!asm_parse_body(asmb))
		ft_exit_msg("Error in body");
	if (!asm_finalize(av[ac - 1], asmb, i))
		ft_exit_msg("Can't create the .cor file");
	ret = get_file_name(av[ac - 1]);
	ft_printf("Writing output program to %s\n", ret);
	free(ret);
	return (1);
}
