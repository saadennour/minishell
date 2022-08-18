/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:10:50 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/17 16:34:11 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	deletenode(t_list **head, char *name)
{
	t_list	*temp;
	t_list	*current;

	if (strcmp((*head)->name, name) == 0)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			if (strcmp(current->next->name, name) == 0)
			{
				temp = current->next;
				current->next = current->next->next;
				free(temp);
				break ;
			}
			else
				current = current->next;
		}
	}
}

int	ft_unset(char **cmd, t_list **data)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		deletenode(data, cmd[i]);
		i++;
	}	
	return (2);
}
