/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 19:54:59 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/14 01:48:58 by jplevy           ###   ########.fr       */
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
	
	t1 = get_typ(gb->arena[ADR(p) + 1], 0);
	if ((t1 == T_DIR || t1 == T_IND) && \
		get_typ(gb->arena[ADR(p) + 1], 1) == T_REG)
	{
		adress = (t1 == T_DIR) ? ADR(p) + 2 : \
			(ADR(p) + (ft_get_int(gb->arena, \
			ADR(p) + 2, IND_SIZE) % IDX_MOD)) % MEM_SIZE;
		val = ft_get_int(gb->arena, adress, REG_SIZE);
		ft_int_write((unsigned char *)(REG(p)[ft_get_int(gb->arena, ADR(p) + 2 + \
			get_type_siz(t1), 1) - 1]), 0, val, REG_SIZE);
		CARRY(p) = (val == 0) ? 1 : 0;
		ft_printf("%d\n", CARRY(p));
		NEXT(p) = (ADR(p) + 3 + get_type_siz(t1)) % MEM_SIZE;
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
					ft_int_write((unsigned char *)(REG(p)[rout - 1]), 0, \
						ft_get_int((unsigned char *)(REG(p)[rin - 1]), 0, 4), 4);
					NEXT(p) = (ADR(p) + 4) % MEM_SIZE;
				}
				else
					NEXT(p) = (ADR(p) + 1) % MEM_SIZE;				
			}
			if (t2 == T_IND)
			{
				ft_int_write(gb->arena, (ADR(p) + (ft_get_int(gb->arena, \
					ADR(p) + 3, IND_SIZE) % IDX_MOD)) % MEM_SIZE,\
					ft_get_int((unsigned char *)(REG(p)[rin - 1]), 0, 4), REG_SIZE);
				NEXT(p) = (ADR(p) + 3 + IND_SIZE) % MEM_SIZE;
			}
		}
	}
	else
		NEXT(p) = (ADR(p) + 1) % MEM_SIZE;
}

void				ft_add(t_list *p, t_global *gb)
{
	if (p && gb)
	{
		return;
	}
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

