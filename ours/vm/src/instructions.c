/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 19:54:59 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/25 04:07:58 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int					ft_get_int(unsigned char *arena, int adr, int size)
{
	int		ret;
	int		i;

	ret = 0;
	i = -1;
	while (++i < size)
		ret += arena[(adr + i) % MEM_SIZE] << ((size - (i + 1)) * 8);
	return (ret);
}

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

int					get_ptype(unsigned char ocp, int pos)
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

void			ft_int_write(unsigned char *arena, int adr, int val, int size)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		arena[(adr + i) % MEM_SIZE] = (val >> ((size - (i + 1)) * 8)) & 0xFF;
	}
}

int				ft_get_reg_nb(unsigned char *arena, int adr)
{
	int		ret;

	ret = ft_get_int(arena, adr, 1);
	return ((ret > 0 && ret <= REG_NUMBER) ? ret : 0);
}

int				ft_get_reg_val(t_list *p, int reg)
{
	return (ft_get_int((unsigned char *)(REG(p)[reg - 1]), 0, REG_SIZE));
}

void			ft_reg_write(t_list *p, int reg, int val)
{
	ft_int_write((unsigned char *)(REG(p)[reg - 1]), 0, val, REG_SIZE);
}

int				ft_get_params(unsigned char *arena, int adr, t_list *p)
{
	int 		inst;
	int 		i;
	int 		ptr;
	int 		len;

	ft_bzero(PAR(p), sizeof(t_param) * 3);
	inst = arena[adr];
	i = -1;
	ptr = (adr + 2) % MEM_SIZE;
	while (++i < g_op_tab[inst - 1].nb_param)
	{
		if ((PAR(p)[i].type = g_op_tab[inst - 1].param[i] \
			& get_ptype(arena[(adr + 1) % MEM_SIZE], i)) == 0)
			return (0);
		if (!(len = get_type_siz(PAR(p)[i].type, g_op_tab[inst - 1].label_size)))
			return (0);
		if (PAR(p)[i].type == T_REG)
			if (!(PAR(p)[i].reg = ft_get_reg_nb(arena, ptr)))
				return(0);
		PAR(p)[i].val = (PAR(p)[i].type == T_REG) ? ft_get_reg_val(p, PAR(p)[i].reg) : 
			ft_get_int(arena, ptr, len);
		ptr = (ptr + len) % MEM_SIZE;
	}
	return (ptr);
}

int				get_relative(int adr, int inc, int mod)
{
	int				ret;

	inc = (mod) ? inc % IDX_MOD : inc;
	ret = adr + inc;
	while (ret < 0)
		ret += MEM_SIZE;
	return (ret % MEM_SIZE);
}
