#include "corewar.h"

int				ft_strupcpy(char *arena, char *champion, int len_champion, int position)
{
	int			i;

	i = 0;
	while (i <= len_champion)
	{
		arena[position + i] = champion[i];
		++i;
	}
}

static void 	put_player(t_player **player, t_global *gb, int nb_player)
{
	int			i;
	int			nb_players;
	int			entry;
	int			modulo;

	nb_player = 0;
	while ((gb->players)[nb_players] != NULL)
		nb_players++;
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
		ft_strupcpy(arena, player-code, player->end, entry);
	}
}

static int		load_players(t_global *gb)
{
	int			i;

	i = 0;
	while ((gb->player[i]) != NULL)
		i++;
	put_player((t_player**)(gb->player), gb->arena, i);
	return (1);
}
