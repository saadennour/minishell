/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:01:53 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/03 00:06:15 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

// return pointer to the name directory
char *ft_lastcar(char *str, char c)
{
	int lent;

	lent = ft_strlen(str);
	while(*str)
		str++;
	while(lent)
	{
		if(*str == c)
		{
			str++;
			return(str);
		}
		lent--;
		str--;
	}
	return(NULL);
}

//printf the name directory
char *    printdir()
{
	char *cwd;
	char *dir;

	cwd = malloc(sizeof(char) * 1000);
	getcwd(cwd, sizeof(char) * 1000);
	dir = ft_lastcar(cwd, '/');
	return (dir);
}


int main(int ac, char **av, char **envp)
{
	char	*buf;
	int		c;

	(void)ac;
	(void)av;
	while (1)
	{
		buf = readline("-> minishell ");
		c = 0;
		if (fork() == 0)
			run_cmd(parsecmd(buf), envp, &c);
		wait(0);
	}
	return (0);
}