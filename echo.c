/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 04:34:11 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/29 02:00:46 by sfarhan          ###   ########.fr       */
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
	int		len;
	int		quote;
	char	*buf;
	
	i = 0;
	len = 0;
	quote = 0;
	//i can change get token or use it
	while (str[i])
	{
		if (str[i] == 1)
			quote++;
		i++;
	}
	len = ft_strlen(str) - quote;
	buf = malloc (sizeof(char) * len + 1);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == 1)
			i++;
		buf[len] = str[i];
		len++;
		i++;
	}
	buf[len] = '\0';
	//printf ("with no space : %s\n", str);
	return (buf);
}

int	spaces_still(char *str)
{
	int	i;
	int	spaces;
	
	i = 0;
	spaces = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			spaces++;
		i++;
	}
	return (spaces);
}