/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dsigne.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 23:44:48 by oel-berh          #+#    #+#             */
/*   Updated: 2022/07/27 05:43:44 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**forenv(char **env)
{
	int		i;
	char	**op;
	char	**operation;

	i = 0;
	while (env[i])
		i++;
	operation = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		op = ft_split(env[i], '=', 0);
		operation[i] = op[0];
		i++;
	}
	operation[i] = 0;
	return (operation);
}

char	*exdsigne(char *op, char **env)
{
	char	**operation;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(op, env[i], ft_strlen(op)) == 0)
		{
			operation = ft_split(env[i], '=', 0);
			return (operation[1]);
		}
		i++;
	}
	return (0);
}

char	*ft_merge(char *str, char *buf)
{
	int		i;
	int		j;
	int		x;
	int		len;
	char	*merge;
	char	**slice;

	i = 0;
	j = 0;
	x = 0;
	len = 0;
	slice = ft_advanced(buf, "*");
	while (slice[j])
	{
		i = 0;
		//printf ("slice %s\n", slice[j]);
		while (slice[j][i])
		{
			if (slice[j][i] == '$')
			{
				while (slice[j][i] && slice[j][i] != 34 && slice[j][i] != 39)
					i++;
				if (slice[j][i] == '\0')
					break ;
			}
			len++;
			i++;
		}
		j++;
	}
	//printf ("%d + %d\n", len, ft_strlen(str));
	len += ft_strlen(str);
	//printf ("%d\n", len);
	merge = malloc(sizeof(char) * (len + 1));
	i = 0;
	j = 0;
	while (j < len)
	{
		if (slice[0][i] == '$')
		{
			while (str[x])
			{
				merge[j] = str[x];
				//printf ("merge[%d] : %c\n", j, merge[j]);
				j++;
				x++;
			}
			while (slice[0][i] && slice[0][i] != ' ' && slice[0][i] != 34 && slice[0][i] != 39)
				i++;
			if (slice[0][i] == '\0')
				break ;
		}
		merge[j] = slice[0][i];
		//printf ("merge[%d] : %c\n", j, merge[j]);
		j++;
		i++;
	}
	merge[j] = '\0';
	printf ("%s\n", merge);
	return (merge);
}

char	*if_dsigne(char *inpt, char **env)
{
	char	**op;
	char	*dollar;
	char	tmp[4];
	char	**var;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp[0] = 34;
	tmp[1] = 39;
	tmp[2] = '*';
	//tmp[3] = ' ';
	//put unprintable char then undo
	var = ft_advanced(inpt, tmp);
	while (var[j])
	{
		printf ("%s\n", var[j]);
		if (var[j][0] == '$')
			break ;
		j++;
	}
	// if (var[j] == NULL)
	// 	return (0);
	if (var[j][0] == '$')
	{
		//var[j]++;
	 	op = forenv(env);
		while (op[i])
		{
			if (strncmp(&var[j][1], op[i], ft_strlen(&var[j][1])) == 0)
			{
				dollar = exdsigne(op[i], env);
				//printf ("%s\n", dollar);
				dollar = ft_merge(dollar, inpt);
				//printf ("%s\n", dollar);
				return (dollar);
			}
			i++;
		}
	}
	return (0);
}
