/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:38:30 by oozkaya           #+#    #+#             */
/*   Updated: 2019/03/08 17:56:51 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Displays "Error" (and eventually precision) and exit
**
** @param precision: Explains error in a string
** @param p_error: Error number
*/

void	error(t_env *env, char *precision, int p_error)
{
	int	nothing;

	nothing = ft_strcmp(precision, "NO");
	if (env && env->gph)
		visu_end(env);
	if (nothing != 0)
		ft_dprintf(2, "Error\n");
	if (precision && nothing != 0)
		ft_dprintf(2, "%s\n", precision);
	if (env && env->err)
		ft_dprintf(2, "%s\n", env->err);
	if (p_error > 0)
		perror(NULL);
	s_env_del(env);
	exit(EXIT_FAILURE);
}

/*
** @brief: Displays Usage (help()) and exits correctly
**
** @param env: Context structure
** @param precision: char *precision used in error(). Explains error in a string
** @param p_error: Error number
*/

void	usage_exit(t_env *env, char *precision, int p_error)
{
	int	nothing;

	nothing = ft_strcmp(precision, "NO");
	if (env->gph)
		visu_end(env);
	if (nothing != 0)
		ft_dprintf(2, "Error\n");
	if (precision && nothing != 0)
		ft_dprintf(2, "%s\n", precision);
	if (env->err)
		ft_dprintf(2, "%s\n", env->err);
	if (p_error > 0)
		perror(NULL);
	s_env_del(env);
	if (nothing != 0)
		ft_putstr("——————\n");
	help();
	exit(EXIT_FAILURE);
}

/*
** @brief: Store a message error in the main context structure.
**
** @param env: Context structure
** @param msg: Message error which has to be added.
*/

void	add_error(t_env *env, const char *fmt, ...)
{
	va_list	ap;
	char	*str;
	char	*tmp;
	int		len;

	str = NULL;
	tmp = NULL;
	len = 0;
	va_start(ap, fmt);
	ft_vasprintf(&str, fmt, ap);
	va_end(ap);
	if (!env->err)
		env->err = ft_strdup(str);
	else if (!(ft_strstr(env->err, str)))
	{
		tmp = ft_strnjoinfree(env->err, "\n", ft_strlen(env->err), 0);
		len = ft_strlen(tmp) + ft_strlen(str);
		env->err = ft_strnjoinfree(tmp, str, len, 0);
	}
	if (!env->err)
		error(env, (char*)__FUNCTION__, 1);
	if (str)
		ft_memdel((void**)&str);
}

/*
** @brief: Does nothing. Useful for some ternaries
*/

int		none(void)
{
	return (0);
}
