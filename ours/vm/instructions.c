/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 19:54:59 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/17 00:55:19 by jplevy           ###   ########.fr       */
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
		arena[adr + i] = (val >> ((size - (i + 1)) * 8)) & 0xFF;
	}
}

int				ft_get_reg_nb(unsigned char *arena, int adr)
{
	int		ret;

	ret = ft_get_int(arena, adr, 1);
	return ((ret > 0 && ret <= REG_NUMBER) ? ret : 0);
}

int				ft_get_reg(t_list *p, int reg)
{
	return (ft_get_int((unsigned char *)(REG(p)[reg - 1]), 0, REG_SIZE));
}

void			ft_reg_write(t_list *p, int reg, int val)
{
	ft_int_write((unsigned char *)(REG(p)[reg - 1]), 0, val, REG_SIZE);
}

int				ft_get_params(unsigned char *arena, int adr, t_param **par, t_list *p)
{
	int 		inst;
	int 		i;
	int 		ptr;
	int 		len;

	inst = arena[adr];
	i = -1;
	ptr = adr + 2;
	while (++i < g_op_tab[inst - 1].nb_param)
	{
		if (!((*par)[i].type = g_op_tab[inst - 1].param[i] \
			& get_ptype(arena[adr + 1], i)))
			return (0);
		len = get_type_siz((*par)[i].type, g_op_tab[inst - 1].label_size);
		if ((*par)[i].type == T_REG && \
			!((*par)[i].reg = ft_get_reg_nb(arena, ptr)))
			return (0);
		(*par)[i].val = ((*par)[i].type == T_REG) ? ft_get_reg(p, (*par)[i].reg) : 
			ft_get_int(arena, ptr, len);
		ptr += len;
	}
	return (ptr);
}

/*
** instructions 
*/

void				ft_live(t_list *p, t_global *gb)
{
	int		id;

	id = ft_get_int(gb->arena, ADR(p) + 1, 4);
	if (id < 0 && id > -5)
		gb->last_id = id;
	LIVE(p)++;
	NEXT(p) = (ADR(p) + 5) % MEM_SIZE;
}

