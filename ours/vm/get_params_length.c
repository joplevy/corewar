#include <corewar.h>

int			get_type_size(t_vmtype type)
{
	if (type == ind)
		return (IND_SIZE);
	if (type == dir)
		return (DIR_SIZE);
	if (type == reg)
		return (REG_SIZE);
	return (0);
}

t_vmtype	get_type(unsigned char ocp, int	pos)
{
	ocp = ocp >> (6 - (pos * 2));
	if ((ocp & 0x03) == IND_CODE)
		return (ind);
	if ((ocp & 0x03) == DIR_CODE)
		return (dir);
	if ((ocp & 0x03) == REG_CODE)
		return (reg);
	return (!ocp ? tnul : terr);
}

int			get_params_length(int adr, unsigned char *arena)
{
	unsigned char	opc;
	unsigned char	ocp;
	int				i;
	int				ret;
	t_vmtype		t;	

	ret = 0;
	ocp = 0;
	if (adr < 0 || adr >= MEM_SIZE || (opc =  *(arena + adr)) < 1 || opc > 16)
		return (ret);
	if (!OP_OCP((int)opc))
		return (DIR_SIZE);
	ocp = *(arena + (adr + 1 == MEM_SIZE ? 0 : adr + 1));
	i = -1;
	while (++i < OP_NBP((int)opc))
	{
		if ((t = get_type(ocp, i)) == terr)
			return (0);
		ret += get_type_size(t);
	}
	return (ret + 1);
}
