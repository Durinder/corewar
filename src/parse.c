/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:27:54 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/21 22:29:02 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "corewar.h"

/*
** checks whether the number associated with a flag is valid and returns it
**
** @arg: the argument after the flag
** @is_playernum: true if the flag in question was n, false otherwise
*/
static int	get_flag_cycles(const char *arg, int is_playernum)
{
	int cycles;

	cycles = ft_atoi(arg);
	if (cycles <= 0 || (is_playernum && cycles > MAX_PLAYERS))
	{
		print_usage();
		exit(-1);
	}
	return (cycles);
}

/*
** checks if the passed argument is a valid flag and stores the number of
** cycles associated with it to the core struct, also passed to this function
**
** @argv: vector of program arguments
** @count: pointer to the index of the current argument in argv
** @core: pointer to a t_core struct
*/
static void	store_flag(const char **argv, int *count, t_core *core)
{
	if (ft_strequ(argv[*count], "-dump"))
		core.dump = get_flag_cycles(argv[++(*count)], 0);
	else if (ft_strequ(argv[*count], "-s"))
		core.split = get_flag_cycles(argv[++(*count)], 0);
	else if (ft_strequ(argv[*count], "-v"))
		core.verbose = get_flag_cycles(argv[++(*count)], 0);
	else if (ft_strequ(argv[*count], "-n"))
		core.player_number = get_flag_cycles(argv[++(*count)], 1);
	else
		print_usage();
	return (count + 1);
}

t_champs	parse_args(const int argc, const char **argv, t_core *core)
{
	t_champs	*champs;
	int			count;

	champs = NULL;
	count = 0;
	while (++count < argc)
	{
		if (argv[count][0] == '-')
		{
			if (argv[count][1] == 'a')
				core.aff = 1;
			else if (count + 1 < argc)
				store_flag(argv, &count, core);
			else
				print_usage();
		}
		else
		{
			champs = read_cor(argv[count], core);
			if (!champs)
				return (NULL);
			champs = champs->next;
		}
	}
	return (champs);
}
