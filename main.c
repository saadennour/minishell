/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:01:53 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/18 18:35:38 by sfarhan          ###   ########.fr       */
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
		printf ("Quit: 3\n");
		g_exit_status = 131;
		exit (131);
	}
}

static void	init_tools(t_tool *tools, char **envp)
{
	tools->fd = 0;
	tools->envp = envp;
	tools->limiter = NULL;
	tools->in = 0;
	tools->out = 0;
	tools->free = 25;
	tools->stdin_copy = dup(STDIN_FILENO);
	tools->stdout_copy = dup(STDOUT_FILENO);
	tools->path = getcwd(NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	int		wait_status;
	char	*buf;
	t_list	*data;
	t_tool	tools;
	t_cmd	*cmd;
	pid_t	pid;

	data = NULL;
	(void) ac;
	(void) av;
	init_tools(&tools, envp);
	ft_envp(envp, &data);
	while (1)
	{
		signal (SIGINT, handle_c);
		signal (SIGQUIT, SIG_IGN);
		buf = readline("-> minishell ");
		if (buf == NULL)
		{
			printf ("exit\n");
			exit(0);
		}
		add_history(buf);
		//printf ("p => %p\n", buf);
		cmd = parsecmd(buf, &data);
		//while (1);
		if (ifexit(cmd) || ifenv(cmd, &data, &tools.path))
			continue ;
		else
		{
			pid = fork();
			if (pid == 0)
			{
				signal (SIGINT, SIG_DFL);
				signal (SIGQUIT, SIG_DFL);
				run_cmd(cmd, &tools, &data);
			}
			signal(SIGINT, SIG_IGN);
			waitpid(pid, &wait_status, 0);
			g_exit_status = WEXITSTATUS(wait_status);
			if (WIFSIGNALED(wait_status))
				g_exit_status = WTERMSIG(wait_status) + 128;
			signal(SIGINT, handle_c);
			if (access("/tmp/ ", F_OK) != -1)
				unlink("/tmp/ ");
		}
		free (buf);
		free_struct(cmd);
		//system("leaks minishell");
	}
	return (0);
}
