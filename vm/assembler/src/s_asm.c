/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_asm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 18:30:07 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/14 13:00:32 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief: Completes s_asm_append and initializes some variables.
**
** @param env: Context structure
** @param last: Last t_asm link
** @param new: New t_asm link
** @param explod: Exploded line
*/

static void	s_asm_otherval(t_env *env, t_asm *last, t_asm *new, char **explod)
{
	int	i;

	i = 0;
	if (explod && is_llabel(explod[i]))
		new->label = ft_strtrimc(explod[i++], LABEL_CHAR);
	else
		new->label = last ? ft_strdup(last->label) : NULL;
	new->op_code = is_op(explod[i]) > 0 ? optocode(explod[i++])
					: is_op(explod[i]);
	new->coding = got_octalcoding(new->op_code);
	new->argc = ft_arrstrlen(explod) - i;
	new->arg = NULL;
	while (explod[i])
		s_arg_append(env, new, new->arg, explod[i++]);
	new->pc = last ? last->pc + last->bytes : 0;
	new->bytes = countbytes(new, new->arg);
	env->header.prog_size = new->pc + new->bytes;
	new->next = NULL;
}

/*
** @brief: Appends new t_asm link
**
** @param env: Context structure
** @param head: t_asm head
** @param line: Line from file.s
** @param explod: Exploded line
*/

void		s_asm_append(t_env *env, t_asm *head, char *line, char **explod)
{
	t_asm	*new;
	t_asm	*last;

	if (!line || !explod || !explod[0])
		return ;
	last = head;
	while (last && last->next)
		last = last->next;
	if (!(new = (t_asm*)malloc(sizeof(t_asm))))
		error(env, (char*)__FUNCTION__, 1);
	new->line = ft_strdup(line);
	s_asm_otherval(env, last, new, explod);
	if (!head)
		env->asmb = new;
	else
		last->next = new;
	s_asm_debug(env, new);
}

/*
** @brief: t_asm debug. Displays t_asm link details
**
** @param env: Context struct
** @param asmb: t_asm link
*/

void		s_asm_debug(t_env *env, t_asm *asmb)
{
	int		i;
	t_arg	*cpy;

	i = 0;
	cpy = asmb ? asmb->arg : NULL;
	if (env && env->flags & FLAG_DEBUG && asmb)
	{
		ft_printf("line:\t|%s|\n", asmb->line);
		ft_printf("\tlabel:\t|%s|\n", asmb->label);
		ft_printf("\top_code:\t%d -> ", asmb->op_code);
		while (g_op_tab[i].op)
		{
			if (g_op_tab[i].op_code == (unsigned int)asmb->op_code)
				ft_printf("%s\n", g_op_tab[i].op);
			i++;
		}
		ft_printf("\targc:\t%d\n", asmb->argc);
		while (cpy)
		{
			s_arg_debug(env, cpy);
			cpy = cpy->next;
		}
		ft_printf("\tpc:\t%d\n", asmb->pc);
		ft_printf("\tbytes:\t%d\n", asmb->bytes);
	}
}

/*
** @brief: Complete missing values. The first time, some values were missing
** because they were not yet parsed.
**
** @param env: Context structure
** @param head: t_asm head
*/

void		s_asm_complete_missing_values(t_env *env, t_asm *head)
{
	t_asm		*asmb;
	t_arg		*arg;
	intmax_t	val;

	asmb = head;
	val = 0;
	while (asmb)
	{
		arg = asmb->arg;
		while (arg)
		{
			val = arg->val;
			if (ft_strchr(arg->rcode, LABEL_CHAR))
				s_arg_value_eval(env, asmb, arg);
			if ((env->flags & FLAG_DEBUG) && val != arg->val)
			{
				ft_printf("UPDATE value from line: |%s|\n", asmb->line);
				s_arg_debug(env, arg);
			}
			arg = arg->next;
		}
		asmb = asmb->next;
	}
}

/*
** @brief: Frees t_asm
**
** @param asmb: t_asm head
*/

void		s_asm_del(t_asm *asmb)
{
	t_asm	*cpy;

	while (asmb)
	{
		cpy = asmb;
		asmb = asmb->next;
		if (cpy->line)
			ft_strdel(&cpy->line);
		if (cpy->label)
			ft_strdel(&cpy->label);
		if (cpy->arg)
			s_arg_del(cpy->arg);
		ft_memdel((void**)&cpy);
	}
}
