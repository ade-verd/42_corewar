/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 11:45:50 by oozkaya           #+#    #+#             */
/*   Updated: 2019/03/13 10:50:13 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Swipes the bytes to convert from Big endian to Little endian
**
** @param nb: Bytes to convert
** @return int : Converted bytes
*/

static int		big_to_little_endian(int nb)
{
	nb = (((nb >> 24) & 0xff)
			| ((nb << 8) & 0xff0000)
			| ((nb >> 8) & 0xff00)
			| ((nb << 24) & 0xff000000));
	return (nb);
}

/*
** @brief: Parses the header of each champion
**
** @param env: Context structure
** @param fd: File descriptor of the champion
*/

static void		read_header(t_env *env, t_player *p, int fd)
{
	int	trash;

	read(fd, &p->header.magic, sizeof(COREWAR_EXEC_MAGIC));
	p->header.magic = big_to_little_endian(p->header.magic);
	if (p->header.magic != COREWAR_EXEC_MAGIC)
		error(env, "Incorrect magic number", 0);
	if (read(fd, p->header.prog_name, PROG_NAME_LENGTH) < PROG_NAME_LENGTH)
		error(env, "Incorrect program name length", 0);
	read(fd, &trash, 4);
	read(fd, &p->header.prog_size, 4);
	p->header.prog_size = big_to_little_endian(p->header.prog_size);
	if (read(fd, p->header.comment, COMMENT_LENGTH) < COMMENT_LENGTH)
		error(env, "Incorrect comment length", 0);
}

/*
** @brief: Reads the instructions into the arena
**
** @param env: Context structure
** @param fd: File descriptor of the champion
** @param arena: Pointer in arena to place each champion
*/

static void		read_instructions(t_env *env, t_player *p, int fd,
									unsigned char *arena)
{
	int				trash;
	unsigned int	curr;
	unsigned int	size;

	read(fd, &trash, 4);
	curr = lseek(fd, 0, SEEK_CUR);
	size = lseek(fd, 0, SEEK_END) - curr;
	if (size != p->header.prog_size)
	{
		add_error(env, " - Program size:     %d", size);
		add_error(env, " - Header prog_size: %d", p->header.prog_size);
		error(env, "Incorrect program size", 0);
	}
	if (size > CHAMP_MAX_SIZE)
		error(env, "Program size too large", 0);
	lseek(fd, curr, SEEK_SET);
	read(fd, arena, p->header.prog_size);
}

/*
** @brief: Handles champions introducing part
**
** @param env: Context structure
*/

static void		introduce_players(t_env *env)
{
	t_player	*p;
	int			i;
	const char	*colors[] = { PLAYER1_BCOLOR, PLAYER2_BCOLOR, PLAYER3_BCOLOR,
		PLAYER4_BCOLOR, 0 };

	i = 1;
	if ((p = env->player))
		printer(env, 1, "Introducing contestants...\n");
	while (p)
	{
		if ((env->flags & FLAG_DUMPC || env->flags & FLAG_SLEEP)
			&& !(env->flags & FLAG_NCURSES))
			printer(env, 1, "%s %s ", colors[i - 1], F_NO);
		else
			printer(env, 1, "* ");
		printer(env, 1, "Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			i, p->header.prog_size, p->header.prog_name, p->header.comment);
		i++;
		p = p->next;
	}
}

/*
** @brief: Reads arguments
**
** @param env: Context structure
** @param ac: Args number
** @param av: Args array
*/

void			read_argv(t_env *env, int ac, char **av)
{
	int				i;
	int				fd;
	t_player		*p;
	int				flag_n;
	unsigned char	*arena;

	i = -1;
	fd = -1;
	flag_n = 0;
	arena = env->arena;
	while (++i < ac)
	{
		flag_n = ft_strequ(av[i], "-n") || ft_strequ(av[i], "-N") ? 1 : flag_n;
		if (ft_strright(av[i], INPUT_EXT))
		{
			if ((fd = ft_open_fd(av[i], O_RDONLY, S_IRUSR)) == -1)
				error(env, (char *)__FUNCTION__, 1);
			p = s_player_new(env, flag_n);
			read_header(env, p, fd);
			read_instructions(env, p, fd, arena);
			arena += MEM_SIZE / env->players_amount;
			flag_n = 0;
		}
	}
	introduce_players(env);
}
