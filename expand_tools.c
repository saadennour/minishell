/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:44:01 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/14 00:35:26 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*assigning(char *more, char *end, t_list **env, int *thief)
{
	int		i;
	t_list	*tmp;
	char	*dollar;

	i = 0;
	tmp = *env;
	dollar = NULL;
	if (ft_strcmp(more, ft_strjoin("?", end)) == 0)
	{
		dollar = ft_itoa(g_exit_status);
		return (dollar);
	}
	while (tmp)
	{
		if (ft_strcmp(more, ft_strjoin(tmp->name, end)) == 0)
		{
			dollar = tmp->value;
			end = NULL;
			break ;
		}
		tmp = tmp->next;
		if (tmp == NULL)
			(*thief) = 1;
	}
	return (dollar);
}

static char	*edges(char *more, t_list **env)
{
	char	*end;
	char	*dollar;
	int		thief;

	end = NULL;
	thief = 0;
	end = after_world(more);
	dollar = assigning(more, end, env, &thief);
	if (dollar && thief != 1)
		dollar = ft_strjoin(dollar, end);
	else if (thief == 1)
		dollar = "";
	free (end);
	return (dollar);
}

static void	expand(char **assign, t_list **env, char *var)
{
	char	*dollar;
	char	**more;
	int		y;

	y = 0;
	while (var[y])
	{
		if (var[y] == '$')
			break ;
		y++;
	}
	more = dq_undo(var);
	if (y > 0)
	{
		(*assign) = ft_strjoin((*assign), more[0]);
		y = 1;
	}
	while (more[y])
	{
		dollar = edges(more[y], env);
		if (dollar)
			(*assign) = ft_strjoin((*assign), dollar);
		free (dollar);
		y++;
	}
	printf ("hello\n");
	free_tab(more, 0);
}

char	*if_dsigne(char *inpt, t_list **env, t_quote quote, int *x)
{
	char	*assign;
	char	**var;
	int		j;
	int		i;

	// while (1);
	j = 0;
	i = 0;
	assign = NULL;
	var = cashier(inpt);
	while (var[j])
	{
		if (quote.quote[(*x)] == 1)
			expand(&assign, env, var[j]);
		else
		{
			var[j] = sq_undo(var[j]);
			assign = ft_strjoin(assign, var[j]);
			free (var[j]);
		}
		(*x)++;
		j++;
	}
	free_tab (var, 0);
	return (assign);
}
