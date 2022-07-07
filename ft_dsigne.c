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

char	*if_dsigne(char *inpt,char **env)
{
	char	**op;
	char	*dollar;
	int		i;

	i = 0;
	if(*inpt == '$')
	{
		inpt++;
		op = forenv(env);
		while(op[i])
		{
			if(strcmp(inpt,op[i]) == 0)
			{
				dollar = exdsigne(op[i],env);
				return (dollar);
			}
			i++;
		}
	}
	return(0);
}