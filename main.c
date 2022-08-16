/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:01:53 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/16 23:08:11 by sfarhan          ###   ########.fr       */
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
		g_exit_status = 1;
	}
}

void	handle_d(int sig)
{
	if (sig == 11)
	{
		printf ("exit\n");
		exit(0);
	}
}

void	handle_s(int sig)
{
	if (sig == 3)
	{
		write(1, "Quit: 3", 7);
		write(1, "\n", 1);
		exit (131);
	}
}

int	main(int ac, char **av, char **envp)
{
	int		wait_status;
	int		error;
	char	*buf;
	t_list	*data;
	t_tool	tools;
	t_cmd	*cmd;
	pid_t	pid;

	tools.fd = 0;
	tools.envp = envp;
	tools.limiter = NULL;
	tools.in = 0;
	tools.out = 0;
	tools.free = 0;
	tools.stdin_copy = dup(STDIN_FILENO);
	tools.stdout_copy = dup(STDOUT_FILENO);
	data = NULL;
	(void) ac;
	(void) av;
	tools.path = getcwd(NULL, 0);
	ft_envp(envp, &data);
	while (1)
	{
		error = 0;
		buf = readline("-> minishell ");
		if (buf == NULL)
		{
			printf ("exit\n");
			exit(0);
		}
		add_history(buf);
		cmd = parsecmd(buf, &data);
		if (ifexit(cmd) || ifenv(cmd, &data, &tools.path))
			continue ;
		else
		{
			pid = fork();
			if (pid == 0)
			{
				signal (SIGINT, handle_c);
				signal (SIGQUIT, handle_s);
				error = run_cmd(cmd, &tools, &data);
			}
			signal (SIGINT, SIG_IGN);
			signal (SIGQUIT, SIG_IGN);
			waitpid(pid, &wait_status, 0);
			if (access("/tmp/ ", F_OK) != -1)
				unlink("/tmp/ ");
			if (error == 258)
				g_exit_status = 258;
			else if (WIFEXITED(wait_status))
				g_exit_status = WEXITSTATUS(wait_status);
		}
		//free (buf);
		//free_struct(cmd);
		//system("leaks minishell");
	}
	return (0);
}
