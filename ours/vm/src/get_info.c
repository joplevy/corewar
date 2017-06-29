/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplev <joeyplev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 13:58:39 by joeyplev          #+#    #+#             */
/*   Updated: 2017/06/29 19:51:10 by niludwig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		exit_message(char *str)
{
	ft_putstr_fd(str, 2);
	exit(0);
}

static int	read_name(int fd, t_player *player)
{
	char	space[6];

	if ((read(fd, player->name, PROG_NAME_LENGTH)) <= 0)
		return (0);
	read(fd, space, 6);
	return (1);
}

static int	read_comment(int fd, t_player *player)
{
	char	space[6];

	if ((read(fd, player->comment, COMMENT_LENGTH)) <= 0)
		return (0);
	read(fd, space, 6);
	return (1);
}

static int	read_code(int fd, t_player *player)
{
	char	*s;

	s = NULL;
	if ((player->size = read(fd, player->code, CHAMP_MAX_SIZE)) <= 0)
		return (0);
	if (read(fd, s, 1) < 0)
	{
		ft_printf("Error : champ %s is to large.\n", player->name);
		return (0);
	}
	return (1);
}

static int	check_magic(int fd)
{
	char	a;
	char	b;
	char	c;
	char	d;
	char	s[4];

	a = 0x0;
	b = 0xea;
	c = 0x83;
	d = 0xf3;
	if ((read(fd, s, 4)) <= 0)
		return (0);
	if (a != s[0] || b != s[1] || c != s[2] || d != s[3])
		exit_message("fail compare in check_magic\n");
	return (1);
}

int			get_info_player(int fd, t_player *player)
{
	if (check_magic(fd) == 0)
		return (0);
	if (read_name(fd, player) == 0)
		return (0);
	if (read_comment(fd, player) == 0)
		return (0);
	if (read_code(fd, player) == 0)
		return (0);
	return (1);
}
