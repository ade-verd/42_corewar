/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:32:11 by ade-verd          #+#    #+#             */
/*   Updated: 2018/12/13 14:57:38 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief: Opens env->input file. Stores fd env->fd_in
**
** @param env: Context structure
*/

void		open_input(t_env *env)
{
	if (env && env->input)
	{
		if ((env->fd_in = ft_open_fd(env->input, O_RDONLY, S_IRUSR)) == -1)
			error(env, (char*)__FUNCTION__, 1);
	}
	else
		error(env, "No input *.cor file", 0);
}

/*
** @brief: Convert a path.ext_in to path.ext_out
**
** @param input: Input
** @param ext_in: Extension to search
** @param ext_out: Extension to replace with
** @return char*
*/

static char	*convert_path(char *input, char *ext_in, char *ext_out)
{
	int		len_noext;
	int		n;
	char	*out;

	len_noext = ft_strlen(input) - ft_strlen(ext_in);
	n = len_noext + ft_strlen(ext_out);
	if (!(out = ft_strnjoinfree(ft_strndup(input, len_noext), ext_out, n, 0)))
		return (NULL);
	return (out);
}

/*
** @brief: Creates output file to write in. Stores fd in env->fd_out
**
** @param env: Context structure
*/

void		create_output(t_env *env)
{
	if (env && env->input)
	{
		if ((env->output = convert_path(env->input, INPUT_EXT, OUTPUT_EXT)))
		{
			if ((env->fd_out = ft_open_fd(env->output,
				O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1)
				error(env, (char*)__FUNCTION__, 1);
		}
	}
	else
		error(env, "No input *.cor file", 0);
}

/*
** @brief: Closes fd relatives to input and output
**
** @param env: Context structure
*/

void		close_in_output(t_env *env)
{
	if (env->fd_in > 2 && (ft_close_fd(env->fd_in) == -1))
		error(env, (char*)__FUNCTION__, 1);
	if (env->fd_out > 2 && (ft_close_fd(env->fd_out) == -1))
		error(env, (char*)__FUNCTION__, 1);
}
