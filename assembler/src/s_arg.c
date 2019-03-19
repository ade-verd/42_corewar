/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_arg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 18:30:07 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/14 11:26:46 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief: Evaluates the value of a Red Code argument and stores it
**
** @param env: Context structure
** @param asmb: t_asm link
** @param arg: t_arg link
*/

void	s_arg_value_eval(t_env *env, t_asm *asmb, t_arg *arg)
{
	arg->val = get_val(env, asmb, arg);
	arg->realval = arg->val;
	arg->dirsize = 0;
	if (arg->type == REG_CODE)
		arg->val = (unsigned char)arg->val;
	else if (arg->type == IND_CODE)
		arg->val = (unsigned short)arg->val;
	else if (arg->type == DIR_CODE)
	{
		if ((arg->dirsize = dir_size(asmb->op_code)) == 1)
			arg->val = (unsigned short)arg->val;
		else
			arg->val = (unsigned int)arg->val;
	}
}

/*
** @brief: Appends new t_arg
**
** @param env: Context structure
** @param asmb: Corresponding t_asm link
** @param head: t_arg head
** @param str: String as Red Code
*/

void	s_arg_append(t_env *env, t_asm *asmb, t_arg *head, char *str)
{
	t_arg	*new;
	t_arg	*last;

	last = head;
	while (last && last->next)
		last = last->next;
	if (!(new = (t_arg*)malloc(sizeof(t_arg))))
		error(env, (char*)__FUNCTION__, 1);
	new->rcode = ft_strdup(str);
	new->type = wh_type(str);
	s_arg_value_eval(env, asmb, new);
	new->next = NULL;
	new->bytes = analyze_nb_bytes(new, asmb->op_code);
	new->id = last ? last->id + 1 : 0;
	if (!head)
		asmb->arg = new;
	else
		last->next = new;
}

/*
** @brief: t_arg debug. Displays t_arg details
**
** @param env: Context structure
** @param arg: t_arg link
*/

void	s_arg_debug(t_env *env, t_arg *arg)
{
	if (env && env->flags & FLAG_DEBUG && arg)
	{
		ft_printf("\targ[%d]: rcode: |%s|\n", arg->id, arg->rcode);
		if (arg->type == REG_CODE)
			ft_printf("\t\t%.7s: %d -> %s\n", "type", arg->type, "REG_CODE");
		else if (arg->type == DIR_CODE)
			ft_printf("\t\t%.7s: %d -> %s\n", "type", arg->type, "DIR_CODE");
		else if (arg->type == IND_CODE)
			ft_printf("\t\t%.7s: %d -> %s\n", "type", arg->type, "IND_CODE");
		else if (arg->type == OP_CODE)
			ft_printf("\t\t%.7s: %d -> %s\n", "type", arg->type, "OP_CODE");
		else if (arg->type == LABEL_CODE)
			ft_printf("\t\t%.7s: %d -> %s\n", "type", arg->type, "LABEL_CODE");
		else
			ft_printf("\t\t%.7s: %d -> %s\n", "type", arg->type, "NON-AVAIL.");
		ft_printf("\t\t%.7s: %d\n", "realval", arg->realval);
		ft_printf("\t\t%.7s: %d\n", "value", arg->val);
		ft_printf("\t\t%.7s: %d\n", "bytes", arg->bytes);
	}
}

/*
** @brief: Frees every arguments
**
** @param arg: t_arg head
*/

void	s_arg_del(t_arg *arg)
{
	t_arg	*cpy;

	while (arg)
	{
		cpy = arg;
		arg = arg->next;
		if (cpy->rcode)
			ft_strdel(&cpy->rcode);
		ft_memdel((void**)&cpy);
	}
}
