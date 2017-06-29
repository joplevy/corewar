/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 05:07:52 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/29 19:35:56 by niludwig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int				get_type_siz(int type, int label_size)
{
	if (type == T_IND)
		return (IND_SIZE);
	if (type == T_DIR)
		return (DIR_SIZE / (label_size + 1));
	if (type == T_REG)
		return (1);
	return (0);
}

int				get_ptype(unsigned char ocp, int pos)
{
	int			cp;

	cp = ocp >> (6 - (pos * 2));
	if ((cp & 0x03) == IND_CODE)
		return (T_IND);
	if ((cp & 0x03) == DIR_CODE)
		return (T_DIR);
	if ((cp & 0x03) == REG_CODE)
		return (T_REG);
	return (0);
}

int				get_relative(int adr, int inc, int mod)
{
	int			ret;

	inc = (mod) ? inc % IDX_MOD : inc;
	ret = adr + inc;
	while (ret < 0)
		ret += MEM_SIZE;
	return (ret % MEM_SIZE);
}

int				ft_get_params(unsigned char *arena, int adr, t_list *p)
{
	int			inst;
	int			i;
	int			ptr;
	int			len;

	ft_bzero(PAR(p), sizeof(t_param) * 3);
	inst = arena[adr];
	i = -1;
	ptr = (adr + 2) % MEM_SIZE;
	while (++i < g_op_tab[inst - 1].nb_param)
	{
		if ((PAR(p)[i].type = g_op_tab[inst - 1].param[i] \
			& get_ptype(arena[(adr + 1) % MEM_SIZE], i)) == 0)
			return (0);
		if (!(len = get_type_siz(PAR(p)[i].type,
			g_op_tab[inst - 1].label_size)))
			return (0);
		if (PAR(p)[i].type == T_REG)
			if (!(PAR(p)[i].reg = ft_get_reg_nb(arena, ptr)))
				return (0);
		PAR(p)[i].val = (PAR(p)[i].type == T_REG)
			? ft_get_reg_val(p, PAR(p)[i].reg) : ft_get_int(arena, ptr, len);
		ptr = (ptr + len) % MEM_SIZE;
	}
	return (ptr);
}
