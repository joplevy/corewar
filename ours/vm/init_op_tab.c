#include <corewar.h>

void		init_tab_instruction(t_global *gb)
{
	gb->f[0] = ft_live;
	gb->f[1] = ft_ld;
	gb->f[2] = ft_st;
	gb->f[3] = ft_add;
	gb->f[4] = ft_sub;
	gb->f[5] = ft_and;
	gb->f[6] = ft_or;
	gb->f[7] = ft_xor;
	gb->f[8] = ft_zjmp;
	gb->f[9] = ft_ldi;
	gb->f[10] = ft_sti;
	gb->f[11] = ft_fork;
	gb->f[12] = ft_lld;
	gb->f[13] = ft_lldi;
	gb->f[14] = ft_lfork;
	gb->f[15] = ft_aff;
}
