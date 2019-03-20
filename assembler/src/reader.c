/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 18:50:18 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/14 17:09:44 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief: Checks path and stores it
**
** @param env: Context structure
** @param ext: Extension expected
** @param err: Integer pointer on error flag.
*/

static void	check_path(t_env *env, char *ext, int *err)
{
	if (!env->input)
		env->input = ft_strdup(ext);
	else
	{
		*err += 1;
		add_error(env, "Arguments contain multiple input path");
	}
}

/*
** @brief: Checks flags stores them
**
** @param env: Context structure
** @param err: argv[#]
*/

static void	parse_flags(t_env *env, char *str, int *err)
{
	if (str[0] == '-' && (ft_strchr(str, 'h') || ft_strchr(str, 'H')))
		env->flags = env->flags | FLAG_HELP;
	if (str[0] == '-' && (ft_strchr(str, 'd') || ft_strchr(str, 'D')))
		env->flags = env->flags | FLAG_DEBUG;
	if (str[0] == '-' && (ft_strchr(str, 'f') || ft_strchr(str, 'F')))
		env->flags = env->flags | FLAG_DEBUG_FLAGS;
	if (str[0] == '-' && (ft_strchr(str, 'a') || ft_strchr(str, 'A')))
		env->flags = env->flags | FLAG_ANNOTED;
	if (str[0] == '-' && !env->flags)
	{
		*err += 1;
		add_error(env, "A flag error occured");
	}
}

/*
** @brief: Reads arguments
**
** @param env: Context structure
** @param ac: Args number
** @param av: Args array
*/

void		read_args(t_env *env, int ac, char **av)
{
	char	**tab;
	int		i;
	int		err;

	err = 0;
	while (ac > 1)
	{
		ac--;
		i = ft_countwords(av[ac], ' ');
		tab = ft_strsplit(av[ac], ' ');
		while (--i >= 0)
		{
			if (tab[i][0] == '-')
				parse_flags(env, tab[i], &err);
			else if (ft_strright(tab[i], INPUT_EXT))
				check_path(env, tab[i], &err);
			else
				err++;
		}
		ft_freetab_strsplit(tab);
		if (err)
			break ;
	}
	if (err)
		usage_exit(env, "Bad argument", 0);
}

/*
** @brief: Allocates the good size to stringify input. Resets lseek to 0.
**
** @param env: Context structure
*/

static void	allocate_sstr(t_env *env)
{
	int		size;

	size = 0;
	if (env && env->fd_in >= 0 && (size = lseek(env->fd_in, 0, SEEK_END)) == -1)
		error(env, (char*)__FUNCTION__, 1);
	if (!(env->sstr = ft_strnew(size)))
		error(env, (char*)__FUNCTION__, 1);
	ft_bzero(env->sstr, size);
	if (env && env->fd_in >= 0 && (size = lseek(env->fd_in, 0, SEEK_SET)) == -1)
		error(env, (char*)__FUNCTION__, 1);
}

/*
** @brief: Reads file descriptor stored in env structure
**
** @param env: Context structure
*/

void		read_fd(t_env *env)
{
	int		ret;
	char	*line;
	char	*trim;

	line = NULL;
	trim = NULL;
	allocate_sstr(env);
	while (env->fd_in >= 0 && (ret = get_next_line(env->fd_in, &line)) > 0)
	{
		trim = ft_strtrim(line);
		if (env->sstr[0])
			ft_strcat(env->sstr, "\n");
		if (env->sstr && trim)
			ft_strcat(env->sstr, trim);
		if (trim)
			ft_strdel(&trim);
		ft_strdel(&line);
	}
	if (line)
		ft_strdel(&line);
	ret < 0 ? error(env, (char*)__FUNCTION__, 1) : none();
}
