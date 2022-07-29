/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dsigne.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 23:44:48 by oel-berh          #+#    #+#             */
/*   Updated: 2022/07/29 01:47:49 by sfarhan          ###   ########.fr       */
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

char	*if_dsigne(char *inpt, char **env)
{
	char	**op;
	char	*dollar = NULL;
	char	*assign = NULL;
	char	**var;
	int		i;
	int		j;
	int		words;

	i = 0;
	j = 0;
	words = 0;
	//put unprintable char then undo
	var = ft_advanced(inpt, "* ");
	// while (var[j])
	// {
	// 	printf ("var[%d] = %s\n", j, var[j]);
	// 	j++;	
	// }
	// j = 0;
	while (var[j])
	{
		//printf ("%c\n", var[j][0]);
		if (var[j][0] == '$')
		{
	 		op = forenv(env);
			i = 0;
			while (op[i])
			{
				if (strncmp(&var[j][1], op[i], ft_strlen(&var[j][1])) == 0)
				{
					dollar = exdsigne(op[i], env);
					break ;
				}
				i++;
				if (op[i] == 0)
					dollar = "";
			}
		}
		// if (var[j][0] != 34 && var[j][0] != 39)
		// 	dollar = ft_strjoin(dollar, " ");
		if (dollar == 0)
			assign = ft_strjoin(assign, var[j]);
		else
		{
			assign = ft_strjoin(assign, dollar);
			dollar = NULL;
		}
		j++;
		//printf ("assign %d = %s\n", j , assign);
	}
	return (assign);
}
