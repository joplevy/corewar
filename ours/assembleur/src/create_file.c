/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 14:04:58 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/04/23 14:06:23 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void	ft_complete_file(t_tasm *tasm)
{
	t_list		*tmp;
	t_labdir	*content;

	if (lseek(tasm->fd, PROG_NAME_LENGTH + 8, SEEK_SET) == -1)
		return ;
	ft_putchar_fd((unsigned)tasm->prog_size >> 24, tasm->fd);
	ft_putchar_fd((unsigned)tasm->prog_size >> 16, tasm->fd);
	ft_putchar_fd((unsigned)tasm->prog_size >> 8, tasm->fd);
	ft_putchar_fd((unsigned)tasm->prog_size, tasm->fd);
	if (lseek(tasm->fd, COMMENT_LENGTH + 4, SEEK_CUR) == -1)
		return ;
	tmp = tasm->labdirs;
	while (tmp)
	{
		content = tmp->content;
		if (lseek(tasm->fd, content->addr - 1, SEEK_CUR) == -1)
			return ;
		print_label_addr(tasm, content);
		tmp = tmp->next;
	}
}

int 		create_file(t_tasm *tasm, char *path, int i)
{
	char 	*dot_cor;

	if ((dot_cor = get_file_name(path)) == NULL)
		return (0);
	if ((tasm->fd = open(dot_cor, O_CREAT | O_WRONLY | O_TRUNC, 0755)) == -1)
		return (0);
	free(dot_cor);
	ft_print_magic(tasm->fd);
	ft_print_header(tasm);
	ft_print_body(tasm, tasm->f_content, i);
	ft_complete_file(tasm);
	return (1);
}
