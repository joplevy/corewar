// utilities

int		ft_load(t_global *gb, int size, int adress)
{
	int		param;

	param = 0;
	while (adress < 0)
		adress += MEM_SIZE;
	if (size == 1)
		param = gb->arena[(adress) % MEM_SIZE];
	else if (size == 2)
	{
		param = ((bg->arena[(adress + 1) % MEM_SIZE]));
		param |= ((gb->arena[(adress + 0) % MEM_SIZE]) << 8);
	}
	else
	{
		param = ((gb->arena[(adress + 3) % MEM_SIZE]));
		param |= ((gb->arena[(adress + 2) % MEM_SIZE]) << 8);
		param |= ((gb->arena[(adress + 1) % MEM_SIZE]) << 16);
		param |= ((gb->arena[(adress + 0) % MEM_SIZE]) << 24);
	}
	return (param);
}

// utilities

void	ft_store(t_global *gb, t_process *process, int adress)
{
	int value;

	value = process->regs[process->param[0] - 1];
	if (adress < 0)
		adress = MEM_SIZE + adress;
	gb->arena[(adress + 3) % MEM_SIZE] = value;
	gb->arena[(adress + 2) % MEM_SIZE] = (value >> 8);
	gb->arena[(adress + 1) % MEM_SIZE] = (value >> 16);
	gb->arena[(adress + 0) % MEM_SIZE] = (value >> 24);
}


static int	get_param_value(t_process *process, int param, int *val, t_global *gb)
{
	if (process->param_type == T_REG)
	{
		if (process->param[param] >= 1 && process->param[param] <= 16)
			*val = process->regs[process->param[param] - 1];
		else
			return (0);
	}
	else if (process->param_type == T_DIR)
		*val = process->param[param];
	else
		*val = ft_load(gb, 4, process->adress + process->param[param] % IDX_MOD);
	return (1);
}

// zjump

void	ft_zjmp(t_process *process)
{
	if (process->carry == 1)
	{
		process->adress2 = process->adress + ((short)process->param[0] % IDX_MOD);
		process->adress2 %= MEM_SIZE;
	}
	else
		process->adress2 = (process->adress + 3) % MEM_SIZE;
}

// xor

void		ft_xor(t_global *gb, t_process *process)
{
	int		val1;
	int		val2;

	if (process->param[2] >= 1 && process->param[2] <= 16)
	{
		if (!get_param_value(process, 0, &val1, gb) ||
			!get_param_value(process, 1, &val2, gb))
			return ;
		process->reg[process->param[2] - 1] = val1 ^ val2;
		process->carry = !process->reg[process->param[2] - 1];
	}
	else
		return ;
}

// sub

void	ft_sub(t_process *process)
{
	if (process->param[0] >= 1 && process->param[0] <= 16
		&& process->param[1] >= 1 && process->param[1] <= 16
		&& process->param[2] >= 1 && process->param[2] <= 16)
	{
		process->regs[process->param[2] - 1] =
			process->regs[process->param[0] - 1] -
			process->regs[process->param[1] - 1];
		process->carry = !process->regs[process->param[2] - 1];
	}
	else
		;
}

// sti

void		ft_sti(t_global *gb, t_process *process)
{
	int		val1;
	int		val2;
	int		adress;

	if (process->param[0] >= 1 && process->param[0] <= 16)
	{
		if (!get_param_value(gb, process, 1, &val1) ||
			!get_param_value(gb, process, 2, &val2))
			return ;
		adress = (process->adress + ((val1 + val2) % IDX_MOD));
		ft_store(gb, process, adress);
	}
	else
		return ;
}

// st

void		ft_st(t_global *gb, t_process *process)
{
	int		adress;

	if (process->param[0] >= 1 && process->param[0] <= 16)
	{
		if (process->param_type[1] == 1)
		{
			if (process->param[1] >= 1 && process->param[1] <= 16)
			{
				process->regs[process->param[1] - 1] =
					process->regs[process->param[0] - 1];
			}
			else
				return ;
		}
		adress = (process->adress + (process->param[1] % IDX_MOD)) % MEM_SIZE;
		ft_store(vm, process, adress);
	}
	else
		return ;
}

// or

void		ft_or(t_global *gb, t_process *process)
{
	int		val1;
	int		val2;

	if (process->param[2] >= 1 && process->param[2] <= 16)
	{
		if (!get_param_value(process, 0, &val1, gb) ||
			!get_param_value(process, 1, &val2, gb))
			return ;
		process->regs[process->param[2] - 1] = val1 | val2;
		process->carry = !process->reg[process->param[2] - 1];
	}
	else
		return ;
}

// lldi

void		ft_lldi(t_global *gb, t_process *process)
{
	int		val1;
	int		val2;
	int		adress;

	if (process->param[2] >= 1 && process->param[2] <= 16)
	{
		if (!get_param_value(process, 0, &val1, gb) ||
			!get_param_value(process, 1, &val2, gb))
			return ;
		adress = (process->adress + (val1 + val2)) % MEM_SIZE;
		if (adress < 0)
			adress += MEM_SIZE;
		process->regs[process->param[2] - 1] = ft_load(vm, 4, adress);
		process->carry = !process->reg[process->param[2] - 1];
	}
	else
		return ;
}

