/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 21:27:59 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/06/16 21:38:31 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include <errno.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <ncurses.h>
# include <stdlib.h>
# include <libft.h>
# include <op.h>

# define ADR(NODE) (((t_process*)((NODE)->content))->adress)
# define OPC(NODE) (((t_process*)((NODE)->content))->opc)
# define TIME(NODE) (((t_process*)((NODE)->content))->time)
# define CARRY(NODE) (((t_process*)((NODE)->content))->carry)
# define LIVE(NODE) (((t_process*)((NODE)->content))->live)
# define REG(NODE) (((t_process*)((NODE)->content))->regs)
# define NEXT(NODE) (((t_process*)((NODE)->content))->next)

# define OP_NAME(OP) (g_op_tab[OP - 1].name)
# define OP_NBP(OP) (g_op_tab[OP - 1].nb_param)
# define OP_PAR(OP) (g_op_tab[OP - 1].param)
# define OP_NBC(OP) (g_op_tab[OP - 1].nb_cycles)
# define OP_DESC(OP) (g_op_tab[OP - 1].description)
# define OP_OCP(OP) (g_op_tab[OP - 1].ocp)
# define OP_LAB(OP) (g_op_tab[OP - 1].label_size)

# define TAB_HEIGHT 64
# define TAB_WIDTH 64

typedef enum		e_vmtype
{
	tnul = 0,
	dir,
	ind,
	reg,
	terr
}					t_vmtype;

typedef enum	e_col
{
	green_b=1,
	b_green,
	red_b,
	b_red,
	blue_b,
	b_blue,
	yellow_b,
	b_yellow,
	white_b,
	b_white,
}				t_col;

typedef struct		s_param
{
	int				type;
	int				val;
	int				reg;
}					t_param;

typedef struct		s_process
{
	int				carry;
	int				live;
	unsigned char	opc;
	char			regs[REG_NUMBER][REG_SIZE];
	int				time;
	int 			adress;
	int 			next;
}					t_process;

typedef struct		s_player
{
	int				id;
	int				live;
	int				size;
	int				entry;
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	char			code[CHAMP_MAX_SIZE];
}					t_player;


typedef struct 		s_global
{
	t_list			*procs;
	t_player		*players[MAX_PLAYERS + 1];
	unsigned char	*arena;
	t_col			*col;
	WINDOW			*box;
	int 			nb_process;
	int				lives;
	int				last_id;
	int				ctd;
	int				checks;
	int				dump;
	int				show;
	int 			nb_pl;
}					t_global;

/*
**	vm
*/
/*
**		get_info.c
*/

int					get_info_player(int fd, t_player *player);

/*
**		affichage.c
*/

void				init_ncurses(t_global *all);
void				end_ncurses(WINDOW *box);
void				box_put_arena(t_global  *all);
void				ft_putbinary(char *str, int size);

/*
**		set_global.c
*/

int					set_global(t_list *args, t_global *gb);

/*
**		init.c
*/

int					load_players(t_global *gb);
int					init_new_proc(t_global *gb, int pos, int id);
t_global			*init_global();
t_opt				*opt_tab(void);

/*
**		get_param_lenght.c
*/

int					get_params_length(int adr, unsigned char *arena);
t_vmtype			get_type(unsigned char ocp, int	pos);
int					get_type_size(t_vmtype type);

/*
**		instructions
*/

void			ft_int_write(unsigned char *arena, int adr, int val, int size);

void				ft_live(t_list *p, t_global *gb);
void				ft_ld(t_list *p, t_global *gb);
void				ft_st(t_list *p, t_global *gb);
void				ft_add(t_list *p, t_global *gb);
void				ft_sub(t_list *p, t_global *gb);
void				ft_and(t_list *p, t_global *gb);
void				ft_or(t_list *p, t_global *gb);
void				ft_xor(t_list *p, t_global *gb);
void				ft_zjmp(t_list *p, t_global *gb);
void				ft_ldi(t_list *p, t_global *gb);
void				ft_sti(t_list *p, t_global *gb);
void				ft_fork(t_list *p, t_global *gb);
void				ft_lld(t_list *p, t_global *gb);
void				ft_lldi(t_list *p, t_global *gb);
void				ft_lfork(t_list *p, t_global *gb);
void				ft_aff(t_list *p, t_global *gb);

extern void 		(*instructab[17])(t_list *, t_global *);

#endif
