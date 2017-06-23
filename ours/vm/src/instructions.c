/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 19:54:59 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/23 20:43:15 by rvan-der         ###   ########.fr       */
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

int				ft_get_reg(t_list *p, int reg)
{
	return (ft_get_int((unsigned char *)(REG(p)[reg - 1]), 0, REG_SIZE));
}

void			ft_reg_write(t_list *p, int reg, int val)
{
	ft_int_write((unsigned char *)(REG(p)[reg - 1]), 0, val, REG_SIZE);
}

int				ft_get_ind(unsigned char *arena, int adr, int add, int size)
{
	return (ft_get_int(arena, (adr + add) % MEM_SIZE, size));
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
		// ft_printf("inst = %X, param %d = %d\n", inst, i, g_op_tab[inst - 1].param[i] \
			// & get_ptype(arena[(adr + 1) % MEM_SIZE], i));
		if (!(len = get_type_siz(PAR(p)[i].type, g_op_tab[inst - 1].label_size)))
			return (0);
		if (PAR(p)[i].type == T_REG)
			if (!(PAR(p)[i].reg = ft_get_reg_nb(arena, ptr)))
				return(0);
		PAR(p)[i].val = (PAR(p)[i].type == T_REG) ? ft_get_reg(p, PAR(p)[i].reg) : 
			ft_get_int(arena, ptr, len);
		ptr = (ptr + len) % MEM_SIZE;
	}
	return (ptr);
}

int					get_relative(int adr, int inc, int mod)
{
	int				ret;

	inc = (mod ? inc % IDX_MOD : inc % MEM_SIZE);
	if ((ret = adr + inc) < 0)
		ret += MEM_SIZE;
	return (ret % MEM_SIZE);
}

/*
** instructions 
*/

void				ft_live(t_list *p, t_global *gb)
{
	int		id;

	id = ft_get_int(gb->arena, (ADR(p) + 1) % MEM_SIZE, 4);
	if (id < 0 && id > -5)
		gb->last_id = id;
	LIVE(p)++;
	NEXT(p) = (ADR(p) + 5) % MEM_SIZE;
}

