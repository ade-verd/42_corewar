/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 11:46:17 by oozkaya           #+#    #+#             */
/*   Updated: 2019/03/14 13:01:42 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief Takes a flag(s) code as int and returns a flag(s) name as string
**
** @param lastflag: Last flag(s) as int
** @return char*: Last flag(s) as char*
*/

static char		*get_flagname(int lastflag)
{
	int			f;
	int			i;
	int			j;
	int			count_flags;
	static char	flags[128];

	ft_bzero(flags, 128);
	f = 0;
	i = 0;
	count_flags = 0;
	while (g_flag_tab[f].code)
	{
		if (lastflag & g_flag_tab[f].code)
		{
			count_flags++;
			if (i > 0)
				flags[i++] = '-';
			j = 0;
			while (g_flag_tab[f].str[j])
				flags[i++] = g_flag_tab[f].str[j++];
		}
		f++;
	}
	return (flags);
}

/*
** @brief: Checks flags and eventual number.
**		   Then stores it, ignores it, or adds an error
**
** @param env: Context structure
** @param str: argv[n]
** @param lastflag: last flag
*/

static void		parse_nb(t_env *env, char *str, int lastflag, int *nextisnb)
{
	intmax_t	n;

	*nextisnb = 0;
	if (!ft_isnumber(str, &n))
	{
		if (!(lastflag & (FLAG_DUMP | FLAG_DUMPC | FLAG_PLAYER | FLAG_SLEEP)))
			return ;
		else
			return (add_error(env, "A number is expected after %s flag(s)",
				get_flagname(lastflag)));
	}
	if (n > INT_MAX)
		add_error(env, "Given number has to be an integer");
	if (lastflag & FLAG_PLAYER)
		env->pid.tab[env->pid.i++] = n;
	else
	{
		env->option_nb = n;
		env->goto_cycle = n;
		if (!env->err && n <= 0)
			add_error(env, "Cycle number has to be bigger than 0");
	}
}

/*
** @brief: Checks arguments and stores flags
**
** @param env: Context structure
** @param str: argv[n]
** @param nextarg_isnb: Indicates that nextarg can expect a number
** @return int
*/

static int		parse_flags(t_env *env, char *str, int *nextarg_isnb)
{
	int	flags;

	flags = 0;
	if (ft_strchr(str, 'h') || ft_strchr(str, 'H'))
		flags |= FLAG_HELP;
	if (ft_strchr(str, 'c') || ft_strchr(str, 'C'))
		flags |= FLAG_NCURSES;
	if (ft_strchr(str, 'v') || ft_strchr(str, 'V'))
		flags |= FLAG_VERBOSE;
	if (ft_strchr(str, 'd') || ft_strcmp("-dump", str) == 0)
		flags |= FLAG_DUMP;
	if (ft_strchr(str, 'D') || ft_strcmp("-Dump", str) == 0)
		flags |= FLAG_DUMPC;
	if (ft_strchr(str, 'n') || ft_strchr(str, 'N'))
		flags |= FLAG_PLAYER;
	if (ft_strchr(str, 'a') || ft_strchr(str, 'A'))
		flags |= FLAG_AFF;
	if (ft_strchr(str, 's') || ft_strchr(str, 'S'))
		flags |= FLAG_SLEEP;
	env->flags |= flags;
	!flags ? add_error(env, "A flag error occured") : none();
	if (flags
		& (FLAG_NCURSES | FLAG_DUMP | FLAG_DUMPC | FLAG_PLAYER | FLAG_SLEEP))
		*nextarg_isnb = 1;
	return (flags);
}

/*
** @brief: Returns the amount of players
**
** @param ac: Args number
** @param av: Args array
** @return char
*/

static char		count_players(int ac, char **av)
{
	int	count;

	count = 0;
	while (ac-- > 1)
	{
		if (ft_strright(av[ac], INPUT_EXT))
			count++;
	}
	return (count);
}

/*
** @brief: Checks arguments
**
** @param env: Context structure
** @param ac: Args number
** @param av: Args array
*/

void			check_argv(t_env *env, int ac, char **av)
{
	int		i;
	int		nextisnb;
	int		lastflag;

	env->players_amount = count_players(ac, av);
	nextisnb = 0;
	lastflag = 0;
	i = 0;
	while (++i < ac)
	{
		if (nextisnb)
			parse_nb(env, av[i], lastflag, &nextisnb);
		if (!ft_isnumber(av[i], 0))
		{
			if (av[i][0] == '-')
				lastflag = parse_flags(env, av[i], &nextisnb);
			else if (!env->err && !ft_strright(av[i], INPUT_EXT))
				add_error(env, "Bad champion's format: '%s'", av[i]);
		}
	}
	nextisnb ? parse_nb(env, av[i - 1], lastflag, &nextisnb) : none();
	env->pid.i = 0;
	env->err ? usage_exit(env, "Bad argument", 0) : none();
}
