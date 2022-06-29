/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 02:37:56 by sfarhan           #+#    #+#             */
/*   Updated: 2022/06/29 18:56:21 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token(char **ps, char *es, char **q, char **eq)
{
	char	*s = NULL;
	int		token;

	s = *ps;
	while (s < es && ft_strchr(s, " \t\n\f\v\r"))
		s++;
	if (q)
		*q = s;
	token = *s;
	if (*s == 0)
		return (token);
	else if (*s == '|')
	{
		s++;
		token = '|';
	}
	else if (*s == '<' || *s == '>')
		token = followed(&s);
	else
		token = 'F';
	while (s < es && !ft_strchr(s, " \t\n\f\v\r") && !ft_strchr(s, "|<>"))
		s++;
	if (eq)
	{
		//printf ("hna\n");
		*eq = s;
	}
	while (s < es && ft_strchr(s, " \t\n\f\v\r"))
		s++;
	*ps = s;
	//printf ("%s %s\n", *q, *eq);
	return (token);
}

t_cmd	*parseexec(char **ps, char *es)
{
	t_exec	*exec;
	char	*q, *eq;
	int		token , i;
	t_cmd	*cmd;

	i = 0;
	cmd = exelior();
	exec = (t_exec*)cmd;
	//printf ("parsered\n");
	cmd = parsered (cmd, ps ,es);
	while (!exist(ps, es, "|"))
	{
		//printf ("1\n");
		if ((token = get_token(ps, es, &q, &eq)) == 0)
			break;
		if (token != 'F')
		{
			printf ("Error\n");
			exit (1);
		}
		exec->args[i] = q;
		exec->erags[i] = eq;
		i++;
		if (i >= 10)
			exit (1);
		cmd = parsered (cmd, ps, es);
	}
	exec->args[i] = 0;
	exec->erags[i] = 0;
	return (cmd);
}

t_cmd	*parsecmd(char *str)
{
	char	*es;
	t_cmd	*cmd;

	es = str + ft_strlen(str);
	//printf ("parsepipe\n");
	cmd = parsepipe(&str, es);
	exist (&str, es, "");
	if (str != es)
	{
		printf ("Error\n");
		exit (1);
	}
	return (cmd);
}

t_cmd	*parsepipe(char	**ps, char *es)
{
	t_cmd	*cmd;

	//printf ("parsexec\n");
	cmd = parseexec(ps, es);
	if (exist(ps, es, "|"))
	{
		get_token(ps, es, 0, 0);
		cmd = piping(cmd, parsepipe(ps, es));
	}
	return (cmd);
}

t_cmd	*parsered(t_cmd	*cmd, char **ps, char *es)
{
	int		token;
	char	*q;
	char	*eq;

	while (exist(ps, es, "<>"))
	{
		//printf ("salam\n");
		token = get_token(ps, es, 0, 0);
		if (get_token(ps, es, &q, &eq) != 'F')
		{
			printf ("Erroro\n");
			exit (1);
		}
		if (token == '<')
		{
			//printf ("mrhba\n");
			cmd = redirect(cmd, q, eq, O_RDONLY, 0);
			break;
		}
		else if (token == '>')
		{
			cmd = redirect(cmd, q, eq, O_WRONLY | O_CREAT | O_TRUNC, 1);
			break;
		}
		else if (token == '+')
		{
			cmd = redirect (cmd, q, eq, O_WRONLY | O_CREAT, 1);
			break;
		}
		else if (token == '-')
		{
			cmd = redirect (cmd, q ,eq , 0, 0);
			break;
		}
	}
	return (cmd);
}
