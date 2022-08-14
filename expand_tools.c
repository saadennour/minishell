/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:44:01 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/14 19:12:30 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*assigning(char *more, char *end, t_list **env, int *thief)
{
	int		i;
	t_list	*tmp;
	char	*dollar;
	char	*maybe;

	i = 0;
	tmp = *env;
	dollar = NULL;
	maybe = ft_strjoin("?", end);
	if (ft_strcmp(more, maybe) == 0)
	{
		dollar = ft_itoa(g_exit_status);
		free (maybe);
		return (dollar);
	}
	while (tmp)
	{
		free (maybe);
		maybe = ft_strjoin(tmp->name, end);
		//printf ("p => %p\n", maybe);
		if (ft_strcmp(more, maybe) == 0)
		{
			dollar = tmp->value;
			end = NULL;
			free (maybe);
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
	char	*garbage;
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
		{
			garbage = (*assign);
			(*assign) = ft_strjoin(garbage, dollar);
			free (garbage);
		}
		free (dollar);
		y++;
	}
	free_tab(more, 0);
}

char	*if_dsigne(char *inpt, t_list **env, t_quote quote, int *x)
{
	char	*assign;
	char	**var;
	int		j;

	j = 0;
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
		}
		(*x)++;
		j++;
	}
	free_tab (var, 0);
	return (assign);
}
