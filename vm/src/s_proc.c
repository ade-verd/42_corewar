/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_proc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:25:30 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/05 19:29:15 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Returns a t_player* corresponding to nplayer
**
** @param env: Context structure
** @param nplayer: Nplayer identification
** @return t_player*
*/

t_player		*s_proc_whplayer(t_env *env, unsigned int nplayer)
{
	t_player	*p;

	p = env->player;
	while (p)
	{
		if (p->nplayer == nplayer)
			return (p);
		p = p->next;
	}
	return (NULL);
}

/*
** @brief: Creates the new process
**
** @param env: Context structure
** @param nplayer: Nplayer identification
** @return t_proc*
*/

t_proc			*s_proc_new(t_env *env, unsigned int nplayer)
{
	t_proc		*new;
	t_player	*p;
	int			i;

	if (!(new = (t_proc*)malloc(sizeof(t_proc))))
		error(env, (char*)__FUNCTION__, 1);
	if ((p = s_proc_whplayer(env, nplayer)))
		p->procs++;
	new->nbr = env->proc ? env->proc->nbr + 1 : 1;
	new->first_pc = 0;
	new->pc = 0;
	i = 0;
	new->reg[i++] = nplayer;
	while (i < REG_NUMBER)
		new->reg[i++] = 0;
	new->charge = 0;
	new->working = 0;
	new->carry = 0;
	new->live = 0;
	new->next = env->proc;
	env->proc = new;
	env->nbproc++;
	return (new);
}

/*
** @brief:Fork process
**
** @param env: Context structure
** @param proc: Processors structure
** @return t_proc*
*/

t_proc			*s_proc_fork(t_env *env, t_proc *proc)
{
	t_proc	*new;
	int		i;

	new = s_proc_new(env, proc->reg[0]);
	new->first_pc = proc->pc;
	new->pc = proc->pc;
	new->charge = proc->charge;
	i = -1;
	while (++i < REG_NUMBER)
		new->reg[i] = proc->reg[i];
	new->carry = proc->carry;
	new->live = proc->live;
	return (new);
}

/*
** @brief: Deletes only the given proc
**
** @param env: Context structure
** @param p: Given proc
*/

void			s_proc_delone(t_env *env, t_proc *p)
{
	t_proc		*curr;
	t_proc		*prev;
	t_player	*plyr;

	curr = env->proc;
	prev = NULL;
	plyr = NULL;
	while (curr)
	{
		if (curr->nbr == p->nbr)
		{
			if (prev)
				prev->next = curr->next;
			else
				env->proc = curr->next;
			if ((plyr = s_proc_whplayer(env, curr->reg[0])))
				plyr->procs--;
			visu_killpc(env, curr);
			ft_memdel((void**)&curr);
			env->nbproc--;
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

/*
** @brief: Deletes all the processors
**
** @param env: Context structure
*/

void			s_proc_del(t_env *env)
{
	t_proc		*curr;
	t_proc		*next;

	curr = env->proc;
	while (curr)
	{
		next = curr->next;
		ft_memdel((void**)&curr);
		env->nbproc--;
		curr = next;
	}
}
