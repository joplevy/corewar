/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 21:46:00 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/06/29 22:46:43 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

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
	ret->nb_pl = 0;
	return (ret);
}

int				init_new_proc(t_global *gb, int pos, int id)
{
	t_process	proc;
	t_list		*new;
	int			i;
	int			j;

	proc.pid = -id;
	proc.carry = 0;
	proc.live = 0;
	proc.opc = gb->arena[pos % MEM_SIZE];
	proc.time = (proc.opc > 0 && proc.opc < 17) ? OP_NBC(proc.opc) : 1;
	proc.adress = pos;
	proc.next = 0;
	i = -1;
	while (++i < REG_NUMBER && (j = -1))
		while (++j < REG_SIZE)
			(proc.regs)[i][j] = 0;
	ft_int_write((unsigned char*)(proc.regs[0]), 0, id, 4);
	if (!(new = ft_lstnew(&proc, sizeof(t_process))))
		return (0);
	NEXT(new) = (OPC(new) > 0 && OPC(new) < 17) ? \
		ft_get_params(gb->arena, new) : (ADR(new) + 1) % MEM_SIZE;
	ft_lstadd(&(gb->procs), new);
	return (1);
}
