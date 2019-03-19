/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:29:21 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/14 16:19:12 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief: Takes an empty char array and fill it with SPACES and SEPARATOR_CHAR
**
** @param separators: Empty char array
*/

void		get_separators(char *separators)
{
	int		i;
	char	*blank;

	i = 0;
	blank = SPACES;
	ft_bzero(separators, 10);
	while (blank[i])
	{
		separators[i] = blank[i];
		i++;
	}
	separators[i] = SEPARATOR_CHAR;
}

/*
** @brief: Parses commands '.name' and '.comment'
**
** @param env: Context structure
*/

void		parse_commands(t_env *env)
{
	int		i;
	char	**lines;
	char	*name;
	char	*comment;

	i = 0;
	lines = ft_strsplit(env->sstr, '\n');
	name = env->header.prog_name;
	comment = env->header.comment;
	while (lines[i] && !env->err)
	{
		if (!name[0] && ft_strleft(lines[i], NAME_CMD_STRING))
			get_name(env, ft_strstr(env->sstr, lines[i]));
		else if (!comment[0] && ft_strleft(lines[i], COMMENT_CMD_STRING))
			get_comment(env, ft_strstr(env->sstr, lines[i]));
		i++;
	}
	ft_freetab_strsplit(lines);
	if (!env->err && !env->header.prog_name[0])
		add_error(env, "The program name [.name] is not set");
	if (!env->err && !env->header.comment[0])
		add_error(env, "The program comment [.comment] is not set");
	env->err ? error(env, "Program header", 0) : none();
}

/*
** @brief: Completes parse_sstr. Parses a line s and appends it into s_asm
**
** @param env: Context structure
** @param s: Line as 's'tring
** @param separators: cf. get_separators() above
*/

void		loop_lines(t_env *env, char *s, char *separators)
{
	char	**explode;
	char	*trim;

	explode = NULL;
	trim = NULL;
	if (!ft_strleft(s, NAME_CMD_STRING) && !ft_strleft(s, COMMENT_CMD_STRING))
	{
		trim = ft_strtrim(ft_del_comments(s, COMMENT_CHAR));
		explode = ft_strmsplit(trim, separators);
		s_asm_append(env, env->asmb, trim, explode);
		ft_strdel(&trim);
		ft_freetab_strsplit(explode);
	}
}

/*
** @brief: Parses env->sstr which contains all of the file.s
**
** @param env: Context structure
*/

void		parse_sstr(t_env *env)
{
	int		i;
	char	separators[10];
	char	**lines;

	parse_commands(env);
	get_separators(separators);
	lines = ft_strsplit(env->sstr, '\n');
	i = 0;
	while (lines[i])
		loop_lines(env, lines[i++], separators);
	ft_freetab_strsplit(lines);
	s_asm_complete_missing_values(env, env->asmb);
	checker(env, env->asmb);
}
