
#include "corewar.h"

int				main(int argc, char **argv)
{
	t_global		*global;

	if ((global = init_global) == NULL || !set_global(argc, argv, global))
		return (main_error(&global));
	play(global);
	clear_main(&global);
	return (0);
}