/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:42:21 by oozkaya           #+#    #+#             */
/*   Updated: 2019/03/13 16:10:23 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Checks for the procs who did the OP 'live'
**         and kills the ones who did not
**
** @param env: Context structure
*/

static void		who_is_alive(t_env *env)
{
	t_proc	*curr;
	t_proc	*next;

	curr = env->proc;
	while (curr)
	{
		next = curr->next;
		if (!curr->live)
			s_proc_delone(env, curr);
		else
			curr->live = 0;
		curr = next;
	}
}

/*
** @brief: Checks and returns the only player alive
**
** @param env: Context structure
** @return t_player*
*/

static t_player	*one_alive(t_env *env)
{
	t_player	*p;
	int			count;

	count = 0;
	p = env->player;
	while (p && count < 2)
	{
		if (p->alive)
			count++;
		p = p->next;
	}
	if (count == 1)
	{
		p = env->player;
		while (p)
		{
			if (p->alive)
				return (p);
			p = p->next;
		}
	}
	return (0);
}

/*
** @brief: Handles every needed tasks when CYCLE_TO_DIE is reached
**
** @param env: Context structure
** @param ctd: Actual cycle, reseted to 0 when CYCLE_TO_DIE is reached
*/

static void		cycle_checker(t_env *env, int *ctd)
{
	if (*ctd == env->cycle_to_die)
	{
		env->max_checks++;
		who_is_alive(env);
		if (env->max_checks == MAX_CHECKS || env->nbr_live >= NBR_LIVE)
		{
			env->cycle_to_die -= CYCLE_DELTA;
			printer(env, 0, "Cycle_to_die (%d) reached (%d Processes)\n",
				env->cycle_to_die, env->nbproc);
			env->max_checks = 0;
			reset_livescycle(env);
		}
		if ((one_alive(env) && env->cycle_to_die < 0) || !env->nbproc)
			env->cycle_to_die = -1;
		env->nbr_live = 0;
		*ctd = 0;
	}
}

/*
** @brief: Loops on every procs to make them execute their instructions
**
** @param env: Context structure
*/

static void		loop_allproc(t_env *env)
{
	t_proc	*curr;
	int		first_pc;
	int		j;

	curr = env->proc;
	while (curr)
	{
		j = -1;
		first_pc = curr->pc;
		while (!curr->working && g_op_tab[++j].op_code)
			if (env->arena[curr->pc] == g_op_tab[j].op_code)
			{
				g_op_tab[j].fct(env, curr);
				break ;
			}
		if (curr->working)
			g_op_tab[curr->working].fct(env, curr);
		else
			curr->first_pc = curr->pc++;
		curr->pc = curr->pc % MEM_SIZE;
		visu_movepc(env, curr);
		curr = curr->next;
	}
}

/*
** @brief: Corewar's main function dealing with the whole tasks
**
** @param env: Context structure
*/

void			ft_process(t_env *env)
{
	int		ctd;

	ctd = 0;
	while (env->cycle_to_die > 0)
	{
		env->cycle++;
		ctd++;
		printer(env, 0, "It is now cycle %d\n", env->cycle);
		deal_options(env);
		loop_allproc(env);
		cycle_checker(env, &ctd);
	}
	winner(env, one_alive(env));
}
