/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:02:03 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/01 03:32:32 by sfarhan          ###   ########.fr       */
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
		if (ft_strchr(line[0], "<>"))
		{
			if ((ft_strncmp(&line[i], ">>", 2) == 0) && (line[i + 1] != ' '))
			{
				str[j] = '>';
				str[j + 1] = '>';
				str[j + 2] = ' ';
				i += 2;
				j += 3;
			}
			else if ((ft_strncmp(&line[i], "<<", 2) == 0) && (line[i + 1] != ' '))
			{
				str[j] = '<';
				str[j + 1] = '<';
				str[j + 2] = ' ';
				i += 2;
				j += 3;		
			}
			else if ((ft_strncmp(&line[i], ">", 1) == 0) && (line[i + 1] != ' '))
			{
				str[j] = '>';
				str[j + 1] = ' ';
				i++;
				j += 2;
			}
			else if ((ft_strncmp(&line[i], "<", 1) == 0) && (line[i + 1] != ' '))
			{
				str[j] = '<';
				str[j + 1] = ' ';
				i++;
				j += 2;
			}
		}
		if (line[i] == 1)
		{
			str[j] = line[i];
			i++;
			j++;
			while (line[i] && !(line[i] == 1 && ft_strchr(line[i + 1], "|<>")))
			{
				str[j] = line[i];
				i++;
				j++;
			}
			if (line[i])
			{
				str[j] = line[i];
				i++;
				j++;
			}
		}
		if (line[i] == '|' && (line[i + 1] != ' ' || line[i - 1] != ' '))
		{
			str[j] = ' ';
			str[j + 1] = '|';
			str[j + 2] = ' ';
			i++;
			j += 3;
		}
		else if ((ft_strncmp(&line[i], ">>", 2) == 0) && (line[i + 1] != ' ' || line[i - 1] != ' '))
		{
			str[j] = ' ';
			str[j + 1] = '>';
			str[j + 2] = '>';
			str[j + 3] = ' ';
			i += 2;
			j += 4;
		}
		else if ((ft_strncmp(&line[i], "<<", 2) == 0) && (line[i + 1] != ' ' || line[i - 1] != ' '))
		{
			str[j] = ' ';
			str[j + 1] = '<';
			str[j + 2] = '<';
			str[j + 3] = ' ';
			i += 2;
			j += 4;		
		}
		else if ((ft_strncmp(&line[i], ">", 1) == 0) && (line[i + 1] != ' ' || line[i - 1] != ' '))
		{
			str[j] = ' ';
			str[j + 1] = '>';
			str[j + 2] = ' ';
			i++;
			j += 3;
		}
		else if ((ft_strncmp(&line[i], "<", 1) == 0) && (line[i + 1] != ' ' || line[i - 1] != ' '))
		{
			str[j] = ' ';
			str[j + 1] = '<';
			str[j + 2] = ' ';
			i++;
			j += 3;
		}
		str[j] = line[i];
		j++;
		i++;
	}
	str[j] = '\0';
	free (line);
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
		if (ft_strchr(line[0], "<>") == 1)
		{
			if ((ft_strncmp(&line[i], ">>", 2) == 0) && (line[i + 1] != ' '))
				count++;
			else if ((ft_strncmp(&line[i], "<<", 2) == 0) && (line[i + 1] != ' '))
				count++;
			else if ((ft_strncmp(&line[i], ">", 1) == 0) && (line[i + 1] != ' '))
				count++;
			else if ((ft_strncmp(&line[i], "<", 1) == 0) && (line[i + 1] != ' '))
				count++;
			i++;
		}
		if (line[i] == 1)
		{
			i++;
			while (line[i] && !(line[i] == 1 && ft_strchr(line[i + 1], "|<>")))
				i++;
			if (line[i])
				i++;
		}
		if (line[i] == '|' && (line[i + 1] != ' ' || line[i - 1] != ' '))
			count++;
		else if ((ft_strncmp(&line[i], ">>", 2) == 0) && (line[i + 1] != ' ' || line[i - 1] != ' '))
			count++;
		else if ((ft_strncmp(&line[i], "<<", 2) == 0) && (line[i + 1] != ' ' || line[i - 1] != ' '))
			count++;
		else if ((ft_strncmp(&line[i], ">", 1) == 0) && (line[i + 1] != ' ' || line[i - 1] != ' '))
			count++;
		else if ((ft_strncmp(&line[i], "<", 1) == 0) && (line[i + 1] != ' ' || line[i - 1] != ' '))
			count++;
		i++;
	}
	str = malloc(sizeof(char) * (size + (count * 2)));
	return (corrected(line, str));
}
