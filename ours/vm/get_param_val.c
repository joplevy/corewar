/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param_val.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 17:42:18 by rvan-der          #+#    #+#             */
/*   Updated: 2017/06/18 19:09:16 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int			get_param_pos(int nb, int opc, int ocp)
{
	int		ret;
	int		i;
	int		t;

	ret = 2;
	if (nb > 1 && nb < 5)
	{
		i = 0;
		while (++i < nb)
		{
			if ((t = get_type(ocp, i)) == T_DIR)
				ret += (OP_LAB(opc) ? IND_SIZE : DIR_SIZE);
			else if (t == T_IND)
				ret += IND_SIZE;
			else if (t == T_REG)
				ret++;
		}
	}
	return (ret);
}

int			get_param_val(int nb, int pc, unsigned char *a, int deref)
{
	int		t;
	int		pos;

	if (!nb)
		return (ft_get_int(a, pc + 1, (OP_LAB(a[pc]) ? IND_SIZE : DIR_SIZE)));
	pos = get_param_pos(nb, a[pc], a[(pc + 1) % MEM_SIZE]);
	if ((t = get_type(a[(pc + 1) % MEM_SIZE], nb - 1)) == T_DIR)
		return (ft_get_int(a, (pc + pos) % MEM_SIZE, \
					(OP_LAB(a[pc]) ? IND_SIZE : DIR_SIZE)));
	if (t == T_REG)
		return ((int)(a[(pc + pos) % MEM_SIZE]));
	if (t == T_IND && deref == 1)
		return (ft_get_int(a, (pc + (ft_get_int(a, (pc + pos) % MEM_SIZE,\
					IND_SIZE) % IDX_MOD)) % MEM_SIZE, \
					(OP_LAB(a[pc]) ? IND_SIZE : DIR_SIZE)));
