/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 19:18:41 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/13 10:48:02 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_H
# define CW_H

# include <stdlib.h>
# include <stdio.h>
# include "ft_printf.h"
# include "op.h"
# include "visu.h"

# define INPUT_EXT		".cor"

# define FLAG_HELP		1
# define FLAG_NCURSES	2
# define FLAG_VERBOSE	4
# define FLAG_DUMP		8
# define FLAG_DUMPC		16
# define FLAG_PLAYER	32
# define FLAG_AFF		64
# define FLAG_SLEEP		128

# define LINE_SIZE		64

typedef struct	s_flag
{
	int				code;
	const char		*str;
}				t_flag;

static t_flag	g_flag_tab[] = {
	{FLAG_HELP, "Help"},
	{FLAG_NCURSES, "nCurses"},
	{FLAG_VERBOSE, "Verbose"},
	{FLAG_DUMP, "dump"},
	{FLAG_DUMPC, "Dump"},
	{FLAG_PLAYER, "Nplayer"},
	{FLAG_AFF, "Aff"},
	{FLAG_SLEEP, "Sleep"},
	{0, 0},
};

typedef struct	s_buffer
{
	char	*str;
	int		index;
	int		len;
}				t_buffer;

typedef struct	s_proc
{
	int				nbr;
	int				first_pc;
	int				pc;
	int				charge;
	int				working;
	unsigned int	reg[REG_NUMBER];
	int				carry;
	int				live;
	struct s_proc	*next;
}				t_proc;

typedef struct	s_playerid
{
	int			i;
	int			tab[MAX_PLAYERS + 1];
}				t_playerid;

typedef struct	s_player
{
	unsigned int	id;
	unsigned int	nplayer;
	t_header		header;
	int				alive;
	int				procs;
	int				last_live;
	int				lives_curr;
	int				lives_last;
	struct s_player	*next;
}				t_player;

typedef struct	s_env
{
	int				players_amount;
	int				flags;
	int				option_nb;
	char			*err;
	unsigned char	arena[MEM_SIZE];
	unsigned char	color[MEM_SIZE];
	char			buf[SCRH + 1][TRMW + 1];
	int				ibuf;
	t_proc			*proc;
	t_player		*player;
	t_player		*plast_live;
	t_playerid		pid;
	int				nbproc;
	int				cycle;
	int				goto_cycle;
	int				cycle_to_die;
	int				nbr_live;
	int				max_checks;
	int				total_lives;
	t_gph			*gph;
	t_buffer		*aff;
}				t_env;

/*
** s_env: Context structure
*/
void			s_env_init(t_env **env);
void			s_env_del(t_env *env);

/*
** s_proc: Process strucure
*/
t_player		*s_player_new(t_env *env, int flag_n);
void			s_player_del(t_env *env);

/*
** s_proc: Process strucure
*/
t_proc			*s_proc_new(t_env *env, unsigned int nplayer);
t_proc			*s_proc_fork(t_env *env, t_proc *proc);
void			s_proc_delone(t_env *env, t_proc *p);
void			s_proc_del(t_env *env);

/*
** Process
*/
void			process_init(t_env *env);
void			ft_process(t_env *env);
void			winner(t_env *env, t_player *p);

/*
** Verbose
*/
int				printer(t_env *env, int force, const char *str, ...);
void			verbose_intro(t_env *env, char *op, int proc_nbr);
void			verbose_outro(t_env *env, int pc, int length);
void			arg_verbose_outro(t_env *e, int fpc, t_arg_type *arg, int op);
void			ldi_inner_verbose(t_env *env, int ret1, int ret2, t_proc *proc);
void			sti_verbose_intro(t_env *env, t_proc *proc);
void			sti_inner_verbose(t_env *env, int ret1, int ret2);
void			zjmp_inner_verbose(t_env *env, t_proc *proc, int ind);

/*
** 		Options
*/
void			deal_options(t_env *env);
void			deal_options_dump(t_env *env);
void			options_compatibility(t_env *env);
void			ft_dump_memory(t_env *env);
void			ft_dumpc_memory(t_env *env);

/*
** Read
*/
void			check_argv(t_env *env, int ac, char **av);
void			read_argv(t_env *env, int ac, char **av);

/*
** OP Tools
*/
char			*get_op(int op_code);
int				get_dir_size(int op_code);
void			arg_parser(unsigned char to_check, t_arg_type *arg);
int				reg_checker(t_env *env, t_proc *proc, t_arg_type *arg, int op);
int				arg_checker1(t_arg_type *arg);
int				arg_checker2(t_arg_type *arg);
int				arg_checker3(t_arg_type *arg);
void			op_intro(t_proc *proc, int op, int charge);
void			move_pc(t_env *env, t_proc *proc, t_arg_type *arg, int op);

/*
** Proc Tools
*/
void			reset_livescycle(t_env *env);

