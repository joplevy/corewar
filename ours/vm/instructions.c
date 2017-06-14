/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 19:54:59 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/14 18:02:25 by jplevy           ###   ########.fr       */
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

int			get_type_siz(int type)
{
	if (type == T_IND)
		return (IND_SIZE);
	if (type == T_DIR)
		return (DIR_SIZE);
	if (type == T_REG)
		return (1);
	return (0);
}

int					get_typ(unsigned char ocp, int	pos)
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
	
	t1 = get_typ(gb->arena[ADR(p) + 1], 0);
	if ((t1 == T_DIR || t1 == T_IND) && \
		get_typ(gb->arena[ADR(p) + 1], 1) == T_REG)
	{
		adress = (t1 == T_DIR) ? (ADR(p) + 2) % MEM_SIZE : \
			(ADR(p) + (ft_get_int(gb->arena, \
			ADR(p) + 2, IND_SIZE) % IDX_MOD)) % MEM_SIZE;
		val = ft_get_int(gb->arena, adress, REG_SIZE);
		if ((r2 = ft_get_reg_nb(gb->arena, \
			(ADR(p) + 2 + get_type_siz(t1)) % MEM_SIZE)))
		{
			ft_reg_write(p, r2, val);
			NEXT(p) = (ADR(p) + 3 + get_type_siz(t1)) % MEM_SIZE;
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

	t2 = get_typ(gb->arena[ADR(p) + 1], 1);
	if ((t2 == T_IND || t2 == T_REG) && \
		get_typ(gb->arena[ADR(p) + 1], 0) == T_REG)
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
	int		r1;
	int		r2;
	int		r3;

	if (((gb->arena[ADR(p) + 1] >> 2) & 0x3f) == 0x15)
	{
		if (!(r1 = ft_get_reg_nb(gb->arena, ADR(p) + 2)) \
			|| !(r2 = ft_get_reg_nb(gb->arena, ADR(p) + 3)) \
			|| !(r3 = ft_get_reg_nb(gb->arena, ADR(p) + 4)))
			NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
		else
		{
			CARRY(p) = (r2 + r1 == 0) ? 1 : 0;
			ft_reg_write(p, r3, ft_get_reg(p, r2) + ft_get_reg(p, r1));
			NEXT(p) = (ADR(p) + 5) % MEM_SIZE;
		}
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
}

void				ft_sub(t_list *p, t_global *gb)
{
	if (p && gb)
	{
		return;
	}
}

void				ft_and(t_list *p, t_global *gb)
{
	if (p && gb)
	{
		return;
	}
}

void				ft_or(t_list *p, t_global *gb)
{
	if (p && gb)
	{
		return;
	}
}

void				ft_xor(t_list *p, t_global *gb)
{
	if (p && gb)
	{
		return;
	}
}

void				ft_zjmp(t_list *p, t_global *gb)
{
	if (p && gb)
	{
		return;
	}
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
	if (p && gb)
	{
		return;
	}
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

