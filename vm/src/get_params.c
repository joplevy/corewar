/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 05:07:52 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/30 01:49:36 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int			get_type_siz(int type, int label_size)
{
	if (type == T_IND)
		return (IND_SIZE);
	if (type == T_DIR)
		return (DIR_SIZE / (label_size + 1));
	if (type == T_REG)
		return (1);
	return (0);
}

int			get_ptype(unsigned char ocp, int pos)
{
	int		cp;

	cp = ocp >> (6 - (pos * 2));
	if ((cp & 0x03) == IND_CODE)
		return (T_IND);
	if ((cp & 0x03) == DIR_CODE)
		return (T_DIR);
	if ((cp & 0x03) == REG_CODE)
		return (T_REG);
	return (0);
}

int			get_relative(int adr, int inc, int mod)
{
	int		ret;

	inc = (mod) ? inc % IDX_MOD : inc;
	ret = adr + inc;
	while (ret < 0)
		ret += MEM_SIZE;
	return (ret % MEM_SIZE);
}

int			ft_get_data(unsigned char *arena, t_list *p, int ptr, t_param *dt)
{
	int		len;
	int		adr;
	int		ls;

	ls = g_op_tab[OPC(p) - 1].label_size;
	if (!(len = get_type_siz(dt->type, ls)))
		return (0);
	if (dt->type == T_REG)
	{
		if (!(dt->reg = ft_get_reg_nb(arena, ptr)))
			return (0);
		dt->val = ft_get_reg_val(p, dt->reg);
	}
	else if (dt->type == T_IND)
	{
		dt->reg = (short)ft_get_int(arena, ptr, len);
		adr = get_relative(ADR(p), dt->reg, \
		(OPC(p) >= 13 && OPC(p) <= 15) ? 0 : 1);
		dt->val = (ls) ? (short)ft_get_int(arena, adr, 2) : \
			ft_get_int(arena, adr, 4);
	}
	else
		dt->val = (ls) ? (short)ft_get_int(arena, ptr, len) : \
			ft_get_int(arena, ptr, len);
	return (len);
}

int			ft_get_params(unsigned char *arena, t_list *p)
{
	int		inst;
	int		i;
	int		ptr;
	int		len;

	ft_bzero(PAR(p), sizeof(t_param) * 3);
	inst = arena[ADR(p)];
	ptr = (g_op_tab[inst - 1].ocp) ? (ADR(p) + 2) % MEM_SIZE : \
		(ADR(p) + 1) % MEM_SIZE;
	i = -1;
	while (++i < g_op_tab[inst - 1].nb_param)
	{
		if (g_op_tab[inst - 1].ocp)
		{
			if ((PAR(p)[i].type = g_op_tab[inst - 1].param[i] \
				& get_ptype(arena[(ADR(p) + 1) % MEM_SIZE], i)) == 0)
				return (ADR(p) + 1) % MEM_SIZE;
		}
		else
			PAR(p)[i].type = g_op_tab[inst - 1].param[i];
		if (!(len = ft_get_data(arena, p, ptr, &(PAR(p)[i]))))
			return (ADR(p) + 1) % MEM_SIZE;
		ptr = (ptr + len) % MEM_SIZE;
	}
	return (ptr);
}
