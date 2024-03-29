/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:50:59 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/27 02:51:34 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	new->next = NULL;
	if (!(*alst))
		*alst = new;
	else
		(ft_lstlast(*alst))->next = new;
}

t_list	*ft_lstnew(void *name, void *value, void *sep)
{
	t_list	*new;

	new = (t_list *) malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->name = name;
	new->value = value;
	new->sep = sep;
	new->next = NULL;
	return (new);
}

int	printenvp(char	**inpt, t_list **data)
{
	t_list	*tmp;

	if (inpt[1])
	{
		printf("env: %s: NO such file or directory\n", inpt[1]);
		return (127);
	}
	tmp = *data;
	while (tmp)
	{
		if (tmp->sep)
			printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (2);
}

void	ft_envp(char **envp, t_list	**data)
{
	int		i;
	int		j;
	char	**op;

	i = 0;
	while (envp[i])
	{
		j = 1;
		op = ft_splito(envp[i], '=');
		if (!ft_strcmp(op[0], "OLDPWD"))
			ft_lstadd_back(data, ft_lstnew(op[0], NULL, NULL));
		else
		{
			j = 2;
			ft_lstadd_back(data, ft_lstnew(op[0], op[1], "="));
		}
		i++;
		free_tab (op, j);
	}
	return ;
}
