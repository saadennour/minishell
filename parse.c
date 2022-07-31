/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 02:37:56 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/31 01:10:08 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	count(char *str, char c)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = 0;
// 	if (str == NULL)
// 		return (0);
// 	while (str[i])
// 	{
// 		while (str[i] == c)
// 			i++;
// 		if (str[i] != '\0' && str[i] != c)
// 		{
// 			while (str[i] != '\0' && str[i] != c)
// 				i++;
// 			len++;
// 		}
// 	}
// 	//printf ("len = %d\n", len);
// 	return (len);
// }

int	get_token(char **ps, char **q, char **eq)
{
	char	*s;
	int		i;
	int		token;

	i = 0;
	s = *ps;
	while (s[i] != '\0' && ft_strchr(s[i], " \t\r\n\v\f"))
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
		while (s[i] && !(s[i] == 1 && s[i + 1] == ' '))
			i++;
		if (s[i])
			i++;
	}
	else
	{
		while (s[i] != '\0' && !ft_strchr(s[i], " \t\r\n\v\f") && !ft_strchr(s[i], "|<>") && s[i] != 1)
			i++;
	}
	if (eq)
	{
		*eq = &s[i];
	}
	while (s[i] != '\0' && ft_strchr(s[i], " \t\r\n\v\f"))
		i++;
	*ps = &s[i];
	//printf ("ps =%s\ns =%s\nq =%s\n", *ps, &s[i], *q);
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
	int		x;
	int		total;
	int		words = 0;
	//char	s[1];
	t_cmd	*cmd;

	i = 0;
	x = 0;
	//s[0] = 1;
	words = wd_count(*ps, ' ', 1);
	total = spaces_still(*ps);
	cmd = exelior(*ps);
	exec = (t_exec *)cmd;
	cmd = parsered (cmd, ps, es);
	//printf ("the cmd : %s\nthe words = %d\n", *ps, words);
	while (!exist(ps, "|"))
	{
		if ((token = get_token(ps, &q, &eq)) == 0)
			break ;
		if (token != 'F')
		{
			printf ("Errorr %d\n", i);
			exit (1);
		}
		//for quotes its cuz of the inprintable char 1
		// if (ft_skip(q, s) && !ft_skip(q, " "))
		// 	one = ft_splito(q, 2);
		// else
		one = ft_split(q, ' ', 1);
		exec->args[i] = one[0];
		//printf ("exe[%d] = %s with %d for quote\n", i, exec->args[i], quote.quote[i]);
		if (quote.quote[x] == 1 && ft_skip(exec->args[i], "$"))
		{
			exec->args[i] = if_dsigne(exec->args[i], env);
			//printf ("after exe[%d] = %s|\n", i, exec->args[i]);
		}
		else
			exec->args[i] = no_space(exec->args[i]);
		x = total - spaces_still(*ps);
		i++;
		// if (i > words)
		// 	exit (1);
		cmd = parsered (cmd, ps, es);
	}
	return (cmd);
}

t_cmd	*parsecmd(char *str, char **env)
{
	char	*es;
	int		x;
	int		words;
	t_cmd	*cmd;
	t_quote	quote;

	es = NULL;
	x = 0;
	words = wd_count(str, ' ', 1);
	quote.quote = malloc(sizeof(int) * words + 1);
	while (x < words)
	{
		quote.quote[x] = 1;
		x++;
	}
	quote.quote[x] = 0;
	if (str[0] == '|')
	{
		printf ("minishell: syntax error near unexpected token '|'\n");
		exit (1);
	}
	str = quotes(str, &quote);
	//add redirection rules in ft_path
	//str = ft_path(str);
	es = str + ft_strlen(str);
	cmd = parsepipe(&str, es, env, quote);
	// exist (&str, es, "");
	// if (str != '\0')
	// {
	// 	printf ("Errori\n");
	// 	exit (1);
	// }
	return (cmd);
}

t_cmd	*parsepipe(char	**ps, char *es, char **env, t_quote quote)
{
	t_cmd	*cmd;

	cmd = parseexec(ps, es, env, quote);
	if (exist(ps, "|"))
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

	while (exist(ps, "<>"))
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
