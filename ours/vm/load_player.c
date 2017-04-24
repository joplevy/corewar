#include "corewar.h"

int	ft_strupcpy(char *arena, char *champion, int len_champion, int position)
{
	int i;

	i = 0;
	while (i <= len_champion)
	{
		arena[position + i] = champion[i];
		++i;
	}
}

static void put_in_arena(t_player *player, char *arena, int nb_player)
{
	if ((nb_player == 4 && player->id == 4) 
		|| (nb_player == 3 && player->id == 3) 
		|| (nb_player == 2 && player->id == 2))
		ft_strupcpy(arena, player->code, player->end, (int)0);
	else if ((nb_player == 4 && player->id == 3) 
		|| (nb_player == 3 && player->id == 2))//le 3joueur est probablement faux, a voir! peut étre a coup de MEM_SIZE / nb_joueur serrais plus viable
		ft_strupcpy(arena, player-code, player->end, (int)1024);
	else if ((nb_player == 4 && player->id == 2) 
		|| (nb_player == 3 && player->id == 1)
		|| (nb_player == 2 && player->id == 1))
		ft_strupcpy(arena, player-code, player->end, (int)2048);
	else if (nb_player == 4 && player->id == 1)
		ft_strupcpy(arena, player-code, player->end, (int)3072);
	else
		exit_msg("ERROR: failed to place champion in arena\n");//ameliorer avec le bonnusse -n
}


static void put_player(t_player **player, t_global *gb, int nb_player)
{
	int i;

	i = 0;
	while (i != (nb_player + 1))
	{
		put_in_arena(player[i], gb->(char*)arena, nb_player);
		i++;
	}
}

static int get_player(t_global *gb)
{
	int i;

	i = 0;
	while ((gb->player[i]) != NULL)
		i++;
	put_player((t_player**)(gb->player), gb->arena, i);
	return (1);
}

void load_player(t_global *gb)
{
	set_arena(gb);
	get_player(gb);
	ft_printf("%s", gb->(char*)arena);
}

