/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:08:31 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/05 17:46:00 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Returns the number of lines in a string
**
** @param str: String
** @return int
*/

int		str_lines(char *str)
{
	char	*tmp;
	int		lines;
	int		i;

	if (!str)
		return (0);
	tmp = str;
	lines = 1;
	while ((tmp = ft_strchr(tmp, '\n')))
	{
		lines++;
		tmp++;
	}
	i = 0;
	while (str[i] && str[i + 1])
		i++;
	if (str[i] == '\n')
		lines--;
	return (lines);
}

/*
** @brief: Scrolls buffer. Old strings are deleted. News are added.
**
** @param env: Context structure
** @param lines: Number of lines which has to be deleted and added
*/

void	scroll_buffer(t_env *env, int lines)
{
	int	i;
	int	c;

	i = 0;
	lines = env->buf[env->ibuf][0] ? lines - 1 : lines;
	if ((env->ibuf + lines) > SCRH)
	{
		while (i < (SCRH - lines))
		{
			c = 0;
			while (env->buf[i + lines][c])
			{
				env->buf[i][c] = env->buf[i + lines][c];
				c++;
			}
			env->buf[i][c] = '\0';
			i++;
		}
		while (i < SCRH)
			env->buf[i++][0] = '\0';
		env->ibuf -= lines;
	}
}

/*
** @brief: Puts string into buffer
**
** @param env: Context structure
** @param str: String which has to be put into buffer
** @param c: Little hack to respect the norm
** @param i: Little hack to respect the norm
*/

void	putinbuffer(t_env *env, char *str, int c, int i)
{
	char	*line;
	char	*next;

	line = str;
	scroll_buffer(env, str_lines(str));
	while (line)
	{
		if ((next = ft_strchr(line, '\n')))
			*next = '\0';
		c = 0;
		while (env->buf[env->ibuf][c])
			c++;
		i = 0;
		while (line && line[i] && (c + i) < (TRMW - 1))
		{
			env->buf[env->ibuf][c + i] = line[i];
			i++;
		}
		env->buf[env->ibuf][c + i] = '\0';
		env->buf[env->ibuf + 1][0] = '\0';
		if ((c + i) >= (TRMW - 1) || next)
			env->ibuf++;
		next ? *next = '\n' : '\0';
		line = next ? (next + 1) : NULL;
	}
}

/*
** @brief: Prints on nCurses terminal
**
** @param env: Context structure
** @param fmt: ft_printf format
** @param ap: ft_printf variadic param
** @return int: Value returned by ft_printf family
*/

int		term_display(t_env *env, const char *fmt, va_list ap)
{
	char	*str;
	int		ret;
	int		i;
	int		j;

	ret = 0;
	str = NULL;
	ret = ft_vasprintf(&str, fmt, ap);
	putinbuffer(env, str, 0, 0);
	if (!env->gph || (env->cycle + SCRH < env->goto_cycle
		&& env->cycle_to_die > 0))
	{
		ft_strdel(&str);
		return (ret);
	}
	i = 0;
	werase(env->gph->wtrm);
	while (i < env->gph->trm.l)
	{
		j = env->cycle < env->gph->trm.l ? i : i + (SCRH - env->gph->trm.l);
		mvwprintw(env->gph->wtrm, i, 1, "%.*s\n", env->gph->trm.c, env->buf[j]);
		i++;
	}
	ft_strdel(&str);
	return (ret);
}

/*
** @brief: Main print function of the virtual machine. Handles 3 printing ways:
** 			 1- Verbose flag enabled: Print on stdout
** 			 2- Verbose & nCurses flags enabled: Print on nCurses terminal
** 			 3- Param. 'force': force printing, even whitout verbose mode
**				Force does not work with nCurses flag
**
** @param env: Context structure
** @param force: Force printing if force != 0
** @param str: Format to pass to ft_printf
** @param ...: Variadics params to pass to ft_printf
** @return int: Value returned by ft_printf family
*/

int		printer(t_env *env, int force, const char *str, ...)
{
	va_list		ap;
	int			ret;

	ret = 0;
	if (!(env->flags & (FLAG_VERBOSE | FLAG_NCURSES)) && !force)
		return (ret);
	va_start(ap, str);
	if (env->flags & FLAG_NCURSES && env->flags & FLAG_VERBOSE)
		ret = term_display(env, str, ap);
	else if (env->flags & FLAG_VERBOSE && !(env->flags & FLAG_NCURSES))
		ret = ft_vprintf(str, ap);
	else if (force && !(env->flags & FLAG_NCURSES))
		ret = ft_vprintf(str, ap);
	va_end(ap);
	return (ret);
}
