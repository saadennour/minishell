/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sidekick.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:12:21 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/07 18:00:15 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *src)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = 0;
	p = NULL;
	while (src[i])
		i++;
	p = malloc((i + 1) * sizeof(char));
	if (!(p))
		return (NULL);
	while (i > 0)
	{
		p[j] = src[j];
		j++;
		i--;
	}
	p[j] = '\0';
	return (p);
}
