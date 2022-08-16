/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:34:38 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/16 01:42:25 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenizer(char *s, int *x)
{
	int		token;
	int		i;

	i = (*x);
	token = s[i];
	if (s[i] == 0)
		return (token);
	else if (s[i] == '|')
	{
		i++;
		token = '|';
	}
	else if (s[i] == '<' || s[i] == '>')
		token = followed(s, &i);
	else
		token = 'F';
	*x = i;
	return (token);
}

int	exec_args(t_exec **exec, int i, char **ps)
{
	char		**one;
	char		*q;
	int			token;

	token = get_token(ps, &q);
	if (token == 0)
		return (0);
	if (token != 'F')
	{
		printf ("syntax error unexpected token '%c'\n", token);
		return (0);
	}
	one = ft_split(q, ' ', 1);
	if (ft_strlen(one[0]) == 0)
		one[0] = " ";
	(*exec)->args[i] = one[0];
	free_tab(one, 1);
	return (1);
}

char	*clean(char *str)
{
	int		i;
	int		j;
	char	*clean;

	i = 0;
	j = 0;
	while (str[i] != '\0' && !ft_strchr(str[i], " \t\n\f\v\r"))
	{
		if (str[i] == 1)
			j++;
		i++;
	}
	clean = malloc (sizeof(char) * (i - j + 1));
	i = 0;
	j = 0;
	while (str[i] != '\0' && !ft_strchr(str[i], " \t\n\f\v\r"))
	{
		if (str[i] == 1)
			i++;
		else
			clean[j++] = str[i++];
	}
	clean[j] = '\0';
	return (clean);
}

void	ft_skip_spaces(char *inpt, int *i)
{
	while (inpt[(*i)] != '\0' && ft_strchr(inpt[(*i)], " \t\n\f\v\r"))
			(*i)++;
}

char *skip_c(char *str, char c)
{
	while(*str && *str != c)
		str++;
	return(str);
}
