/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dsigne.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 23:44:48 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/04 04:57:57 by sfarhan          ###   ########.fr       */
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

char	*after_world(char *str)
{
	int	i;
	int	len;
	char	*quote;

	i = 0;
	len = 0;
	//printf ("str = %s\n", str);
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39 || str[i] == ' ')
			break ;
		i++;
	}
	if (str[i] == '\0')
		return (NULL);
	len = ft_strlen(str) - i;
	//printf ("%d, %d\n", len , i);
	quote = malloc (sizeof(char) * (len + 1));
	len = 0;
	while (str[i])
	{
		quote[len] = str[i];
		i++;
		len++;
	}
	quote[len] = '\0';
	//printf ("quote = %s\n", quote);
	return (quote);
}


char	*if_dsigne(char *inpt, char **env)
{
	char	**op;
	char	*dollar = NULL;
	char	*assign = NULL;
	char	**var;
	char	**more;
	int		thief;
	int		i;
	int		j;
	int		x;
	int		y;
	int		words;
	char	split[1];
	char	quote[3];
	char	*tmp = NULL;

	split[0] = 1;
	quote[0] = 34;
	quote[1] = 39;
	quote[2] = ' ';
	i = 0;
	j = 0;
	x = 0;
	y = 0;
	thief = 0;
	words = 0;
	//put unprintable char then undo
	if (ft_strlen(inpt) == 1)
		return ("$");
	// else if (ft_strlen(inpt) > 1)
	// {
	// 	while (inpt[i])
	// 	{
	// 		if (inpt[i] == '$' && inpt[i + 1] == '$')
	// 			return ("");
	// 		i++;
	// 	}
	// }
	i = 0;
	var = ft_advanced(inpt, split);
	while (var[j])
	{
		if (ft_skip(var[j], "$"))
		{
			y = 0;
			while (var[j][y])
			{
				if (var[j][y] == '$')
					break ;
				y++;
			}
			more = ft_splito(var[j], '$');
			if (y > 0)
			{
				assign = ft_strjoin(assign, more[0]);
				y = 1;
			}
			while (more[y])
			{
				//printf ("yes\n");
				i = 0;
				if (ft_skip(more[y], quote))
				{
					tmp = after_world(more[y]);
					//printf ("tmp = %s\n", tmp);
				}
				op = forenv(env);
				while (op[i])
				{
					//printf ("%s %s\n", more[y], op[i]);
					if (strcmp(more[y], ft_strjoin(op[i], tmp)) == 0)
					{
						dollar = exdsigne(op[i], env);
						//printf ("dollar = %s\n", dollar);
						tmp = NULL;
						break ;
						free (op);
					}
					i++;
					if (op[i] == NULL)
					{
						thief = 1;
						dollar = "";
					}
				}
				if (ft_skip(more[y], quote))
				{
					//printf ("ana mqewed\n");
					if (dollar && thief != 1)
						dollar = ft_strjoin(dollar, after_world(more[y]));
					else if (thief == 1)
						dollar = after_world(more[y]);
				}
				if (dollar)
				{
					//printf ("ana mqewed fdsfdsfds\n");
					assign = ft_strjoin(assign, dollar);
					dollar = NULL;
					//printf ("assign = %s\n", assign);
				}
				y++;
			}
		}
		else
			assign = ft_strjoin(assign, var[j]);
		j++;
	}
	return (assign);
}
