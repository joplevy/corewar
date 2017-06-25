/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 03:41:40 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/25 21:07:00 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void				ft_lfork(t_list *p, t_global *gb)
{
	t_list	*new;
	short	jump;

	NEXT(p) = (ADR(p) + 3) % MEM_SIZE;
	if (!(new = ft_lstnew((t_process *)(p->content), sizeof(t_process))))
		return;
	ft_lstadd(&(gb->procs), new);
	jump = (short)ft_get_int(gb->arena, (ADR(p) + 1) % MEM_SIZE, 2);
	ADR(new) = get_relative(ADR(p), jump, 0);
	gb->col[ADR(new)] = (gb->col[ADR(new)] & 0xF0) | PID(p);
	OPC(new) = gb->arena[ADR(new)];
	CARRY(p) = 1;
	if (OPC(new) > 0 && OPC(new) < 17)
		TIME(new) = OP_NBC(OPC(new));
	else
		TIME(new) = 1;
}