void				ft_ld(t_list *p, t_global *gb)
{
	int		adress;
	int		val;
	char	t1;
	int		r2;
	
	t1 = get_ptype(gb->arena[ADR(p) + 1], 0);
	if ((t1 == T_DIR || t1 == T_IND) && \
		get_ptype(gb->arena[ADR(p) + 1], 1) == T_REG)
	{
		adress = (t1 == T_DIR) ? (ADR(p) + 2) % MEM_SIZE : \
			(ADR(p) + (ft_get_int(gb->arena, \
			ADR(p) + 2, IND_SIZE) % IDX_MOD)) % MEM_SIZE;
		val = ft_get_int(gb->arena, adress, REG_SIZE);
		if ((r2 = ft_get_reg_nb(gb->arena, \
			(ADR(p) + 2 + get_type_siz(t1, 0)) % MEM_SIZE)))
		{
			ft_reg_write(p, r2, val);
			NEXT(p) = (ADR(p) + 3 + get_type_siz(t1, 0)) % MEM_SIZE;
			CARRY(p) = (val == 0) ? 1 : 0;
		}
		else
			NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
}

void				ft_st(t_list *p, t_global *gb)
{
	int		t2;
	int 	rin;
	int 	rout;

	t2 = get_ptype(gb->arena[ADR(p) + 1], 1);
	if ((t2 == T_IND || t2 == T_REG) && \
		get_ptype(gb->arena[ADR(p) + 1], 0) == T_REG)
	{
		rin = ft_get_int(gb->arena, ADR(p) + 2, 1);
		if (rin > 0 && rin < REG_NUMBER)
		{
			if (t2 == T_REG)
			{
				rout = ft_get_int(gb->arena, ADR(p) + 3, 1);
				if (rout <= REG_NUMBER && rout > 0)
				{
					ft_reg_write(p, rout, ft_get_reg(p, rin));
					NEXT(p) = (ADR(p) + 4) % MEM_SIZE;
				}
				else
					NEXT(p) = (ADR(p) + 1) % MEM_SIZE;				
			}
			if (t2 == T_IND)
			{

				ft_int_write(gb->arena, (ADR(p) + (ft_get_int(gb->arena, \
					ADR(p) + 3, IND_SIZE) % IDX_MOD)) % MEM_SIZE,\
					ft_get_reg(p, rin), REG_SIZE);
				NEXT(p) = (ADR(p) + 3 + IND_SIZE) % MEM_SIZE;
			}
		}
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
}

void				ft_add(t_list *p, t_global *gb)
{
	t_param	*tab;
	int		nxt;
	int		res;

	tab = malloc(sizeof(t_param) * 3);
	if ((nxt = ft_get_params(gb->arena, ADR(p), &tab, p)))
	{
		res = tab[0].val + tab[1].val;
		CARRY(p) = (res == 0) ? 1 : 0;
		ft_reg_write(p, tab[2].reg, res);
		NEXT(p) = (nxt) % MEM_SIZE;
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
	free(tab);
}

void				ft_sub(t_list *p, t_global *gb)
{
	t_param	*tab;
	int		nxt;
	int		res;

	tab = malloc(sizeof(t_param) * 3);
	if ((nxt = ft_get_params(gb->arena, ADR(p), &tab, p)))
	{
		res = tab[0].val - tab[1].val;
		CARRY(p) = (res == 0) ? 1 : 0;
		ft_reg_write(p, tab[2].reg, res);
		NEXT(p) = (nxt) % MEM_SIZE;
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
	free(tab);
}

void				ft_and(t_list *p, t_global *gb)
{
	t_param	*tab;
	int		nxt;
	int		res;

	tab = malloc(sizeof(t_param) * 3);
	if ((nxt = ft_get_params(gb->arena, ADR(p), &tab, p)))
	{
		res = tab[0].val & tab[1].val;
		CARRY(p) = (res == 0) ? 1 : 0;
		ft_reg_write(p, tab[2].reg, res);
		NEXT(p) = (nxt) % MEM_SIZE;
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
	free(tab);
}

void				ft_or(t_list *p, t_global *gb)
{
	t_param	*tab;
	int		nxt;
	int		res;

	tab = malloc(sizeof(t_param) * 3);
	if ((nxt = ft_get_params(gb->arena, ADR(p), &tab, p)))
	{
		res = tab[0].val | tab[1].val;
		CARRY(p) = (res == 0) ? 1 : 0;
		ft_reg_write(p, tab[2].reg, res);
		NEXT(p) = (nxt) % MEM_SIZE;
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
	free(tab);
}

void				ft_xor(t_list *p, t_global *gb)
{
	t_param	*tab;
	int		nxt;
	int		res;

	tab = malloc(sizeof(t_param) * 3);
	if ((nxt = ft_get_params(gb->arena, ADR(p), &tab, p)))
	{
		res = tab[0].val ^ tab[1].val;
		CARRY(p) = (res == 0) ? 1 : 0;
		ft_reg_write(p, tab[2].reg, res);
		NEXT(p) = (nxt) % MEM_SIZE;
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
	free(tab);
}

void				ft_zjmp(t_list *p, t_global *gb)
{
	if (CARRY(p) == 1)
		NEXT(p) = (ADR(p) + ((short)(ft_get_int(gb->arena, ADR(p) + 1, 2)) % IDX_MOD)) % MEM_SIZE;
	else
		NEXT(p) = (ADR(p) + 3) % MEM_SIZE;
}

void				ft_ldi(t_list *p, t_global *gb)
{
	if (p && gb)
	{
		return;
	}
}

void				ft_sti(t_list *p, t_global *gb)
{
	if (p && gb)
	{
		return;
	}
}

void				ft_fork(t_list *p, t_global *gb)
{
	t_list	*new;

	NEXT(p) = (ADR(p) + 3) % MEM_SIZE;
	if (!(new = ft_lstnew((t_process *)(p->content), sizeof(t_process))))
		return;
	ft_lstadd(&(gb->procs), new);
	ADR(new) = (ADR(p) + (ft_get_int(gb->arena, ADR(p) + 1, 2) % IDX_MOD)) % MEM_SIZE;
	OPC(new) = gb->arena[ADR(new)];
	if (OPC(new) > 0 && OPC(new) < 17)
		TIME(new) = OP_NBC(OPC(new));
	else
		TIME(new) = 1;
}

void				ft_lld(t_list *p, t_global *gb)
{
	if (p && gb)
	{
		return;
	}
}

void				ft_lldi(t_list *p, t_global *gb)
{
	if (p && gb)
	{
		return;
	}
}

void				ft_lfork(t_list *p, t_global *gb)
{
	if (p && gb)
	{
		return;
	}
}

void				ft_aff(t_list *p, t_global *gb)
{
	if (p && gb)
	{
		return;
	}
}

