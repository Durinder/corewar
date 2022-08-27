/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 16:09:28 by rkyttala          #+#    #+#             */
/*   Updated: 2022/08/28 00:04:15 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** prints the arena to STDOUT after a specific amount of execution cycles if the
** program was launched with the -dump flag
**
** @arena: pointer to the start of the arena
** @size: amount of bytes to print out
*/
void	dump_memory(const unsigned char *arena, int size)
{
	int	i;
	int	j;
	int	row_len;
	int	address;

	i = 0;
	row_len = 32;	// row_len according to subject
	row_len = 64;	// delete this row once program works as intended
	j = row_len - 1;
	address = 0;
	ft_printf("0x0000 :");
	while (i < size)
	{
		if (arena[i] != 0)
			ft_printf(" \033[92m%02x\033[0m", arena[i]);
		else
			ft_printf(" %02x", arena[i]);
		if (i == j && i != (size - 1))
		{
			address += row_len;
			ft_printf("\n%#06x :", address);
			j += row_len;
		}
		i++;
	}
	ft_putchar('\n');
}

static void	introduce_champs(t_champ *champs, int champ_count)
{
	int	i;

	ft_printf("Introducing contestants...\n");
	i = 0;
	while (i < champ_count)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\")!\n", \
		champs[i].playernbr, champs[i].size, champs[i].name, champs[i].comment);
		i++;
	}
}

static void	init_arena(t_champ *champs, int champ_count, unsigned char *arena)
{
	int				i;
	int				pos;

	i = 0;
	pos = 0;
	ft_bzero(arena, MEM_SIZE);
	while (i < champ_count)
	{
		ft_memcpy(&arena[pos], champs[i].exec, champs[i].size);
		pos += MEM_SIZE / champ_count;
		i++;
	}
	introduce_champs(champs, champ_count);
}

static t_flags	init_flags(void)
{
	t_flags	flags;
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		flags.used_nbrs[i] = 0;
		i++;
	}
	flags.dump = 0;
	flags.split = 0;
	flags.verbose = 0;
	flags.champ_count = 0;
	flags.playernbr = -1;
	return (flags);
}

int	main(int argc, char **argv)
{
	t_flags			flags;
	t_champ			champs[MAX_PLAYERS];
	unsigned char	arena[MEM_SIZE];
	int				winner;

	if (argc == 1)
		print_usage();
	flags = init_flags();
	parse_args(argc, argv, &flags, champs);
	if (flags.champ_count == 0)
		print_usage();
	sort_champs(champs, flags.champ_count);
	init_arena(champs, flags.champ_count, arena);
	winner = start_game(flags, arena, champs);
	if (winner > 0)
		ft_printf("Player %d (%s) has won!\n", winner, champs[winner - 1].name);
	else if (winner < 0)
		print_error(winner, NULL, NULL);
	else
		dump_memory(arena, MEM_SIZE);
	return (0);
}
