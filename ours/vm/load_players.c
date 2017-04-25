#include "corewar.h"

int				ft_strupcpy(unsigned char *arena, char *code, int len, int pos)
{
	int			i;

	i = 0;
	while (i <= len)
	{
		arena[pos + i] = code[i];
		++i;
	}
}

static void 	put_players(t_player **player, t_global *gb, int nb_players)
{
	int			i;
	int			entry;
	int			modulo;

	entry = -1 * (MEM_SIZE  / nb_players);
	modulo = MEM_SIZE % nb_players;
	i = -1;
	while (++i != nb_players)
	{
		entry += (MEM_SIZE / nb_players);
		if (modulo && entry)
		{
			entry++;
			modulo--;
		}
		ft_strupcpy(gb->arena, ((gb->players)[i])->code, \
								((gb->players)[i])->size, entry);
	}
}

int				load_players(t_global *gb)
{
	int			i;

	i = 0;
	while ((gb->players)[i] != NULL)
		i++;
	put_players((t_player**)(gb->players), gb, i);
	return (1);
}
