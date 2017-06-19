/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_on.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 20:04:07 by niludwig          #+#    #+#             */
/*   Updated: 2017/06/20 00:03:52 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int ft_putchar_fd_one(char c, int fd)
{
    ft_putchar_fd(c, fd);
    return (1);
}

void ft_putchar_fd_two(char c, char c2, int fd)
{
	ft_putchar_fd(c, fd);
	ft_putchar_fd(c2, fd);
}

void ft_putchar_fd_quatro(char c, char c2, char c3, char c4, int fd)
{
	ft_putchar_fd(c, fd);
	ft_putchar_fd(c2, fd);
	ft_putchar_fd(c3, fd);
	ft_putchar_fd(c4, fd);
}
