/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dsigne.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 23:44:48 by oel-berh          #+#    #+#             */
/*   Updated: 2022/07/26 20:14:34 by sfarhan          ###   ########.fr       */
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
	int		count;
	char	*merge;

	i = 0;
	j = 0;
	count = 0;
	printf ("%s , %s\n", str, buf);
	while (buf[i])
	{
		if (buf[i] == 1)
			i++;
		else if (buf[i] == '$')
		{
			while (buf[i] && buf[i] != 1)
				i++;
		}
		else
		{
			count++;
			i++;
		}
	}
	merge = malloc (sizeof(char) * ft_strlen(str) + count + 1);
	i = 0;
	while (buf[i])
	{
		if (buf[i] == 1)
			i++;
		else if (buf[i] == '$')
			break ;
		else
		{
			merge[j] = buf[i];
			j++;
			i++;
		}
	}
	x = 0;
	while (str[x])
	{
		merge[j] = str[x];
		j++;
		x++;
	}
	while (buf[i] && buf[i] != 1)
		i++;
	while (buf[i])
	{
		if (buf[i] == 1)
			i++;
		else
		{
			merge[j] = buf[i];
			j++;
			i++;
		}
	}
	merge[j] = '\0';
	printf ("%s\n", merge);
	return (merge);
}

char	*if_dsigne(char *inpt, char **env)
{
	char	**op;
	char	*dollar;
	char	tmp[3];
	char	**var;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp[0] = 34;
	tmp[1] = 39;
	tmp[2] = 1;
	//put unprintable char then undo
	var = ft_advanced(inpt, tmp);
	while (var[j])
	{
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
