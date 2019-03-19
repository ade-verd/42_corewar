/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_player.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:14:27 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/05 19:35:31 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Checks doubles nplayer numbers and adjust them (if not fixed by user)
**
** @param env: Context structure
** @param nplayr: Nplayer identification (int pointuer)
** @param flag_n: Flag n enable ?
*/

void			check_nplyr_double(t_env *env, unsigned int *nplayr, int flag_n)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (env->pid.tab[i])
	{
		if (*nplayr == (unsigned int)env->pid.tab[i])
		{
			if (flag_n)
				count++;
			else
			{
				(*nplayr)--;
				i = -1;
			}
		}
		i++;
	}
	if (count > 1)
	{
		add_error(env, "Multiple assignment of the value %d", *nplayr);
		usage_exit(env, "Bad Nplayer argument", 0);
	}
}

/*
** @brief: Adjusts nplayer number for champions which haven't enable flag n
**
** @param env: Context structure
** @return unsigned int: Nplayer number adjusted
*/

unsigned int	get_nplayer(t_env *env)
{
	t_player		*p;
	unsigned int	nplayer;

	p = env->player;
	nplayer = UINT_MAX;
	while (p)
	{
		if (p->nplayer == nplayer)
		{
			nplayer--;
			p = env->player;
		}
		else
			p = p->next;
	}
	return (nplayer);
}

/*
** @brief: Checks the number of players
**
** @param env: Context structure
*/

static void		check_player_nbr(t_env *env)
{
	t_player	*player;
	int			count;

	count = 1;
	player = env->player;
	while (player)
	{
		count++;
		player = player->next;
	}
	if (count > MAX_PLAYERS)
		error(env, "Maximum 4 champions authorized", 0);
}

/*
** @brief: Creates new player
**
** @param *env: Context structure
** @param flag_n: Flag_n enabled for this player ?
** @return t_player*
*/

t_player		*s_player_new(t_env *env, int flag_n)
{
	t_player	*new;
	t_player	*curr;

	check_player_nbr(env);
	curr = env->player;
	while (curr && curr->next)
		curr = curr->next;
	if (!(new = (t_player*)malloc(sizeof(t_player))))
		error(env, (char*)__FUNCTION__, 1);
	new->id = curr ? curr->id - 1 : UINT_MAX;
	new->nplayer = flag_n ? env->pid.tab[env->pid.i++] : get_nplayer(env);
	check_nplyr_double(env, &new->nplayer, flag_n);
	new->alive = 0;
	new->procs = 0;
	new->last_live = 0;
	new->lives_curr = 0;
	new->lives_last = 0;
	ft_memset(&new->header, 0, sizeof(t_header));
	new->next = NULL;
	if (curr)
		curr->next = new;
	else
		env->player = new;
	return (new);
}

/*
** @brief: Deletes all the players
**
** @param env: Context structure
*/

void			s_player_del(t_env *env)
{
	t_player	*curr;
	t_player	*next;

	curr = env->player;
	while (curr)
	{
		next = curr->next;
		ft_memdel((void**)&curr);
		curr = next;
	}
}
