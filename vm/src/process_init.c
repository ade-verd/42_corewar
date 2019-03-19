/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:41:48 by oozkaya           #+#    #+#             */
/*   Updated: 2019/03/05 18:00:23 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Creates all the processors
**
** @param env: Context structure
*/

static void			create_all_process(t_env *env)
{
	t_player	*p;

	p = env->player;
	while (p)
	{
		s_proc_new(env, p->nplayer);
		p = p->next;
	}
}

/*
** @brief: Returns the right champion size
**
** @param env: Context structure
** @param index: Champion index
** @return unsigned int
*/

static unsigned int	get_progsize(t_env *env, unsigned int index)
{
	t_player		*p;
	unsigned int	i;

	i = 1;
	p = env->player;
	while (env && p && i <= index)
	{
		if (i == index)
			return (p->header.prog_size);
		p = p->next;
		i++;
	}
	return (0);
}

/*
** @brief: Initializes proc
**
** @param env: Context structure
*/

void				process_init(t_env *env)
{
	int		i;
	int		j;
	int		nbr;
	t_proc	*curr;

	create_all_process(env);
	i = 0;
	j = (MEM_SIZE / env->players_amount) * (env->players_amount - 1);
	nbr = env->players_amount;
	curr = env->proc;
	while (++i <= env->players_amount)
	{
		curr->pc = j;
		curr->first_pc = j;
		curr->live = 0;
		visu_colorized(env, curr, get_progsize(env, nbr--), curr->pc);
		visu_movepc(env, curr);
		curr = curr->next;
		j -= MEM_SIZE / env->players_amount;
	}
	ft_wrefresh(env);
}
