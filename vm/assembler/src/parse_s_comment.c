/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s_comment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:20:47 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/14 15:47:08 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief: Checks if line is a comment
**
** @param line: String
** @return int: Returns 1 if line is a comment. Otherwise returns 0
*/

int		is_comment(char *line)
{
	return (ft_strstr(line, COMMENT_CMD_STRING) ? 1 : 0);
}

/*
** @brief Gets the program's description
**
** @param env: Context structure
** @param sstr: File.s as char*
*/

void	get_comment(t_env *env, char *orig)
{
	int		i;
	char	*str;

	i = 0;
	str = orig ? orig + ft_strlen(COMMENT_CMD_STRING) : NULL;
	while (str && *str && ft_strchr(SPACES, *str))
		str++;
	if (!str || !*str || *str != '"')
		add_error(env, "The program description [.comment] is not set");
	while (!env->err && ++str && *str && *str != '"')
	{
		if (i >= COMMENT_LENGTH)
			add_error(env, "The program description [.comment] is too long");
		else
			env->header.comment[i++] = *str;
		*str = ' ';
	}
	if (i && str && *str != '"')
		add_error(env, "The program description [.comment] is not terminated");
	if (!i && !env->err)
		add_error(env, "The program description [.comment] is empty");
	env->header.comment[i] = '\0';
	if (env->flags & FLAG_DEBUG)
		ft_printf("header.comment: |%s|\n", env->header.comment);
}
