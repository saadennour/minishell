/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:02:03 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/03 20:59:44 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
}

static char	*corrected(char *line, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '|' && (line[i + 1] != ' ' || line[i - 1] != ' '))
		{
			str[j] = ' ';
			str[j + 1] = '|';
			str[j + 2] = ' ';
			i++;
			j += 3;
		}
		str[j] = line[i];
		j++;
		i++;
	}
	return (str);
}

char	*ft_path(char *line)
{
	int		i;
	int		size;
	int		count;
	char	*str;
	
	i = 0;
	count = 0;
	size = ft_strlen(line);
	while (line[i])
	{
		if (line[i] == '|' && (line[i + 1] != ' ' || line[i - 1] != ' '))
			count++;
		i++;
	}
	str = malloc(sizeof(char) * (size + (count * 2)));
	return (corrected(line, str));
}

// char	**get_path(char *env)
// {
// 	int		i;
// 	char	**path;
// 	// char	**equal;

// 	// i = search_path(env);
// 	// equal = ft_split(env, '=', &i);
// 	path = ft_split(env, ':', &i);
// 	// printf("%s\n",path[0]);
// 	// free_tab(equal);
// 	return (path);
// }

// int		lets_check(char *str)
// {
// 	int  i;
// 	char **cmd_op;
// 	char **path;
// 	char *env;
// 	char  *cmd_path;
	
// 	i = 0;
// 	env = NULL;
// 	env = getenv("PATH");
// 	cmd_op = ft_split(str, ' ', &i);
// 	if (access(str, F_OK) == 0)
// 		execve(cmd_op[0], cmd_op, &env);
// 	path = get_path(env);
// 	// 	printf("hey\n");
// 	// printf("%s\n",path[0]);
// 	i = 0;
// 	while (path[i])
// 	{
// 		// printf("%s\n",path[i]);
// 		cmd_path = ft_strjoin(path[i], "/");
// 		cmd_path = ft_strjoin(cmd_path, cmd_op[0]);
// 		printf("%s\n",cmd_path);
// 		if (access(cmd_path, F_OK) == 0)
// 			execve(cmd_path, cmd_op, &env);
// 		free(cmd_path);
// 		i++;
// 	}
// 	return (0);
// }