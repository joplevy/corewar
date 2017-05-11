#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

void	c(t_list *args);
void	d(t_list *args);

typedef enum	e_type
{
	file,
	string,
	number,
	opt
}				t_type;

typedef struct	s_arg
{
	t_type	type;
	char	*opt;
	int		fd;
	int		err;
	char	*str;
	int		val;
}				t_arg;

typedef struct	s_opt
{
	char		*name;
	char		*args;
}				t_opt;

static t_opt	tab[4] = {
	{"c", ""},
	{"d", "i"},
	{"f", "fis"},
	{"", ""}
};

// possible types : i int | s str | f file

int		ft_match(char *str, t_opt *tab)
{
	int		i;

	i = -1;
	while (ft_strlen(tab[++i].name) > 0)
		if (ft_strcmp(str, tab[i].name) == 0)
			return (i);
	return (-1);
}

t_arg	ft_newarg(char type, char *str)
{
	t_arg	ret;

	if (type == 'o')
		ret.type = opt;
	else if (type == 'i')
		ret.type = number;
	else if (type == 's')
		ret.type = string;
	else if (type == 'f')
		ret.type = file;
	ret.opt = (type == 'o') ? str + 1 : NULL;
	ret.fd = (type == 'f') ? open((const char*)str, O_RDONLY) : 0;
	ret.err = (type == 'f') ? errno : 0;
	ret.str =  str;
	ret.val = (type == 'i') ? ft_atoi(str) : 0;
	return (ret);
}

int		ft_get_opt_args(char **av, int *i, t_list **lst, t_opt o)
{
	int		j;
	t_arg	arg;

	j = -1;
	while ((o.args)[++j])
	{
		if ((o.args)[j] == 'i')
		{
			arg = ft_newarg('i', av[++(*i)]);
			ft_lstadd_back(lst, ft_lstnew(&arg, sizeof(t_arg)));
		}
		else if ((o.args)[j] == 's')
		{
			arg = ft_newarg('s', av[++(*i)]);
			ft_lstadd_back(lst, ft_lstnew(&arg, sizeof(t_arg)));
		}
		else if ((o.args)[j] == 'f')
		{
			arg = ft_newarg('f', av[++(*i)]);
			ft_lstadd_back(lst, ft_lstnew(&arg, sizeof(t_arg)));
		}
		else
			return (0);
	}
	return (1);
}

t_list	*ft_get_args(int ac, char **av, t_opt *tab, char elsetype)
{
	t_list	*ret;
	int		i;
	int		opt;
	t_arg	arg;

	i = 0;
	ret = NULL;
	if (elsetype != 'i' &&  elsetype != 'f' && elsetype != 's')
		return (NULL);
	while (++i < ac)
	{
		if (av[i][0] == '-' && (opt = ft_match(av[i] + 1, tab)) >= 0)
		{
			arg = ft_newarg('o', av[i]);
			ft_lstadd_back(&ret, ft_lstnew(&arg, sizeof(t_arg)));
			if (i + ft_strlen(tab[opt].args) >= ac)
				return (NULL);
			if (!(ft_get_opt_args(av, &i, &ret, tab[opt])))
				return (NULL);
		}
		else
		{
			arg = ft_newarg(elsetype, av[i]);
			ft_lstadd_back(&ret, ft_lstnew(&arg, sizeof(t_arg)));
		}
	}
	return (ret);
}

int		main(int ac, char **av)
{
	t_list	*lst;

	if (ac > 1)
	{
		lst = ft_get_args(ac, av, tab, 's');
		while(lst)
		{
			printf("{\n type=%d\n opt=%s\n fd=%d\n err=%d\n str=%s\n val=%d\n}\n\n", ((t_arg *)(lst->content))->type, ((t_arg *)(lst->content))->opt, ((t_arg *)(lst->content))->fd,((t_arg *)(lst->content))->err, ((t_arg *)(lst->content))->str, ((t_arg *)(lst->content))->val);
			lst = lst->next;
		}
	}
	return (0);
}
