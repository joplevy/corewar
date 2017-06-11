/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 21:46:00 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/05/30 20:18:31 by joeyplevy        ###   ########.fr       */
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

int				init_new_proc(t_global *gb, int pos)
{
	t_process	proc;
	t_list		*new;
	int			i;
	int			j;

	proc.carry = 0;
	proc.live = 0;
	proc.opc = gb->arena[pos % MEM_SIZE];
	proc.time = (proc.opc > 0 && proc.opc < 17) ? OP_NBC(proc.opc) : 1;
	proc.adress = pos;
	i = -1;
	j = -1;
	while (++i < REG_NUMBER)
		while (++j < REG_SIZE)
			(proc.regs)[i][j] = 0;
	if (!(new = ft_lstnew(&proc, sizeof(t_process))))
		return (0);
	ft_lstadd(&(gb->procs), new);
	return (1);
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
		ft_memcpy((void*)(gb->arena + pos), \
					(const void*)((gb->players)[i])->code, \
					(size_t)((gb->players)[i])->size);
		if (!init_new_proc(gb, pos))
			return (0);
	}
 	return (1);
}
