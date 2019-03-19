/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 18:30:07 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/06 17:43:01 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief: Initializes env
**
** @param env: Main context structure t_env
*/

void	s_env_init(t_env **env)
{
	if (!(*env = (t_env*)malloc(sizeof(t_env))))
		error(*env, (char*)__FUNCTION__, 1);
	(*env)->input = NULL;
	(*env)->output = NULL;
	(*env)->flags = 0;
	(*env)->fd_in = -1;
	(*env)->fd_out = 1;
	(*env)->sstr = NULL;
	(*env)->inst = NULL;
	ft_memset(&(*env)->header, 0, sizeof(t_header));
	(*env)->header.magic = COREWAR_EXEC_MAGIC;
	(*env)->asmb = NULL;
	(*env)->err = NULL;
}

/*
** @brief: Frees t_env
**
** @param env: Main context structure t_env
*/

void	s_env_del(t_env *env)
{
	if (env && env->input)
		ft_strdel(&env->input);
	if (env && env->output)
		ft_strdel(&env->output);
	if (env && env->sstr)
		ft_strdel(&env->sstr);
	if (env && env->asmb)
		s_asm_del(env->asmb);
	if (env && env->err)
		ft_strdel(&env->err);
	if (env)
		ft_memdel((void**)&env);
}
