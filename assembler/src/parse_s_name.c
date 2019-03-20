/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:20:47 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/20 19:43:24 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief: Checks if line is the program's name
**
** @param line: String
** @return int: Returns 1 if line is the program's name. Otherwise returns 0
*/

int		is_name(char *line)
{
	return (ft_strstr(line, NAME_CMD_STRING) ? 1 : 0);
}

/*
** @brief Get the program's name
**
** @param env: Context structure
** @param sstr: File.s as char*
*/

void	get_name(t_env *env, char *orig)
{
	int		i;
	char	*str;

	i = 0;
	str = orig ? orig + ft_strlen(NAME_CMD_STRING) : NULL;
	while (str && *str && ft_strchr(SPACES, *str))
		str++;
	if (!str || !*str || *str != '"')
		add_error(env, "The program name [.name] is not set");
	while (!env->err && ++str && *str && *str != '"')
	{
		if (i >= PROG_NAME_LENGTH)
			add_error(env, "The program name [.name] is too long");
		else
			env->header.prog_name[i++] = *str;
		*str = ' ';
	}
	if (i && str && *str != '"' && !env->err)
		add_error(env, "The program name [.name] is not terminated");
	if (!i && !env->err)
		add_error(env, "The program name [.name] is empty");
	env->header.prog_name[i] = '\0';
	if (env->flags & FLAG_DEBUG)
		ft_printf("header.prog_name: |%s|\n", env->header.prog_name);
}
