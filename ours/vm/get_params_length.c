#include <corewar.h>

int			get_type_size(t_vmtype type)
{
	if (type == ind)
		return (IND_SIZE);
	if (type == dir)
		return (DIR_SIZE);
	return (REG_SIZE);
}

t_vmtype	get_type(unsigned char ocp, int	pos)
{
	ocp = ocp >> (6 - (pos * 2));
	if (ocp & 0x03 == IND_CODE)
		return (ind);
	if (ocp & 0x03 == DIR_CODE)
		return (dir);
	if (ocp & 0x03 == REG_CODE)
		return (reg);
	return (-1);
}

int			get_params_length(int adress, unsigned char *arena)
{
	unsigned char	opcode;
	unsigned char	ocp;
	int				i;
	int				ret;
	t_vmtype		t;	

	ret = 0;
	ocp = 0;
	opcode = *(arena + adress);
	if (opcode < 1 || opcode > 16)
		return (ret);
	if (!OP_OCP((int)opcode))
		return (def_op_size((int)opcode));
	ocp = *(arena + adress + 1);
	i = -1;
	while (++i < OP_NBP((int)opcode))
	{
		if ((t = get_type(ocp, i)) < 0)
			return (0);
		ret += get_type_size(t);
	}
	return (ret);
}
