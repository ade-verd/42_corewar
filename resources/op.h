/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2018/10/31 11:11:37 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

#define IND_SIZE				2
// Taille d'un registre
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
// En tout état de cause, la mémoire est circulaire et fait MEM_SIZE octets.
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
//Les champions ne peuvent pas dépasser CHAMP_MAX_SIZE, sinon c’est une erreur.
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

// Nombre de registre pour un processus
#define REG_NUMBER				16

// Tous les CYCLE_TO_DIE, vérification que chaque processus a effectué au moins
// un live depuis la dernière verif.
#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
// Si au cours d’une de ces vérifications on se rend compte qu’il y a eu au moins
// NBR_LIVE exécutions delivedepuis la dernière vérification en date, on décrémente
//  CYCLE_TO_DIE de CYCLE_DELTA unités.
#define NBR_LIVE				21
// Si on n’a pas décrémenté CYCLE_TO_DIE depuis MAX_CHECKS vérifications,on le décrémente
#define MAX_CHECKS				10

/*
**
*/

	typedef char t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

/*
**
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		header_s
{
  unsigned int		magic;
  char				prog_name[PROG_NAME_LENGTH + 1];
  unsigned int		prog_size;
  char				comment[COMMENT_LENGTH + 1];
}					header_t;
