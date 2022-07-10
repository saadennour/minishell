/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dsigne.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 23:44:48 by oel-berh          #+#    #+#             */
/*   Updated: 2022/07/05 23:44:49 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **forenv(char **env)
{
	int     i;
    char     **op;
	char     **operation;
	
	i = 0;
	operation = malloc(sizeof(char *) * 37);
	while(env[i])
	{
        op = ft_split(env[i], '=');
		operation[i] = op[0];
		i++;
	}
	operation[i] = 0;
	return(operation);
}

char	*exdsigne(char *op,char **env)
{
	char **operation;
	int i;

	i = 0;
	while(env[i])
	{
		if(ft_strncmp(op,env[i],ft_strlen(op)) == 0)
		{
			operation = ft_split(env[i],'=');
			return (operation[1]);
		}
		i++;
	}
	return(0);
}

char *ft_merge(char *str, char *buf)
{
	int		i;
	int		j;
	int		x;
	int		count;
	char	*merge;

	count = 0;
	i = 0;
	j = 0;
	x = 0;
	while (buf[i])
	{
		if (buf[i] == 34 || buf[i] == 39)
			count++;
		i++;
	}
	merge = malloc(sizeof(char) * ft_strlen(str) + count);
	i = 0;
	while (buf[i] == 34 || buf[i] == 39)
	{
		merge[x] = buf[i];
		i++;
		x++;
	}
	while (buf[i] && (buf[i] != 34 && buf[i] != 39))
		i++;
	while (str[j])
	{
		merge[x] = str[j];
		x++;
		j++;
	}
	while (buf[i] && (buf[i] == 34 || buf[i] == 39))
	{
		merge[x] = buf[i];
		i++;
		x++;
	}
	merge[x] = '\0';
	return (merge);
}

char	*if_dsigne(char *inpt,char **env)
{
	char	**op;
	char	*dollar;
	char	tmp[2];
	char	**var;
	int		i;

	i = 0;
	tmp[0] = 34;
	tmp[1] = 39;
	//put unprintable char then undo
	var = ft_advanced(inpt, tmp);
	//printf("hadi %s\n", var[0]);
	if(*var[0] == '$')
	{
		var[0]++;
		op = forenv(env);
		while(op[i])
		{
			if(strcmp(var[0],op[i]) == 0)
			{
				dollar = exdsigne(op[i],env);
				dollar = ft_merge(dollar, inpt);
				// printf ("%s\n", dollar);
				return (dollar);
			}
			i++;
		}
	}
	return(0);
}