#include <corrwar.h>

int		read_name(int fd, t_players *player)
{
	//probable utilisation du gnl
	//recupe le nom et le mais dans player->name
	//probablement un petit parsing pour voir si c'est que des LABEL_CHARS le nom
	//envoie ensuite aux commente si gnl si non direction => < > du fd(valeur fixe)
}

int		read_comment(int fd, t_players *player)
{
	//recupe le comment et place dans player->comment
	//continue le gnl jusqu'aux code
	//pareil petit parsing du LABEL_CHARS et si tj pas de gnl direction => < > du fd(valeur fixe)
}

int		read_code(int fd, t_players *player)
{
	//un petit coups de memcpy dans player->code
	//on free, pas besoin de parsing, on recupe la taille du code ici <3
}

int					check_magic(int fd)
{
	char			*line = NULL;
	unsigned char	tab[3];

	tab[0] = 0;
	tab[1] = 234;
	tab[2] = 131;
	tab[3] = 243;
	if (get_next_line(fd, &line) < 0)
		exit_msg("failed to read files\n");
	if (ft_memcmp(line, tab, 4) != 0)
		exit_msg("not a magic word\n");
	free(line);
	//on peut même voir si le nom du champion corespond au nom du dossier, a discuter
}
