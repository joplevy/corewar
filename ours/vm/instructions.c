/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 19:54:59 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/13 04:15:20 by jplevy           ###   ########.fr       */
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

void			ft_reg_write(t_list *p, int reg_nb, int data)
{
	if (reg_nb > 0 && reg_nb <= REG_NUMBER)
	{
		REG(p)[reg_nb - 1][0] = (char)((data & 0xFF000000) >> 24);
		REG(p)[reg_nb - 1][1] = (char)((data & 0xFF0000) >> 16);
		REG(p)[reg_nb - 1][2] = (char)((data & 0xFF00) >> 8);
		REG(p)[reg_nb - 1][3] = (char)(data & 0xFF);
	}
}

/*
** instructions 
*/

void				ft_live(t_list *p, t_global *gb)
{
		//checker que l'id recu soit valide
	gb->last_id = ft_get_int(gb->arena, ADR(p) + 1, 4);
	LIVE(p)++;
	NEXT(p) = ADR(p) + 4;
	NEXT(p)++;
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
		ft_reg_write(p, ft_get_int(gb->arena, ADR(p) + 2 + \
			get_type_siz(t1), 1), val);
		CARRY(p) = (val == 0) ? 1 : 0;
		NEXT(p) = ADR(p) + 3 + get_type_siz(t1);
	}
	else
		NEXT(p) = ADR(p) + 1;
}

void				ft_st(t_list *p, t_global *gb)
{
	int		t2;
	int 	rin;
	int 	rout;

	NEXT(p) = 0;
	t2 = get_typ(gb->arena[ADR(p) + 1], 1);
	if ((t2 == T_IND || t2 == T_REG) && \
		get_typ(gb->arena[ADR(p) + 1], 0) == T_REG)
	{
		rin = ft_get_int(gb->arena, ADR(p) + 2, 1);
		if (rin > 0 && rin < REG_NUMBER)
		{
			rout = ft_get_int(gb->arena, ADR(p) + 3, 1);
			if (t2 == T_REG && rout < REG_NUMBER && rout > 0)
			{
				ft_reg_write(p, rout, \
					ft_get_int((unsigned char *)(REG(p)[rin]), 0, 4));
				NEXT(p) = ADR(p) + 3;
			}
		}
	}
	if (NEXT(p) == 0)
		NEXT(p) = ADR(p) + 1;
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

