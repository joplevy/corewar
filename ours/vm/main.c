/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 17:00:57 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/05/12 23:02:50 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>
#include <stdio.h>

/*
static void		ft_uputbinary(unsigned char *str, int size)
{
	int		i;
	char *strr;

	i = -1;
	strr = (char*)str;
	while (++i < size)
		printf("%02x ", strr[i] & 0xFF);
}
*/

void		ft_putbinary(char *str, int size)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		printf("%02x ", str[i] & 0xFF);
		if (!((i + 1) % 32))
			printf("\n");
	}
}

t_global	*init_global()
{
	t_global	*ret;
	int			i;

	if (!(ret = (t_global*)malloc(sizeof(t_global))))
		return (NULL);
	if (!(ret->arena = ft_memalloc(MEM_SIZE)))
		return (NULL);
	ret->procs = NULL;
	i = -1;
	while (++i <= MAX_PLAYERS)
		ret->players[i] = NULL;
	ret->lives = 0;
	ret->last_id = 0;
	ret->ctd = CYCLE_TO_DIE;
	ret->checks = 0;
	ret->dump = -2;
	ret->show = 0;
	ret->nb_arg = 0;
	ret->nb_pl = 0;
	return (ret);
}

/*
static int 				get_poss(t_global *gb)
{
	int possition;

	possition = gb->nb_arg;
	//recuperation des possition
	return (possition);
}

static int				load_players(t_player *player)
{
	int i;
	int pos;

	i = 0;
	pos = get_poss(gb);
	ft_memcpy(gb->arena + pos, player->code, CHAMP_MAX_SIZE);
	ft_uputbinary(gb->arena, MEM_SIZE);
	return (1);
}

static void get_arg(int ac, char **av, t_global *gb)
{
	int i;

	i = 1;
	while (i != ac)
	{
		if (ft_strlen(av[i]) == 2)
			gb->nb_arg += 1;
		else
			gb->nb_player += 1;
		i++;
	}
	ft_printf("nb_player=%i\nnb_arg=%i\n", gb->nb_player, gb->nb_arg);
	if (gb->nb_arg > 0)
		;//a faire
}
*/
t_opt		*opt_tab(void)
{
	t_opt		*ret;

	if ((ret = (t_opt*)malloc(sizeof(t_opt) * 4)) == NULL)
		return (NULL);
	(ret[0]).name = "p";
	(ret[0]).args = "if";
	(ret[1]).name = "n";
	(ret[1]).args =  "";
	(ret[2]).name = "dump";
	(ret[2]).args = "i";
	(ret[3]).name = "";
	(ret[3]).args = "";
	return (ret);
}

int				init_new_proc(t_player *player, t_list **procs)
{
	t_process	proc;
	t_list		*new;
	int			i;

	proc.player = player->id;
	proc.carry = 0;
	proc.live = 0;
	proc.cycles = 0;
	proc.adress = player->pos;
	i = -1;
	while (++i < REG_NUMBER)
		(proc.regs)[i] = 0;
	if (!(new = ft_lstnew((void*)(&proc), sizeof(t_process))))
		return (0);
	ft_lstadd(procs, new);
	return (1);
}

int				load_players(t_global *gb)
{
	int			i;
	int			pos;
	int			modulo;

	pos = -1 * (MEM_SIZE  / gb->nb_pl);
	modulo = MEM_SIZE % gb->nb_pl;
	i = -1;
	while (++i < gb->nb_pl)
	{
		pos += (MEM_SIZE / gb->nb_pl);
		if (modulo && pos)
		{
			pos++;
			modulo--;
		}
		ft_memcpy((void*)(gb->arena) + pos, \
					(const void*)((gb->players)[i])->code, \
					(size_t)((gb->players)[i])->size);
	}
 	i = -1;
  	while ((gb->players)[++i] != NULL)
  		if (!init_new_proc((gb->players)[i], &(gb->procs)))
  			return (0);
 	return (1);
}

void		print_proclist(t_list *procs)
{
	t_list		*tmp;
	
	tmp = procs;
	while (tmp != NULL)
	{
		printf("player: %d\n", ((t_process*)(tmp->content))->player);
		printf("carry: %d\n", ((t_process*)(tmp->content))->carry);
		printf("cycles: %d\n", ((t_process*)(tmp->content))->cycles);
		printf("live: %d\n", ((t_process*)(tmp->content))->live);
		printf("adress: %d\n", ((t_process*)(tmp->content))->adress);
		printf("|\n");
		tmp = tmp->next;
	}
	printf("NULL\n");
}

int			main(int ac, char **av)
{
	t_global	*global;
	t_list		*args;
	int 		i;
	t_opt		*tab;

	tab = opt_tab();
	if (!(global = init_global()))
		return (0);
	ft_putendl("////init_global////");
	if (!(args = ft_get_args(ac, av, tab, 'f')))
		return (0);
	free(tab);
	ft_putendl("////ft_get_args////");
	if (!set_global(args, global))
		return (0);
	ft_putendl("////set_global////");
	printf("global->nb_pl = %d\n", global->nb_pl);
	i = -1;
	while (++i < global->nb_pl)
	{
		ft_putbinary(global->players[i]->name, PROG_NAME_LENGTH);
		printf("\n\n");
		ft_putbinary(global->players[i]->comment, COMMENT_LENGTH);
		printf("\n\n");
		ft_putbinary(global->players[i]->code, global->players[i]->size);
		printf("\n\n");
	}
	printf("\nARENA:\n\n");
	ft_putbinary((char*)global->arena, MEM_SIZE);
	print_proclist(global->procs);
	return (0);
}
