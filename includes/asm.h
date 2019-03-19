/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 11:37:19 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/14 11:26:40 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include "ft_printf.h"
# include "op.h"

# define INPUT_EXT			".s"
# define OUTPUT_EXT			".cor"

# define FLAG_HELP			1
# define FLAG_DEBUG			2
# define FLAG_DEBUG_FLAGS	4
# define FLAG_ANNOTED		8

# define ERR_LEX			1001
# define ERR_REG			1002

typedef struct		s_arg
{
	int				id;
	char			*rcode;
	unsigned int	type;
	intmax_t		val;
	intmax_t		realval;
	char			dirsize;
	unsigned int	bytes;
	struct s_arg	*next;
}					t_arg;

typedef struct		s_asm
{
	char			*line;
	char			*label;
	int				op_code;
	unsigned int	coding;
	unsigned int	argc;
	struct s_arg	*arg;
	unsigned int	pc;
	unsigned int	bytes;
	struct s_asm	*next;
}					t_asm;

typedef struct		s_env
{
	char			*input;
	char			*output;
	int				fd_in;
	int				fd_out;
	int				flags;
	char			*sstr;
	char			*inst;
	t_header		header;
	t_asm			*asmb;
	char			*err;
}					t_env;

/*
** s_env: Context structure
*/
void				s_env_init(t_env **env);
void				s_env_del(t_env *env);

/*
** s_buf: Buffer structure
*/
void				s_buf_init(t_env *env);
void				s_buf_write(t_env *env, void *mem, int size);
void				s_buf_del(t_env *env);

/*
** s_asm: RedCode structure
*/
void				s_asm_append(t_env *env, t_asm *cur, char *str, char **exp);
int					countbytes(t_asm *asmb, t_arg *arg);
void				s_asm_complete_missing_values(t_env *env, t_asm *head);
void				s_asm_debug(t_env *env, t_asm *asmb);
void				s_asm_del(t_asm *asmb);

/*
** s_arg: argument structure
*/
void				s_arg_append(t_env *env, t_asm *asmb, t_arg *cur, char *s);
void				s_arg_value_eval(t_env *env, t_asm *asmb, t_arg *arg);
void				s_arg_debug(t_env *env, t_arg *arg);
void				s_arg_del(t_arg *arg);

/*
** File descriptor
*/
void				open_input(t_env *env);
void				create_output(t_env *env);
void				close_in_output(t_env *env);

/*
** Read
*/
void				read_args(t_env *env, int ac, char **av);
void				read_fd(t_env *env);

/*
** Parsing
*/
void				parse_sstr(t_env *env);
int					is_name(char *line);
void				get_name(t_env *env, char *sstr);
int					is_comment(char *line);
void				get_comment(t_env *env, char *sstr);
void				get_separators(char *separators);
char				*ft_del_comments(char *str, char seperator);

/*
** Checker
*/
void				checker(t_env *env, t_asm *head);

/*
** Types
*/
int					wh_type(char *str);
int					is_llabel(char *str);
int					is_op(char *str);
int					analyze_nb_bytes(t_arg *arg, unsigned int op_code);
int					get_val(t_env *env, t_asm *asmb, t_arg *arg);
int					get_labelpc(t_asm *head, char *label);
unsigned char		coding_val(t_asm *asmb);
unsigned int		code2type(unsigned int code);

/*
** Read g_op_tab
*/
int					optocode(char *op);
char				*codetoop(unsigned int op_code);
int					got_octalcoding(unsigned int op_code);
int					dir_size(unsigned int op_code);
t_arg_type			get_argtype(int op_code, unsigned int index);

/*
** Interpret
*/
void				interpret_bin(t_env *env);
void				interpret_annoted(t_env *env);

/*
** Print annoted
*/
void				print_label(t_asm *asmb, char **lab);
void				print_rcode(t_asm *asmb);
void				print_arg(t_arg *arg, char base);
void				print_dec(t_asm *asmb);
void				print_hex(t_asm *asmb);

/*
** Help
*/
void				deal_help_debug(t_env *env);
void				help(void);

/*
** Errors
*/
void				error(t_env *env, char *precision, int p_error);
void				add_error(t_env *env, const char *fmt, ...);
void				usage_exit(t_env *env, char *precision, int p_error);
int					none(void);

/*
** Annex Functions
*/
int					ft_arrstrlen(char **tab);
char				*ft_strtrimc(char *s, char c);
int					ft_isnumber(char *str, intmax_t *nb);
unsigned int		ft_endian(unsigned int nb, char bytes);
int					ft_isstralpha(char *str);

#endif
