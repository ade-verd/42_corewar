/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahassin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 19:16:48 by rahassin          #+#    #+#             */
/*   Updated: 2019/03/20 15:22:29 by rahassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rasm.h"

int		main(int argc, char **argv)
{
	int		i;
	int		len;

	i = 1;
	if (argc == 1)
		ft_putstr(USAGE_ASMR);
	else
		while (argv[i])
		{
			len = ft_strlen(argv[i]);
			if (len > 4 && !ft_strcmp(&argv[i][len - 4], ".cor"))
				asmr(argv[i], len, 0, 0);
			else
				ft_putstr_fd(ERR_FRM, 2);
			i++;
		}
}
