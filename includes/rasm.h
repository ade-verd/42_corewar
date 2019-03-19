/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:55:36 by rahassin          #+#    #+#             */
/*   Updated: 2019/03/18 22:21:16 by rahassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RASM_H
# define RASM_H
# include "ft_printf.h"
# include "op.h"

typedef	struct		s_opc
{
	unsigned char	opn : 2;
	unsigned char	op1 : 2;
	unsigned char	op2 : 2;
	unsigned char	op3 : 2;
}					t_opc;

# define USAGE_ASMR	"Usage: ./rasm  <sourcefile.cor>\n"
# define ERR_FRM	"Bad format: files expected <file.cor>\n"
# define ERR_FIL	"Can't read source file\n"
# define ERR_MGN	"Bad magic number\n"
# define ERR_INS	"Bad instruction Stop writing to "
# define ASMR_OK	"Writing output program to "

int					asmr_arg(int o, unsigned char *file, int i, int fd);
int					asmr_instr(int fd, int fdo, int s, int i);
void				asmr(char *file, int len, int i);

#endif
