/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dsigne.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 23:44:48 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/06 05:00:07 by sfarhan          ###   ########.fr       */
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

// static int	cashier(char *str)
// {
// 	int	i;
// 	int	dollar;

// 	i = 0;
// 	dollar = 0;
// 	while (str[i])
// 	{
// 		while (str[i] == '$')
// 			dollar++;
// 		i++;
// 	}
// }

char	*after_world(char *str)
{
	int		i;
	int		len;
	char	*quote;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39 || str[i] == ' ')
			break ;
		i++;
	}
	if (str[i] == '\0')
		return (NULL);
	len = ft_strlen(str) - i;
	quote = malloc (sizeof(char) * (len + 1));
	len = 0;
	while (str[i])
	{
		quote[len] = str[i];
		i++;
		len++;
	}
	quote[len] = '\0';
	return (quote);
}

static char *assigning(char *more, char *end, char **env, int *thief)
{
	int		i;
	char	**op;
	char	*dollar;
	
	i = 0;
	op = forenv(env);
	while (op[i])
	{
		if (strcmp(more, ft_strjoin(op[i], end)) == 0)
		{
			dollar = exdsigne(op[i], env);
			end = NULL;
			break ;
			free (op);
		}
		i++;
		if (op[i] == NULL)
		{
			(*thief) = 1;
			dollar = "";
		}
	}
	return (dollar);
}

static char *edges(char *more, char **env)
{
	char	*end;
	char	*dollar;
	char	quote[3];
	int		thief;

	end = NULL;
	thief = 0;
	quote[0] = 34;
	quote[1] = 39;
	quote[2] = ' ';
	if (ft_skip(more, quote))
		end = after_world(more);
	dollar = assigning(more, end, env, &thief);
	if (ft_skip(more, quote))
	{
		if (dollar && thief != 1)
			dollar = ft_strjoin(dollar, after_world(more));
		else if (thief == 1)
			dollar = after_world(more);
	}
	return (dollar);
}

char	*if_dsigne(char *inpt, char **env, t_quote quote, int *x)
{
	char	*dollar = NULL;
	char	*assign = NULL;
	char	**var;
	char	**more;
	int		i;
	int		j;
	int		y;
	int		words;
	char	split[1];

	split[0] = 1;
	i = 0;
	j = 0;
	y = 0;
	words = 0;
	if (ft_strlen(inpt) == 1)
		return ("$");
	// else if (ft_strlen(inpt) > 1)
	// {
	// 	while (inpt[i])
	// 	{
	// 		while (inpt[i] == '$' && inpt[i + 1] == '$')
	// 			return ("");
	// 		i++;
	// 	}
	// }
	var = ft_advanced(inpt, split);
	while (var[j])
	{
		if (quote.quote[(*x)] == 1 && ft_skip(var[j], "$"))
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
				dollar = edges(more[y], env);
				if (dollar)
				{
					assign = ft_strjoin(assign, dollar);
					dollar = NULL;
				}
				y++;
			}
		}
		else
			assign = ft_strjoin(assign, var[j]);
		(*x)++;
		j++;
	}
	return (assign);
}


				// i = 0;
				// if (ft_skip(more[y], quote))
				// 	tmp = after_world(more[y]);
				// op = forenv(env);
				// while (op[i])
				// {
				// 	if (strcmp(more[y], ft_strjoin(op[i], tmp)) == 0)
				// 	{
				// 		dollar = exdsigne(op[i], env);
				// 		tmp = NULL;
				// 		break ;
				// 		free (op);
				// 	}
				// 	i++;
				// 	if (op[i] == NULL)
				// 	{
				// 		thief = 1;
				// 		dollar = "";
				// 	}
				// }
				// if (ft_skip(more[y], quote))
				// {
				// 	if (dollar && thief != 1)
				// 		dollar = ft_strjoin(dollar, after_world(more[y]));
				// 	else if (thief == 1)
				// 		dollar = after_world(more[y]);
				// }