/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 04:34:11 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/26 22:33:40 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echoprint(char **cmd, int i, t_list *data)
{
	char *line;
	int	j;
	int n;

	j = 0;
	n = i;
	line = NULL;
	data = NULL;
	if (!cmd[i])
		return(1);
	while (cmd[i])
	{	
		line = ft_strjoin(line, cmd[i]);
		if(cmd[++i])
			line = ft_strjoin(line, " ");
	}
	while (line[j])
	{
		write (1, &line[j], 1);
		j++;
	}
	if (n == 1)
		printf("\n");
	return (1);
}

int	ft_echo(char **cmd, t_list *data)
{
	int i;
	int n;

	i = 1;
	while(cmd[i])
	{
		n = 0;
		if(n == 0)
		{
			if(cmd[i][n] != '-')
			{
				if(echoprint(cmd, i, data))
					return (0);
			}
			else
				n++;
		}
		while(cmd[i][n] == 'n')
			n++;
		if(ft_strlen(cmd[i]) == n)
			i++;
		else
			if(echoprint(cmd, i, data))
				return (0);
	}
	echoprint(cmd, i, data);
	return (0);
}

char *no_space(char *str)
{
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	//i can change get token or use it
	while (str[i])
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i] && !(str[i] == 34 && str[i + 1] == ' '))
				i++;
			if (str[i])
				i++;
		}
		if (str[i] == 39)
		{
			i++;
			while (str[i] && !(str[i] == 39 && str[i + 1] == ' '))
				i++;
			if (str[i])
				i++;
		}
		if (str[i] == ' ')
			str[i] = 2;
		i++;
	}
	//printf ("%s\n", str);
	return (str);
}