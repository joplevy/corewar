
#include <corewar.h>

void			check_lives(t_global *global)
{
	t_list		*tmp;

	tmp = global->procs;
	while (tmp != NULL)
		if (!ACC(tmp, live))
			delete_process(global->procs, tmp);
	if (global->lives > NBR_LIVE || global->checks == MAX_CHECKS)
	{
		global->ctd -= CYCLE_DELTA;
		global->checks = 0;
	}
	global->lives = 0;
}