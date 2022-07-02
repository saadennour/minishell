/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:01:53 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/02 17:10:29 by sfarhan          ###   ########.fr       */
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
void    printdir()
{
	char *cwd;
	char *dir;

	cwd = malloc(sizeof(char) * 1000);
	getcwd(cwd, sizeof(char) * 1000);
	dir = ft_lastcar(cwd, '/');
	printf("-> %s ",dir);
}

char	*ft_read()
{
	int		size;
	int		i;
	//char 	**arg;
	char	*inpt;

	size = 0;
	i = 0;
	inpt = readline("");
	//parsing(inpt);
	// arg	 = ft_split(inpt,' ',&size);
	// while (i < size)
	// {
	// 	printf ("%s\n", arg[i]);
	// 	i++;
	// }
	//cmd = parsecmd(inpt);
	return (inpt);
}

int main(int ac, char **av, char **envp)
{
	int 	fd;
	char	*buf;
	int		c;

	(void)ac;
	(void)av;
	while ((fd = open("test.txt", O_RDWR)) >= 0)
	{
		if (fd >= 3)
		{
			close (fd);
			break;
		}
	}
	while (1)
	{
		printdir();
		buf = ft_read();
		c = 0;
		if (fork() == 0)
			run_cmd(parsecmd(buf), envp, &c);
		wait(0);
	}
	return (0);
}