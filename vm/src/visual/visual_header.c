/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:47:09 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/08 17:52:11 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Displays authors from author file
**
** @param env: Context structure
** @param gph: Graph structure
** @param x: Absciss
*/

void	visu_display_authors(t_env *env, t_gph *gph, int x)
{
	int		fd;
	int		ret;
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	if ((fd = ft_open_fd(AUTHORS_PATH, O_RDONLY, S_IRUSR)) == -1)
		error(env, (char*)__FUNCTION__, 1);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (i++ > 0)
			mvprintw(gph->head.l - 1, x++, ", ");
		mvprintw(gph->head.l - 1, ++x, "%s", line);
		x += ft_strlen(line);
		ft_strdel(&line);
	}
	refresh();
	if (line)
		ft_strdel(&line);
	if (ret < 0 || (ft_close_fd(fd) == -1))
		error(env, (char*)__FUNCTION__, 1);
}

/*
** @brief: Displays header
**
** @param env: Context structure
** @param gph: Graph structure
*/

void	visu_display_header(t_env *env, t_gph *gph)
{
	int		fd;
	int		ret;
	char	*line;
	int		len;

	line = NULL;
	gph->head.l = 0;
	gph->head.c = 0;
	gph->head.x = 0;
	gph->head.y = 0;
	if ((fd = ft_open_fd(HEADER_PATH, O_RDONLY, S_IRUSR)) == -1)
		error(env, (char*)__FUNCTION__, 1);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		len = ft_strlen(line);
		gph->head.c = gph->head.c == 0 ? len : gph->head.c;
		gph->head.x = gph->head.x == 0 ? ft_sqrt(MEM_SIZE) : gph->head.x;
		mvprintw(gph->head.l++, gph->head.x, "%s\n", line);
		ft_strdel(&line);
	}
	if (line)
		ft_strdel(&line);
	if (ret < 0 || (ft_close_fd(fd) == -1))
		error(env, (char*)__FUNCTION__, 1);
	visu_display_authors(env, env->gph, gph->head.x + len);
}
