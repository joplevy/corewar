#include <corrwar.h>

int		read_name(int fd, t_players *player)
{
	int size;
	char *name = NULL;

	size = read(fd, name, PROG_NAME_LENGTH);
	if (!(player->name = (char*)malloc(sizeof(char) * size + 1)))
		return (1);
	player->name = ft_strjoin(name, "\0");
	return (0);
}

int		read_comment(int fd, t_players *player)
{
	int size;
	char *comment;

	if (size = read(fd, comment, COMMENT_LENGTH) < 0)
		return (1);
	if (!(player->comment = (char*)malloc(sizeof(char) * size + 1)))
		return (1);
	player->comment = ft_strjoin(comment, "\0");
	return (0);
}

int		read_code(int fd, t_players *player, char *size)
{
	int i;
	char *code;

	while (player->end += read(fd, code, 1) < 0)
		ft_strjoin(player->code, code);
	if (!(player->code = (char*)malloc(sizeof(char) * size + 1)))
		return (1);
	player->code = ft_strjoin(code, "\0");
	return (0);
}

int					check_magic(int fd)
{
	char a;
	char b;
	char c;
	char d;
	char *s = NULL;

	a = 0x0
	b = 0xea
	c = 0x83
	d = 0xf3;
	if (read(fd, s, 4) =< 0)
		return (1);
	if (ft_strncmp(a, s[0], 1) != 0 || ft_strncmp(b, s[1], 1) != 0 
	|| ft_strncmp(c, s[2], 1) != 0 || ft_strncmp(a, s[0], 1) != 0)
		retur (1);
	return (0);
}

int get_info_player(int fd, t_players *player)
{
	if (check_magic(fd) == 1)
		return (1);
	if (read_name(fd, player) == 1)
		return (1);
	if (read_comment(fd, player) == 1)
		return (1);
	if (read_code(fd, player) == 1)
		return (1);
}