void				ft_ld(t_list *p, t_global *gb)
{
	int		nxt;
	int		adr;

	// tab = malloc(sizeof(t_param) * 2);
	if ((nxt = ft_get_params(gb->arena, ADR(p), p)))
	{
		if (PAR(p)[0].type == T_IND)
		{
			adr = get_relative(ADR(p), (short)(PAR(p)[0].val), 1);
			PAR(p)[0].val = ft_get_int(gb->arena, adr, 4);
		}
		CARRY(p) = ((PAR(p)[0].val == 0) ? 1 : 0);
		ft_reg_write(p, PAR(p)[1].reg, PAR(p)[0].val);
		NEXT(p) = (nxt) % MEM_SIZE;
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
	// free(tab);
}

void				ft_st(t_list *p, t_global *gb)
{
	int		nxt;
	int		adr;
	int		i;

	if ((nxt = ft_get_params(gb->arena, ADR(p), p)))
	{
		if (PAR(p)[1].type == T_REG)
			ft_reg_write(p, PAR(p)[1].reg, PAR(p)[0].val);
		else
		{
			adr = get_relative(ADR(p), (short)(PAR(p)[1].val), 1);
			ft_int_write(gb->arena, adr, PAR(p)[0].val, 4);
			i = -1;
			while (++i < 4)
				gb->col[(adr + i) % MEM_SIZE] = \
			(gb->col[(adr + i) % MEM_SIZE] & 0xF) | (PID(p) << 4);
		}
		NEXT(p) = (nxt) % MEM_SIZE;
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
}

void				ft_add(t_list *p, t_global *gb)
{
	int		nxt;
	int		res;

	// tab = malloc(sizeof(t_param) * 3);
	if ((nxt = ft_get_params(gb->arena, ADR(p), p)))
	{
		res = PAR(p)[0].val + PAR(p)[1].val;
		CARRY(p) = (res == 0) ? 1 : 0;
		ft_reg_write(p, PAR(p)[2].reg, res);
		NEXT(p) = (nxt) % MEM_SIZE;
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
	// free(tab);
}

void				ft_sub(t_list *p, t_global *gb)
{
	int		nxt;
	int		res;

	// tab = malloc(sizeof(t_param) * 3);
	if ((nxt = ft_get_params(gb->arena, ADR(p), p)))
	{
		res = PAR(p)[0].val - PAR(p)[1].val;
		CARRY(p) = (res == 0) ? 1 : 0;
		ft_reg_write(p, PAR(p)[2].reg, res);
		NEXT(p) = (nxt) % MEM_SIZE;
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
	// free(tab);
}

void				ft_and(t_list *p, t_global *gb)
{
	int		nxt;
	int		res;
	int		adr;

	// tab = malloc(sizeof(t_param) * 3);
	if ((nxt = ft_get_params(gb->arena, ADR(p), p)))
	{
		if (PAR(p)[0].type == T_IND)
		{
			adr = get_relative(ADR(p), PAR(p)[0].val, 1);
			PAR(p)[0].val = ft_get_int(gb->arena, adr, 4);
		}
		if (PAR(p)[1].type == T_IND)
		{
			adr = get_relative(ADR(p), PAR(p)[1].val, 1);
			PAR(p)[1].val = ft_get_int(gb->arena, adr, 4);
		}
		res = PAR(p)[0].val & PAR(p)[1].val;
		CARRY(p) = (res == 0) ? 1 : 0;
		ft_reg_write(p, PAR(p)[2].reg, res);
		NEXT(p) = (nxt) % MEM_SIZE;
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
	// free(tab);
}

void				ft_or(t_list *p, t_global *gb)
{
	int		nxt;
	int		res;
	int		adr;

	// tab = malloc(sizeof(t_param) * 3);
	if ((nxt = ft_get_params(gb->arena, ADR(p), p)))
	{
		if (PAR(p)[0].type == T_IND)
		{
			adr = get_relative(ADR(p), PAR(p)[0].val, 1);
			PAR(p)[0].val = ft_get_int(gb->arena, adr, 4);
		}
		if (PAR(p)[1].type == T_IND)
		{
			adr = get_relative(ADR(p), PAR(p)[1].val, 1);
			PAR(p)[1].val = ft_get_int(gb->arena, adr, 4);
		}
		res = PAR(p)[0].val | PAR(p)[1].val;
		CARRY(p) = (res == 0) ? 1 : 0;
		ft_reg_write(p, PAR(p)[2].reg, res);
		NEXT(p) = (nxt) % MEM_SIZE;
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
	// free(tab);
}

void				ft_xor(t_list *p, t_global *gb)
{
	int		nxt;
	int		res;
	int		adr;

	// tab = malloc(sizeof(t_param) * 3);
	if ((nxt = ft_get_params(gb->arena, ADR(p), p)))
	{
		if (PAR(p)[0].type == T_IND)
		{
			adr = get_relative(ADR(p), PAR(p)[0].val, 1);
			PAR(p)[0].val = ft_get_int(gb->arena, adr, 4);
		}
		if (PAR(p)[1].type == T_IND)
		{
			adr = get_relative(ADR(p), PAR(p)[1].val, 1);
			PAR(p)[1].val = ft_get_int(gb->arena, adr, 4);
		}
		res = PAR(p)[0].val ^ PAR(p)[1].val;
		CARRY(p) = (res == 0) ? 1 : 0;
		ft_reg_write(p, PAR(p)[2].reg, res);
		NEXT(p) = (nxt) % MEM_SIZE;
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
	// free(tab);
}

void				ft_zjmp(t_list *p, t_global *gb)
{
	short			jump;

	if (CARRY(p) == 1)
	{
		jump = (short)ft_get_int(gb->arena, ADR(p) + 1, 2);
		NEXT(p) = get_relative(ADR(p), jump, 1);
	}
	else
		NEXT(p) = (ADR(p) + 3) % MEM_SIZE;
}

void				ft_ldi(t_list *p, t_global *gb)
{
	int		nxt;
	int		adr;
	int		res;

	// tab = malloc(sizeof(t_param) * 3);
	if ((nxt = ft_get_params(gb->arena, ADR(p), p)))
	{
		if (PAR(p)[0].type == T_IND)
		{
			adr = get_relative(ADR(p), PAR(p)[0].val, 1);
			PAR(p)[0].val = (short)ft_get_int(gb->arena, adr, 2);
		}
		adr = get_relative(ADR(p), PAR(p)[0].val + PAR(p)[1].val, 1);
		res = ft_get_int(gb->arena, adr, 4);
		ft_reg_write(p, PAR(p)[2].reg, res);
		NEXT(p) = (nxt) % MEM_SIZE;
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
	// free(tab);
}

void				ft_sti(t_list *p, t_global *gb)
{
	int		nxt;
	int		adr;
	int		i;

	// tab = malloc(sizeof(t_param) * 3);
	if ((nxt = ft_get_params(gb->arena, ADR(p), p)))
	{
		if (PAR(p)[1].type == T_IND)
		{
			adr = get_relative(ADR(p), PAR(p)[1].val, 1);
			PAR(p)[1].val = (short)ft_get_int(gb->arena, adr, 2);
		}
		adr = get_relative(ADR(p), PAR(p)[1].val + PAR(p)[2].val, 1);
		ft_int_write(gb->arena, adr, PAR(p)[0].val, 4);
		NEXT(p) = (nxt) % MEM_SIZE;
		i = -1;
		while (++i < 4)
			gb->col[(adr + i) % MEM_SIZE] = \
			(gb->col[(adr + i) % MEM_SIZE] & 0xF) | (PID(p) << 4);
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
	// free(tab);
}

void				ft_fork(t_list *p, t_global *gb)
{
	t_list	*new;
	short	jump;

	NEXT(p) = (ADR(p) + 3) % MEM_SIZE;
	if (!(new = ft_lstnew((t_process *)(p->content), sizeof(t_process))))
		return;
	ft_lstadd(&(gb->procs), new);
	jump = (short)ft_get_int(gb->arena, (ADR(p) + 1) % MEM_SIZE, 2);
	ADR(new) = get_relative(ADR(p), jump, 1);
	gb->col[ADR(new)] = (gb->col[ADR(new)] & 0xF0) | PID(p);
	OPC(new) = gb->arena[ADR(new)];
	if (OPC(new) > 0 && OPC(new) < 17)
		TIME(new) = OP_NBC(OPC(new));
	else
		TIME(new) = 1;
}

void				ft_lld(t_list *p, t_global *gb)
{
	int		nxt;
	int		adr;

	// tab = malloc(sizeof(t_param) * 2);
	if ((nxt = ft_get_params(gb->arena, ADR(p), p)))
	{
		if (PAR(p)[0].type == T_IND)
		{
			adr = get_relative(ADR(p), (short)(PAR(p)[0].val), 0);
			PAR(p)[0].val = ft_get_int(gb->arena, adr, 4);
		}
		CARRY(p) = ((PAR(p)[0].val == 0) ? 1 : 0);
		ft_reg_write(p, PAR(p)[1].reg, PAR(p)[0].val);
		NEXT(p) = (nxt) % MEM_SIZE;
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
	// free(tab);
}

void				ft_lldi(t_list *p, t_global *gb)
{
	int		nxt;
	int		adr;
	int		res;

	// tab = malloc(sizeof(t_param) * 3);
	if ((nxt = ft_get_params(gb->arena, ADR(p), p)))
	{
		if (PAR(p)[0].type == T_IND)
		{
			adr = get_relative(ADR(p), PAR(p)[0].val, 0);
			PAR(p)[0].val = (short)ft_get_int(gb->arena, adr, 2);
		}
		adr = get_relative(ADR(p), PAR(p)[0].val + PAR(p)[1].val, 0);
		res = ft_get_int(gb->arena, adr, 4);
		ft_reg_write(p, PAR(p)[2].reg, res);
		NEXT(p) = (nxt) % MEM_SIZE;
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
	// free(tab);
}

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
	if (OPC(new) > 0 && OPC(new) < 17)
		TIME(new) = OP_NBC(OPC(new));
	else
		TIME(new) = 1;
}

void				ft_aff(t_list *p, t_global *gb)
{
	int		nxt;

	// tab = malloc(sizeof(t_param) * 3);
	if ((nxt = ft_get_params(gb->arena, ADR(p), p)))
	{
		ft_putchar((char)(PAR(p)[0].val % 256));
		NEXT(p) = (nxt) % MEM_SIZE;
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
	// free(tab);
}

