/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 14:38:22 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/08 17:51:34 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <stdlib.h>
# include <curses.h>
# include <locale.h>
# include <limits.h>

# define HEADER_PATH 	CUR_DIR"header"
# define AUTHORS_PATH	CUR_DIR"../auteur"

# define SPEED_DEFAULT	50

# define KEY_ESC		27

# define SCRH			84
# define TRMW			108
# define TRMW_MIN		70

# define PLAYER1_FCOLOR	F_GREEN
# define PLAYER2_FCOLOR	F_CYAN
# define PLAYER3_FCOLOR	F_PURPLE
# define PLAYER4_FCOLOR F_YELLOW
# define PLAYER1_BCOLOR "\033[0;30;42m"
# define PLAYER2_BCOLOR "\033[0;30;46m"
# define PLAYER3_BCOLOR "\033[0;30;45m"
# define PLAYER4_BCOLOR "\033[0;30;43m"

# define PLAYER1_COLOR	COLOR_GREEN
# define PLAYER2_COLOR	COLOR_CYAN
# define PLAYER3_COLOR	COLOR_MAGENTA
# define PLAYER4_COLOR	COLOR_YELLOW
# define ERR_COLOR		99
# define NORMAL_COLOR	100

# define RCOLOR			256

# define PAUSE			0
# define RUN			1
# define FW				2
# define STOP			3

struct s_env;
struct s_player;

typedef struct	s_dim
{
	int				l;
	int				c;
	int				x;
	int				y;
}				t_dim;

typedef struct	s_gph
{
	WINDOW			*warn;
	WINDOW			*winf;
	WINDOW			*wlgd;
	WINDOW			*wtrm;
	t_dim			arn;
	t_dim			inf;
	t_dim			lgd;
	t_dim			trm;
	t_dim			head;
	int				cycles_sec;
	int				running;
}				t_gph;

/*
** Init
*/
void			visu_init(struct s_env *env);
void			visu_init_colors(void);
void			visu_boxes_initial_position(t_gph *gph);
void			visu_create_windows(t_env *env, t_gph *gph);
void			visu_display_boxes(t_gph *gph);
void			visu_display_header(t_env *env, t_gph *gph);
void			visu_display_legend(t_env *env);
void			visu_display_scales(t_gph *gph);

/*
** Display Arena
*/
void			visu_colorized(t_env *env, t_proc *p, int siz, unsigned int pc);
void			visu_movepc(t_env *env, t_proc *p);
void			visu_killpc(t_env *env, t_proc *p);
void			visu_dump_arn(t_env *env);

/*
** Display info
*/
void			visu_info(t_env *env, WINDOW *winf);
void			visu_currlive_brkdown(t_env *env, int *y, int x);
void			visu_lastlive_brkdown(t_env *env, int *y, int x);

/*
** Events
*/
void			visu_manage_events(t_env *env);
void			visu_resize(t_env *env);

/*
** Quit
*/
void			visu_winner(t_env *env, struct s_player *p);
void			visu_delwin(t_env *env);
void			visu_end(struct s_env *env);

/*
** Tools
*/
int				ft_getch(void);
void			ft_wrefresh(t_env *env);

#endif
