/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 17:46:00 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/04 17:15:24 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief: Removes leading and trailing space, tabulation, newline, or c chars
** from the string s and returns the result as new string.
**
** @param s: String
** @param c: Char which should be remove
** @return char*: New mallocated string
*/

char			*ft_strtrimc(const char *s, char c)
{
	char	*trim;
	int		i;
	int		a;
	int		z;
	int		diff;

	i = 0;
	a = 0;
	if (!s || !*s)
		return (NULL);
	while (s[a] && (s[a] == ' ' || s[a] == '\t' || s[a] == '\n' || s[a] == c))
		a++;
	z = ft_strlen(s) - 1;
	while (z >= 0 && s[z]
		&& (s[z] == ' ' || s[z] == '\t' || s[z] == '\n' || s[z] == c))
		z--;
	diff = (z < a ? 1 : z - a + 1);
	if ((trim = (char*)malloc(sizeof(char) * (diff + 1))) == NULL)
		return (NULL);
	while (a <= z)
		trim[i++] = s[a++];
	trim[i] = '\0';
	return (trim);
}
