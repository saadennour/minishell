#include "minishell.h"

int	ft_echo(char *buf)
{
	buf = buf + 4;
	while (buf != '\0' && ft_strchr(*buf, " \t\n\f\v\r"))
		buf++;
	if(*buf == '$')
	{
		printf("hey\n");
		return (0);
	}

	if(ft_strncmp(buf,"-n ",3) == 0)
	{
		buf = buf + 2;
		while (buf != '\0' && ft_strchr(*buf, " \t\n\f\v\r"))
			buf++;
		printf("%s",buf);
		return (0);
	}
	else
	{
		printf("%s\n",buf);
		return (0);
	}
	return (1);
}

int if_builtins(char *buf)
{
	if(ft_strncmp(buf,"cd ",3) == 0)
	{
		if(chdir(buf + 3) < 0)
			printf("cd: no such file or directory: %s\n",buf + 3);
		return (0);
	}
	else if(strcmp(buf,"pwd") == 0 )
	{
		char *cwd;
	
		cwd = malloc(sizeof(char) * 100);
		getcwd(cwd, 100);
		printf("pwd=%s\n",cwd);
		return (0);
	}
	else if(strcmp(buf,"exit") == 0)
	{
		printf("exit\n");
		exit (0);
	}
	else if(ft_strncmp(buf, "echo ",5) == 0)
		if(ft_echo(buf) == 0)
			return (0);
	return (1);
}
