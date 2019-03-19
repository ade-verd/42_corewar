/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:18:15 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/14 12:25:15 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief Takes an op code in parameter, reads g_op_tab and returns the number
** of arguments (argc) associated
**
** @param op_code: OP code
** @return unsigned int: Number of argument (argc) associated
*/

static unsigned int	op_argc(unsigned int op_code)
{
	int	i;

	i = 0;
	while (g_op_tab[i].op_code)
	{
		if (g_op_tab[i].op_code == op_code)
			return (g_op_tab[i].argc);
		i++;
	}
	return (0);
}

/*
** @brief: Checks arg validity
**
** @param env: Context structure
** @param cur: Current argument
** @param op_code: Current op_code
*/

void				check_arg(t_env *env, t_asm *as, t_arg *cur, int op_code)
{
	char		*str;
	t_arg_type	argtype;

	str = NULL;
	argtype = get_argtype(op_code, cur->id);
	if (cur->type == (unsigned int)-1)
	{
		add_error(env, "[%s] Unk. argument type: '%s' ", as->line, cur->rcode);
		return ;
	}
	else if (cur->type == ERR_LEX)
		add_error(env, "[%s] Lexical error with: '%s' ", as->line, cur->rcode);
	else if (cur->type == ERR_REG)
		add_error(env, "[%s] Bad register number [1-%d]: '%s' ", as->line,
			REG_NUMBER, cur->rcode);
	else if (!(code2type(cur->type) & argtype))
		add_error(env, "[%s] Bad argument type: '%s' ", as->line, cur->rcode);
	if ((str = ft_strchr(cur->rcode, LABEL_CHAR))
		&& (get_labelpc(env->asmb, str + 1) == -1))
		add_error(env, "[%s] Unk. label: '%s' ", as->line, str + 1);
}

/*
** @brief: Checks op validity
**
** @param env: Context structure
** @param cur: Current op
*/

void				check_asm(t_env *env, t_asm *cur)
{
	int				i;
	unsigned int	argc;
	char			*o;
	char			*m;

	i = -1;
	argc = 0;
	o = "argument is expected";
	m = "arguments are expected";
	if (cur->op_code < 0 && cur->argc > 0 && cur->arg)
	{
		if (ft_isstralpha(cur->arg->rcode))
			add_error(env, "[%s] Unk. OP: '%s' ", cur->line, cur->arg->rcode);
		else
			add_error(env, "[%s] Lexical error with: '%s' ", cur->line,
				cur->arg->rcode);
	}
	else if (cur->argc != (argc = op_argc(cur->op_code)) && argc <= 1)
		add_error(env, "[%s] Bad arguments number: %d %s ", cur->line, argc, o);
	else if (cur->argc != argc && argc > 1)
		add_error(env, "[%s] Bad arguments number: %d %s ", cur->line, argc, m);
	while (cur->label && cur->label[++i])
		if (!ft_strchr(LABEL_CHARS, cur->label[i]))
			add_error(env, "[%s] Bad label format: '%c' is not authorized",
				cur->label, cur->label[i]);
}

/*
** @brief: Checks the champion's size
**
** @param env: Context structure
*/

void				check_progsize(t_env *env)
{
	if (!env->header.prog_size)
		add_error(env, "This anemic champion weights 0 bytes");
	else if (env->header.prog_size > CHAMP_MAX_SIZE)
		add_error(env, "Program size (%d b.) exceeds the limit of %d bytes",
			env->header.prog_size, CHAMP_MAX_SIZE);
}

/*
** @brief: Main checker function
**
** @param env: Context structure
** @param head: First op (=> env->asmb)
*/

void				checker(t_env *env, t_asm *head)
{
	t_asm	*asmb;
	t_arg	*arg;
	size_t	len_err;

	asmb = head;
	check_progsize(env);
	while (asmb)
	{
		arg = asmb->arg;
		check_asm(env, asmb);
		while (arg && asmb->op_code > 0)
		{
			len_err = env->err ? ft_strlen(env->err) : 0;
			check_arg(env, asmb, arg, asmb->op_code);
			if (env->err && (ft_strlen(env->err) > len_err))
				break ;
			arg = arg->next;
		}
		asmb = asmb->next;
	}
	if (env->err)
	{
		s_asm_debug(env, asmb);
		error(env, 0, 0);
	}
}
