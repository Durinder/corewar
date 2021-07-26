/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 16:09:28 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/26 13:16:25 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_core	init_core(void)
{
	t_core	core;

	core.aff = 0;
	core.dump = 0;
	core.split = 0;
	core.verbose = 0;
	core.champ_count = 0;
	core.player_number = 0;
	core.program_counter = 0x0;
	core.carry = 0;
	return (core);
}

int	main(int argc, char **argv)
{
	t_core		core;
	t_champs	champs[MAX_PLAYERS];

	if (argc == 1)
		print_usage();
	core = init_core();
	parse_args(argc, argv, &core, champs);
	if (core.champ_count == 0)
		print_usage();
	return (0);
}
