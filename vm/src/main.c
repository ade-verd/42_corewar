/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 11:08:13 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/20 11:20:28 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void	help(void)
{
	ft_printf("Usage\t./corewar [-havdDsc [cycle_nb]] [-n nb] file.cor ...\n");
	ft_printf("Executes all the given '.cor' files, the champions, "\
		"to make them fight (maximum 4 champions)\n");
	ft_printf("——————\n");
	ft_printf("-hH\t[Help] Displays this help\n");
	ft_printf("-aA\t[Aff] Prints output from 'aff' (Default is to hide it)\n");
	ft_printf("-vV\t[Verbose] Enables the verbose mode\n");
	ft_printf("-d (i)\t[dump] Dumps a 32x128 arena after i cycles\n");
	ft_printf("-D (i): [Dump] Dumps a 64x64 arena with player's colors\n");
	ft_printf("-sS (i)\t[Sleep] Runs i cycles, dumps memory, waits for "\
		"an user action, then repeats\n");
	ft_printf("-cC [i]\t[nCurses] Enables the Ncurses visual mode\n");
	ft_printf("\t -cC [i]: Starts at cycle i. i has to be bigger than 0\n");
	ft_printf("\tThe Ncurses option disables dump options (-dD)\n");
	ft_printf("-nN (i)\t[Nplayer] Sets the next champion's number at i.\n");
}

int		main(int ac, char **av)
{
	t_env	*env;

	if (ac > 1)
	{
		s_env_init(&env);
		check_argv(env, ac, av);
		if (env->flags & FLAG_HELP || !env->players_amount)
			usage_exit(env, "NO", 0);
		if (!env->goto_cycle)
			visu_init(env);
		read_argv(env, ac, av);
		options_compatibility(env);
		process_init(env);
		ft_process(env);
		s_env_del(env);
	}
	else
	{
		help();
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