// lld

void	ft_lld(t_global *gb, t_process *process)
{
	int		adress;

	if (process->param[1] >= 1 && process->param[1] <= 16)
	{
		if (process->param_type == T_DIR)
			process->regs[process->param[1] - 1] = process->param[0];
		else
		{
			adress = (process->adress + process->param[0]) % MEM_SIZE;
			if (adress < 0)
				adress += MEM_SIZE;
			process->regs[process->param[1] - 1] =
				ft_load(vm, 4, adress);
		}
		process->carry = !process->regs[process->param[1] - 1];
	}
	else
		return ;
}

// live

void		ft_live(t_process *process)
{
	//process->cycles_wo_live = 0; a implementer
	process->live++;
}

// lfork

static void	ft_lfork2(t_global *gb, t_process *process, t_process *new_process,
	t_list *lst)
{
	new_process->carry = process->carry;
	lst->content = new_process;
	lst->next = NULL;
	lst->content_size = sizeof(t_list);
	ft_lstadd(&gb->processes, lst);
}

void		ft_lfork(t_global *gb, t_process *process)
{
	t_list		*lst;
	t_process	*new_process;

	lst = NULL;
	if (((new_process = (t_process*)malloc(sizeof(t_process))) == NULL) ||
		((lst = (t_list *)malloc(sizeof(t_list))) == NULL))
		exit(0);
	ft_copy_reg(new_process, process);
	new_process->adress =
		(short)(process->adress + (short)process->param[0]) % MEM_SIZE;
	if (new_process->adress < 0)
		new_process->adress += MEM_SIZE;
	ft_lfork2(gb, process, new_process, lst);
}

// ldi

void		ft_ldi(t_global *gb, t_process *process)
{
	int		val1;
	int		val2;
	int		adress;

	if (process->param[2] >= 1 && process->param[2] <= 16)
	{
		if (!get_param_value(process, 0, &val1, vm) ||
			!get_param_value(process, 1, &val2, vm))
			return ;
		adress = (process->adress + (val1 + val2) % IDX_MOD);
		if (adress < 0)
			adress += MEM_SIZE;
		process->regs[process->param[2] - 1] = ft_load(vm, 4, adress % MEM_SIZE);
	}
	else
		return ;
}

// ld

void	ft_ld(t_process *process)
{
	int		adress;

	if (process->param[1] >= 1 && process->param[1] <= 16)
	{
		if (process->param_type == T_DIR)
			process->regs[process->param[1] - 1] = process->param[0];
		else
		{
			adress = (process->adress + process->param[0] % IDX_MOD) % MEM_SIZE;
			if (adress < 0)
				adress += MEM_SIZE;
			process->regs[process->param[1] - 1] =
				ft_load(gb, 4, adress);
		}
		process->carry = !process->regs[process->param[1] - 1];
	}
	else
		;
}

// fork

static void	ft_fork2(t_global *gb, t_process *process, t_process *new_process,
	t_list *lst)
{
	new_process->carry = process->carry;
	ft_copy_reg(new_process, process);
	lst->content = new_process;
	lst->next = NULL;
	lst->content_size = sizeof(t_list);
	ft_lstadd(&vm->processes, lst);
}

void		ft_fork(t_global *gb, t_process *process)
{
	t_list		*lst;
	t_process	*new_process;

	lst = NULL;
	if (((new_process = (t_process*)malloc(sizeof(t_process))) == NULL) ||
		((lst = (t_list *)malloc(sizeof(t_list))) == NULL))
		exit(0);
	new_process->adress =
		(process->adress + ((short)process->param[0] % IDX_MOD)) % MEM_SIZE;
	if (new_process->adress < 0)
		new_process->pc += MEM_SIZE;
	ft_fork2(gb, process, new_process, lst);
}


// and

void		ft_and(t_global *gb, t_process *process)
{
	int		val1;
	int		val2;

	if (process->param[2] >= 1 && process->param[2] <= 16)
	{

		if (!get_param_value(process, 0, &val1, gb) ||
			!get_param_value(process, 1, &val2, gb))
			;
		else
		{
			process->regs[process->param[2] - 1] = val1 & val2;
			process->carry = !process->regs[process->param[2] - 1];
		}
	}
	else
		;
}


// aff

void		ft_aff(t_process *process)
{
	if (process->param[0] >= 1 && process->param[0] <= 16)
		ft_printf("Aff: %c", process->regs[process->param[0] - 1] % 256);
	else
		;
}

// add

void	ft_add(t_process *process)
{
	if (process->param[0] >= 1 && process->param[0] <= 16
		&& process->param[1] >= 1 && process->param[1] <= 16
		&& process->param[2] >= 1 && process->param[2] <= 16)
	{
		process->reg[process->param[2] - 1] =
			process->regs[process->param[0] - 1] +
			process->regs[process->param[1] - 1];
		process->carry = !process->regs[process->param[2] - 1];
	}
	else
		;
}
