#include "corewar.h"

int				ft_strupcpy(unsigned char *arena, char *code, int len, int pos)
{
	int			i;

	i = 0;
	while (i <= len)
	{
		if (pos + i > MEM_SIZE)
			return (0);
		arena[pos + i] = code[i];
		++i;
	}
	return (1);
}

static int		put_players(t_global *gb, int nb_players)
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
		((gb->players)[i])->entry = pos;
		if (!ft_strupcpy(gb->arena, ((gb->players)[i])->code, \
								((gb->players)[i])->size, pos))
			return  (0);
	}
	return (1);
}

int				intit_new_proc(t_player *pl, t_list **list)
{
	t_list		*new;
	int			i;
	int			j;

	if ((new = (t_list*)malloc(sizeof(t_list))) == NULL)
		return (0);
	new->content_size = sizeof(t_process);
	if ((new->content = malloc(new->content_size)) == NULL)
		return (0);
	ACC(new, player) = pl->id;
	i = -1;
	while (++i < REG_NUMBER)
	{
		j = -1;
		while (++j < REG_SIZE)
			ACC(new, regs)[i][j] = 0;
	}
}

int				load_players(t_global *gb)
{
	int			i;

	i = 0;
	while ((gb->players)[i] != NULL)
		i++;
	if (!put_players(gb, i))
		return (0);
	i = -1;
	while ((gb->players)[i] != NULL)
		if (!intit_new_proc((gb->players)[i], &(gb->procs)))
			return (0);
	return (1);
}
