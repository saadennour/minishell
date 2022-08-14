/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:44:37 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/13 13:15:38 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	double_quotes(char *str, int *i)
{
	str[(*i)] = 1;
	while (str[(*i)] && str[(*i)] != 34)
		(*i)++;
	if (str[(*i)] == '\0')
	{
		printf ("minishell: quotation error\n");
		exit (1);
	}
	str[(*i)] = 1;
	return (1);
}

static int	single_quotes(char *str, int *i)
{
	str[(*i)] = 1;
	while (str[(*i)] && str[(*i)] != 39)
		(*i)++;
	if (str[(*i)] == '\0')
	{
		printf ("minishell: quotation error\n");
		exit (1);
	}
	str[(*i)] = 1;
	return (2);
}

char	*quotes(char *str, t_quote *quote)
{
	int		i;
	int		x;
	int		tmp;

	i = 0;
	x = 0;
	while (str[i])
	{
		tmp = i;
		if (str[i] == 34)
			quote->quote[x] = double_quotes(str, &i);
		else if (str[i] == 39)
			quote->quote[x] = single_quotes(str, &i);
		i++;
		if (str[i] == ' ' || str[i] == 34 || str[i] == 39 || str[i] == '$')
		{
			if (tmp + 2 == i)
				x--;
			x++;
			quote->quote[x] = 1;
			if (str[i] == ' ')
				i++;
		}
	}
	return (str);
}

static int	quotes_count(char *str, int i, int *len)
{
	if (str[i] == 34)
	{
		i++;
		while (str[i] && str[i] != 34)
			i++;
		if (str[i])
			i++;
		(*len)++;
	}
	else if (str[i] == 39)
	{
		i++;
		while (str[i] && str[i] != 39)
			i++;
		if (str[i])
			i++;
		(*len)++;
	}
	return (i);
}

int	num_quotes(char *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		i = quotes_count(str, i, &len);
		while (str[i] == c)
			i++;
		if (str[i] && str[i] != c && str[i] != 39 && str[i] != 34)
		{
			while (str[i] && str[i] != c)
				i++;
			len++;
		}
	}
	return (len);
}
