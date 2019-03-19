/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 12:23:00 by oozkaya           #+#    #+#             */
/*   Updated: 2019/03/05 18:22:40 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Sets the player alive according to the ID given
**
** @param env: Context structure
** @param id: ID read on the arena
*/

static void			set_alive(t_env *env, unsigned int id)
{
	t_player *p;

	p = env->player;
	while (p)
	{
		if (id == p->id)
		{
			p->alive = 1;
			p->last_live = env->cycle;
			p->lives_curr++;
			env->plast_live = p;
			return ;
		}
		p = p->next;
	}
}

/*
** @brief: Gets the ID read in the arena
**
** @param env: Context structure
** @param proc: Processors structure
** @return unsigned int
*/

static unsigned int	get_id(t_env *env, t_proc *proc)
{
	unsigned int	id;

	proc->pc++;
	id = ((env->arena[proc->pc % MEM_SIZE] << 24)
		| (env->arena[(proc->pc + 1) % MEM_SIZE] << 16)
		| (env->arena[(proc->pc + 2) % MEM_SIZE] << 8)
		| env->arena[(proc->pc + 3) % MEM_SIZE]);
	set_alive(env, id);
	if (id & 0x80000000)
		id = id - 0xFFFFFFFF - 1;
	proc->pc += 4;
	return (id);
}

/*
** @brief: Resets lives of every players
**
** @param env: Context structure
*/

void				reset_livescycle(t_env *env)
{
	t_player *p;

	p = env->player;
	while (p)
	{
		p->lives_last = p->lives_curr;
		p->lives_curr = 0;
		p->alive = 0;
		p = p->next;
	}
}

/*
** @brief: Indicates that the player is alive
**
** @param env: Context structure
** @param proc: Processors structure
*/

void				ft_live(t_env *env, t_proc *proc)
{
	unsigned int		id;

	op_intro(proc, OP_LIVE, CH_LIVE);
	if (proc->working && !proc->charge)
	{
		proc->first_pc = proc->pc;
		id = get_id(env, proc);
		verbose_intro(env, "live", proc->nbr);
		printer(env, 0, " %d\n", id);
		verbose_outro(env, proc->first_pc, 5);
		proc->live = 1;
		env->nbr_live++;
		visu_movepc(env, proc);
		proc->working = 0;
	}
	else
		proc->charge--;
}