/*
** Others Tools
*/
int				ft_isnumber(char *str, intmax_t *nb);

/*
**	Operations
*/
void			ft_live(t_env *env, t_proc *proc);
void			ft_ld(t_env *env, t_proc *proc);
void			ft_st(t_env *env, t_proc *proc);
void			ft_add(t_env *env, t_proc *proc);
void			ft_sub(t_env *env, t_proc *proc);
void			and_or_xor_core(t_env *env, t_proc *proc, int op);
void			ft_and(t_env *env, t_proc *proc);
void			ft_or(t_env *env, t_proc *proc);
void			ft_xor(t_env *env, t_proc *proc);
void			ft_zjmp(t_env *env, t_proc *proc);
void			ft_ldi(t_env *env, t_proc *proc);
void			ft_sti(t_env *env, t_proc *proc);
void			ft_fork(t_env *env, t_proc *proc);
void			ft_lld(t_env *env, t_proc *proc);
void			ft_lldi(t_env *env, t_proc *proc);
void			ft_lfork(t_env *env, t_proc *proc);
void			ft_aff(t_env *env, t_proc *proc);

/*
** Errors
*/
void			error(t_env *env, char *precision, int p_error);
void			add_error(t_env *env, const char *fmt, ...);
void			usage_exit(t_env *env, char *precision, int p_error);
int				none(void);
void			help(void);

# define OP_LIVE	1
# define OP_LD		2
# define OP_ST		3
# define OP_ADD		4
# define OP_SUB		5
# define OP_AND		6
# define OP_OR		7
# define OP_XOR		8
# define OP_ZJMP	9
# define OP_LDI		10
# define OP_STI		11
# define OP_FORK	12
# define OP_LLD		13
# define OP_LLDI	14
# define OP_LFORK	15
# define OP_AFF		16

# define CH_LIVE	10
# define CH_LD		5
# define CH_ST		5
# define CH_ADD		10
# define CH_SUB		10
# define CH_AND		6
# define CH_OR		6
# define CH_XOR		6
# define CH_ZJMP	20
# define CH_LDI		25
# define CH_STI		25
# define CH_FORK	800
# define CH_LLD		10
# define CH_LLDI	50
# define CH_LFORK	1000
# define CH_AFF		2

typedef struct	s_op
{
	char			*op;
	void			(*fct)(t_env *env, t_proc *proc);
	unsigned int	argc;
	t_arg_type		argv[3];
	unsigned int	op_code;
	unsigned int	cycles;
	char			*desc;
	unsigned int	coding;
	unsigned int	dir_size;
}				t_op;

/*
** @brief: The first line is here to put every operations' op_code
** 		   at the right g_op_tab index
** 		   ex : live op_code = 1, so we access it with g_op_tab[1]
*/

static t_op		g_op_tab[18] =
{
	{"right index", 0, 0, {0}, 404, 0, "right index", 0, 0},
	{"live", ft_live, 1, {T_DIR}, OP_LIVE, CH_LIVE, "alive", 0, 0},
	{"ld", ft_ld, 2, {T_DIR | T_IND, T_REG}, OP_LD, CH_LD, "load", 1, 0},
	{"st", ft_st, 2, {T_REG, T_IND | T_REG}, OP_ST, CH_ST, "store", 1, 0},
	{"add", ft_add, 3, {T_REG, T_REG, T_REG}, OP_ADD, CH_ADD, "addition", 1, 0},
	{"sub", ft_sub, 3, {T_REG, T_REG, T_REG}, OP_SUB, CH_SUB, "sub", 1, 0},
	{"and", ft_and, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		OP_AND, CH_AND, "and (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", ft_or, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		OP_OR, CH_OR, "or  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", ft_xor, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		OP_XOR, CH_XOR, "xor (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", ft_zjmp, 1, {T_DIR}, OP_ZJMP, CH_ZJMP, "jump if zero", 0, 1},
	{"ldi", ft_ldi, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, OP_LDI,
		CH_LDI, "load index", 1, 1},
	{"sti", ft_sti, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, OP_STI,
		CH_STI, "store index", 1, 1},
	{"fork", ft_fork, 1, {T_DIR}, OP_FORK, CH_FORK, "fork", 0, 1},
	{"lld", ft_lld, 2, {T_DIR | T_IND, T_REG}, OP_LLD, CH_LLD, "long ld", 1, 0},
	{"lldi", ft_lldi, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, OP_LLDI,
		CH_LLDI, "long load index", 1, 1},
	{"lfork", ft_lfork, 1, {T_DIR}, OP_LFORK, CH_LFORK, "long fork", 0, 1},
	{"aff", ft_aff, 1, {T_REG}, OP_AFF, CH_ADD, "aff", 1, 0},
	{0, 0, 0, {0}, 0, 0, 0, 0, 0}
};

#endif
