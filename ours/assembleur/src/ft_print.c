/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 13:55:46 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/04/23 14:01:16 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void	ft_print_header(t_tasm *tasm)
{
	int		len;

	len = ft_strlen(tasm->prog_name);
	ft_putstr_fd(tasm->prog_name, tasm->fd);
	while (++len <= PROG_NAME_LENGTH)
		write(tasm->fd, "\0", 1);
	write(tasm->fd, "\0\0\0\0\0\0\0\0", 8);
	len = ft_strlen(tasm->comment);
	ft_putstr_fd(tasm->comment, tasm->fd);
	while (++len <= COMMENT_LENGTH + 4)
		write(tasm->fd, "\0", 1);
}

void	ft_print_magic(int fd)
{
	int		magic[4];
	int		mag;
	int		i;

	i = -1;
	mag = COREWAR_EXEC_MAGIC;
	while (++i < 4)
	{
		magic[i] = (unsigned char)mag;
		mag >>= 8;
	}
	while (--i >= 0)
		ft_putchar_fd(magic[i], fd);
}

int		ft_print_params(t_tasm *tasm, t_inst *ins, int i)
{
	char	*f_content;

	if (g_op_tab[ins->i_instr].ocp)
		ins->octet++;
	ins->nb_instr = -1;
	ins->ocp = 0;
	tasm->idx = i;
	f_content = tasm->f_content;
	while (++(ins->nb_instr) < g_op_tab[ins->i_instr].nb_param)
	{
		while (ft_iswhitespace(f_content[tasm->idx]))
			tasm->idx++;
		if (f_content[tasm->idx] == SEPARATOR_CHAR)
			tasm->idx++;
		while (ft_iswhitespace(f_content[tasm->idx]))
			tasm->idx++;
		if ((ins->ins = ft_strsub(f_content, tasm->idx,
				ft_get_param_end(f_content, tasm->idx) - tasm->idx)) == NULL)
			return (0);
		tasm->idx = ft_get_param(tasm, ins);
		free(ins->ins);
	}
	ft_print_param(tasm, ins);
	return (tasm->idx);
}

void	ft_print_body(t_tasm *tasm, char *f_content, int i)
{
	t_inst	ins;

	ins.octet = 0;
	while (f_content[i])
	{
		if ((f_content[i] == COMMENT_CHAR || f_content[i] == ';')
			&& (i = ft_jump_nextline(f_content, i)))
			continue;
		if (!ft_iswhitespace(f_content[i]))
		{
			i = ft_get_label_pos(tasm, &ins, i);
			while (ft_iswhitespace(f_content[i]))
				i++;
			while (f_content[i] == COMMENT_CHAR || f_content[i] == ';')
				i = ft_jump_nextline(f_content, i);
			while (ft_iswhitespace(f_content[i]))
				i++;
			if (!(i = ft_get_instr(tasm, i, &ins)))
				return ;
		}
		else
			i++;
	}
	tasm->prog_size = ins.octet;
}

void	print_label_addr(t_tasm *tasm, t_labdir *labdir)
{
	t_list	*tmp;
	t_label	*label;
	int		val;

	tmp = tasm->labels;
	while (tmp)
	{
		label = tmp->content;
		if (!ft_strcmp(labdir->label, label->label))
		{
			val = label->addr - labdir->instr_addr;
			ft_putchar_fd(val >> 8, tasm->fd);
			ft_putchar_fd(val, tasm->fd);
			if (lseek(tasm->fd, -(labdir->addr + 1), SEEK_CUR) == -1)
				return ;
			return ;
		}
		tmp = tmp->next;
	}
}
