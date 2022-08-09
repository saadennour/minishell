/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:44:37 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/09 14:56:35 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	sign_pos(char *str)
// {
// 	static int	j;
// 	char		quote;
// 	int			sign;

// 	sign = 0;
// 	while (str[j])
// 	{
// 		if (str[j] == 34 || str[j] == 39)
// 		{
// 			quote = str[j];
// 			j++;
// 			while (str[j] && str[j] != quote)
// 			{
// 				if (str[j] == '$')
// 					sign = j;
// 				j++;
// 			}
// 			if (str[j])
// 				j++;
// 			break ;
// 		}
// 		else
// 		{
// 			if (str[j] == '$')
// 			{
// 				sign = j;
// 				break ;
// 			}
// 		}
// 		j++;
// 	}
// 	return (sign);
// }

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

	i = 0;
	x = 0;
	while (str[i])
	{
		if (str[i] == 34)
			quote->quote[x] = double_quotes(str, &i);
		else if (str[i] == 39)
			quote->quote[x] = single_quotes(str, &i);
		i++;
		if (str[i] == ' ' || str[i] == 34 || str[i] == 39)
		{
			x++;
			if (str[i] == ' ')
				i++;
		}
	}
	return (str);
}
