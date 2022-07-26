/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 02:37:56 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/26 03:40:13 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token(char **ps, char **q, char **eq)
{
	char	*s;
	int		i;
	int		token;
	char	quote[1];

	i = 0;
	quote[0] = 1;
	s = *ps;
	while (s[i] != '\0' && ft_strchr(s[i], " \t\n\f\v\r"))
		i++;
	if (q)
		*q = &s[i];
	token = s[i];
	if (s[i] == 0)
		return (token);
	else if (s[i] == '|')
	{
		i++;
		token = '|';
	}
	else if (s[i] == '<' || s[i] == '>')
		token = followed(&s);
	else
		token = 'F';
	if (s[i] == 1)
	{
		i++;
		while (s[i] != '\0' && !(s[i] == 1 && s[i + 1] == ' '))
			i++;
		if (s[i] != '\0')
			i++;
	}
	else
	{
		while (s[i] != '\0' && !ft_strchr(s[i], " \t\n\f\v\r") && !ft_strchr(s[i], "|<>") && !ft_strchr(s[i], quote))
			i++;
	}
	if (eq)
	{
		*eq = &s[i];
	}
	while (s[i] != '\0' && ft_strchr(s[i], " \t\n\f\v\r"))
		i++;
	*ps = &s[i];
	//printf ("%sh || %sh\n", *ps, &s[i]);
	return (token);
}

t_cmd	*parseexec(char **ps, char *es, char **env, t_quote quote)
{
	t_exec	*exec;
	char	*q;
	char	*eq;
	char	**one;
	int		token;
	int		i;
	int		words;
	t_cmd	*cmd;

	i = 0;
	words = wd_count(*ps, ' ', 1);
	cmd = exelior(*ps);
	exec = (t_exec *)cmd;
	cmd = parsered (cmd, ps, es);
	while (!exist(ps, es, "|"))
	{
		if ((token = get_token(ps, &q, &eq)) == 0)
			break ;
		if (token != 'F')
		{
			printf ("Errorr %d\n", i);
			exit (1);
		}
		one = ft_split(q, ' ', 1);
		exec->args[i] = one[0];
		//printf ("exe[%d] = %s\n", i, exec->args[i]);
		if (quote.quote[i] == 1 && if_dsigne(exec->args[i], env) != 0)
		{
			exec->args[i] = if_dsigne(exec->args[i], env);
			//printf ("exe[%d] = %s\n", i, exec->args[i]);
		}
		i++;
		if (i > words)
			exit (1);
		cmd = parsered (cmd, ps, es);
	}
	//exit (1);
	return (cmd);
}

t_cmd	*parsecmd(char *str, char **env)
{
	char	*es;
	t_cmd	*cmd;
	t_quote	quote;

	es = NULL;
	quote.quote = malloc(sizeof(int) * wd_count(str, ' ', 1) + 1);
	if (str[0] == '|')
	{
		printf ("minishell: syntax error near unexpected token '|'\n");
		exit (1);
	}
	str = quotes(str, &quote);
	//add redirection rules in ft_path
	str = ft_path(str);
	es = str + ft_strlen(str);
	cmd = parsepipe(&str, es, env, quote);
	// exist (&str, es, "");
	if (str != es)
	{
		printf ("Errori\n");
		exit (1);
	}
	return (cmd);
}

t_cmd	*parsepipe(char	**ps, char *es, char **env, t_quote quote)
{
	t_cmd	*cmd;

	cmd = parseexec(ps, es, env, quote);
	if (exist(ps, es, "|"))
	{
		get_token(ps, 0, 0);
		cmd = piping(cmd, parsepipe(ps, es, env, quote));
	}
	return (cmd);
}

t_cmd	*parsered(t_cmd	*cmd, char **ps, char *es)
{
	int		token;
	char	*q;
	char	*eq;
	char	*clear;

	while (exist(ps, es, "<>"))
	{
		token = get_token(ps, 0, 0);
		if (get_token(ps, &q, &eq) != 'F')
		{
			printf ("Error missing file\n");
			exit (1);
		}
		clear = clean(q);
		if (token == '<')
			cmd = redirect(cmd, clear, O_RDONLY, 0, 1);
		else if (token == '>')
			cmd = redirect(cmd, clear, O_WRONLY | O_CREAT | O_TRUNC, 1, 2);
		else if (token == '+')
			cmd = redirect (cmd, clear, O_WRONLY | O_CREAT | O_APPEND, 1, 3);
		else if (token == '-')
			cmd = redirect (cmd, clear, O_RDONLY, 0, 4);
		cmd = parsered(cmd, ps, es);
	}
	return (cmd);
}
