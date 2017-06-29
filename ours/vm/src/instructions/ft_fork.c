/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 03:41:19 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/29 22:00:09 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void				ft_fork(t_list *p, t_global *gb)
{
	t_list	*new;

	if (!(new = ft_lstnew((t_process *)(p->content), sizeof(t_process))))
		return;
	new->next = p->next;
	p->next = new;
	ADR(new) = get_relative(ADR(p), PAR(p)[0].val, 1);
	gb->col[ADR(new)] = (gb->col[ADR(new)] & 0xF0) | PID(p);
	OPC(new) = gb->arena[ADR(new)];
	TIME(new) = (OPC(new) > 0 && OPC(new) < 17 ? OP_NBC(OPC(new)) : 1);
	NEXT(new) = (OPC(new) > 0 && OPC(new) < 17) ? \
	ft_get_params(gb->arena, new) : (ADR(new) + 1) % MEM_SIZE;
}
