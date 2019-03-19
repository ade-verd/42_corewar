/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 13:44:24 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/13 10:50:56 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Returns the player who made the most lives in the last period
**
** @param env: Context structure
** @return t_player*
*/

static t_player	*max_liveslast(t_env *env)
{
	t_player	*p;
	t_player	*winner;
	int			equals;

	equals = 0;
	p = env->player;
	winner = NULL;
	while (p)
	{
		if (!winner)
			winner = p;
		else if (p->lives_last >= winner->lives_last)
		{
			if (p->lives_last == winner->lives_last)
				equals++;
			else
			{
				equals = 0;
				winner = p;
			}
		}
		p = p->next;
	}
	return (equals ? NULL : winner);
}

/*
** @brief: Returns the number player (1-4)
**
** @param env: Context structure
** @param winner: Winner
** @return int: Player number
*/

static int		player_nb(t_env *env, t_player *winner)
{
	int			i;
	t_player	*p;

	i = 1;
	p = env->player;
	while (p)
	{
		if (p == winner)
			return (i);
		i++;
		p = p->next;
	}
	return (0);
}

/*
** @brief: Sets winner and displays it
**
** @param env: Context structure
** @param p: Winner (can be NULL)
*/

void			winner(t_env *env, t_player *p)
{
	if (env->flags & FLAG_NCURSES && !env->gph)
		visu_init(env);
	if (!p)
		p = max_liveslast(env);
	if (!p)
		p = env->plast_live;
	if (env->flags & FLAG_AFF)
		ft_printf("Aff : %s\n", env->aff->str);
	if (p)
		printer(env, 1, "Contestant %d, \"%s\", has won after %d cycles !\n",
			player_nb(env, p), p->header.prog_name, env->cycle);
	else
		printer(env, 1, "Draw match after %d cycles !\n", env->cycle);
	if (env->flags & (FLAG_DUMP | FLAG_DUMPC | FLAG_SLEEP) && env->option_nb)
		deal_options_dump(env);
	visu_winner(env, p);
}
