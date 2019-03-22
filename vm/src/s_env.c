/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:10:46 by oozkaya           #+#    #+#             */
/*   Updated: 2019/03/22 10:50:01 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Initializes env
**
** @param env: Main context structure t_env
*/

#include <string.h>

void			s_env_init(t_env **env)
{
	int	i;

	i = 0;
	if (!(*env = (t_env*)malloc(sizeof(t_env))))
		error(*env, (char*)__FUNCTION__, 1);
	ft_bzero(*env, sizeof(t_env));
	ft_bzero((*env)->arena, MEM_SIZE);
	ft_bzero((*env)->color, MEM_SIZE);
	while (i < (SCRH + 1))
		ft_bzero((*env)->buf[i++], TRMW + 1);
	ft_bzero(&(*env)->pid, sizeof(t_playerid));
	(*env)->cycle_to_die = CYCLE_TO_DIE;
	if (!((*env)->aff = (t_buffer*)malloc(sizeof(t_buffer))))
		error(*env, (char*)__FUNCTION__, 1);
	ft_bzero((*env)->aff, sizeof(t_buffer));
	if (!((*env)->aff->str = (char*)malloc(sizeof(char) * 4096)))
		error(*env, (char*)__FUNCTION__, 1);
	ft_bzero((*env)->aff->str, sizeof(char) * 4096);
}

/*
** @brief: Frees t_env
**
** @param env: Main context structure t_env
*/

void			s_env_del(t_env *env)
{
	if (env && env->err)
		ft_strdel(&env->err);
	if (env && env->proc)
		s_proc_del(env);
	if (env && env->player)
		s_player_del(env);
	if (env && env->aff)
	{
		if (env->aff->str)
			ft_strdel(&env->aff->str);
		ft_memdel((void**)&env->aff);
	}
	if (env && env->gph)
		visu_end(env);
	if (env)
		ft_memdel((void**)&env);
}
