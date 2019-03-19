/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 11:08:13 by ade-verd          #+#    #+#             */
/*   Updated: 2019/02/20 11:56:49 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief: Main function
**
** @param ac: Arg count
** @param av: Arg values
** @return int: Exit_Success or Exit_Failure
*/

int		main(int ac, char **av)
{
	t_env	*env;

	if (ac > 1)
	{
		s_env_init(&env);
		read_args(env, ac, av);
		deal_help_debug(env);
		open_input(env);
		read_fd(env);
		parse_sstr(env);
		env->flags & FLAG_ANNOTED ? interpret_annoted(env) : interpret_bin(env);
		close_in_output(env);
		s_env_del(env);
	}
	else
	{
		help();
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
