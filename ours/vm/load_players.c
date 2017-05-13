#include "corewar.h"

int				init_new_proc(t_player *player, t_list **procs)
{
	t_process	proc;
	t_list		new;
	int			i;

	proc.player = player->id;
	proc.carry = 0;
	proc.live = 0;
	proc.cycles = 0;
	proc.adress = player->pos;
	i = -1;
	while (++i < REG_NUMBER)
		(proc.regs)[i] = 0;
	if (!(new = ft_lstnew(proc, sizeof(t_process))))
		return (0);
	ft_lstadd(procs, new);
	return (1);
}

int				load_players(t_global *gb)
{
	int			i;
	int			pos;
	int			modulo;

	pos = -1 * (MEM_SIZE  / nb_players);
	modulo = MEM_SIZE % nb_players;
	i = -1;
	while (++i != nb_players)
	{
		pos += (MEM_SIZE / nb_players);
		if (modulo && pos)
		{
			pos++;
			modulo--;
		}
		ft_memcpy((void*)(gb->arena) + (((gb->players)[i])->pos = pos), \
					(const void*)((gb->players)[i])->code, \
					(size_t)((gb->players)[i])->size);
	}
	i = -1;
 	while ((gb->players)[++i] != NULL)
 		if (!intit_new_proc((gb->players)[i], &(gb->procs)))
 			return (0);
 	return (1);
}