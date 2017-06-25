/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_rw.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 04:39:05 by jplevy            #+#    #+#             */
/*   Updated: 2017/06/25 05:07:26 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>


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
