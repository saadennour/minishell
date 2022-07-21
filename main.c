/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:01:53 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/21 14:53:19 by sfarhan          ###   ########.fr       */
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

void	handle_C(int sig)
{
	if (sig == 2)
	{
		printf ("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_D(int sig)
{
	if (sig == 11)
	{
		rl_replace_line("", 0);
		printf ("exit\n");
		rl_redisplay();
		exit(0);
	}
}

void	handle_S(int sig)
{
	if (sig == 3)
	{
		printf ("-> minishell ");
		rl_redisplay();
	}
}

char	*ft_read()
{
	char	*inpt;
	
	inpt = readline("-> minishell ");
	inpt = ft_skip_spaces(inpt);
	while(if_builtins(inpt) == 0)
	{
		inpt = readline("-> minishell ");
		inpt = ft_skip_spaces(inpt);
	}
	return (inpt);
}

int main(int ac, char **av, char **envp)
{
	char	*buf;
	int		c;
	char	*limiter = NULL;

	(void)ac;
	(void)av;
	signal(SIGINT, handle_C);
	signal(SIGSEGV, handle_D);
	signal(SIGQUIT, handle_S);
	while (1)
	{
		c = 0;
		buf = ft_read();
		add_history(buf);
		if (fork() == 0)
			run_cmd(parsecmd(buf, envp), envp, &c, &limiter);
		wait(0);
	}
	return (0);
}