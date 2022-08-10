/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:01:53 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/10 12:02:11 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

char	*ft_lastcar(char *str, char c)
{
	int	lent;

	lent = ft_strlen(str);
	while (*str)
		str++;
	while (lent)
	{
		if (*str == c)
		{
			str++;
			return (str);
		}
		lent--;
		str--;
	}
	return (NULL);
}

void	handle_c(int sig)
{
	if (sig == 2)
	{
		printf ("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_d(int sig)
{
	if (sig == 11)
	{
		rl_replace_line("", 0);
		printf ("exit\n");
		exit(0);
	}
}

void	handle_s(int sig)
{
	if (sig == 3)
		readline ("-> minishell ");
}

int	main(int ac, char **av, char **envp)
{
	char	*buf;
	t_list	*data;
	t_tool	tools;

	tools.fd = 0;
	tools.limiter = NULL;
	tools.c = 10;
	tools.stdin_copy = dup(STDIN_FILENO);
	tools.stdout_copy = dup(STDOUT_FILENO);
	data = NULL;
	(void) ac;
	(void) av;
	signal (SIGINT, handle_c);
	signal (SIGSEGV, handle_d);
	signal (SIGQUIT, handle_s);
	while (1)
	{
		buf = readline("-> minishell ");
		add_history(buf);
		if (fork() == 0)
			run_cmd(parsecmd(buf, envp), envp, &tools, &data);
		wait(0);
		//free (buf);
		//system("leaks minishell");
	}
	return (0);
}
