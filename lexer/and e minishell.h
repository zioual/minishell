/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:02 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/14 16:49:14 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	get_char_type(char c)
{
	if (c == '|')
		return (TOKEN_PIPE);
	else if (c == '\'')
		return (TOKEN_SINGLE_QUOTES);
	else if (c == '\"')
		return (TOKEN_DOUBLE_QUOTES);
	else if (c == '>')
		return (TOKEN_SINGLE_REDIR);
	else if (c == '<')
		return (TOKEN_SINGLE_REDIR);
	return (TOKEN);
}

t_list	*tokenize(const char *s)
{
	t_list	*list;
	int		i;
	int		j;
	char	*token;

	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	init_list(list);

	while (*s != '\0')
	{
		token = malloc(sizeof(char) * 100);	
		if (token == NULL) return (NULL);

		i = 0;
		if ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z') && (*s >= '0' && *s <= '9'))
		{
			while (*s && *s != ' ')
				token[i++] = *s++;
			token[i] = '\0';
			append(list, token, TOKEN);
		}
		else if (*s == '|')
		{
			token[i++] = *s;
			token[i] = '\0';
			append(list, token, TOKEN_PIPE);
		}
		else if (*s == '>' || *s == '<')
		{
			if (*(s+1) != '>' && *(s+1) != '<')
			{
				token[i++] = *s;
				token[i] = '\0';
				append(list, token, TOKEN_SINGLE_REDIR);
			}
			else if (*(s+1) == '>' || *(s+1) == '<')
			{
				token[i++] = *s;
				token[i++] = *s;
				token[i] = '\0';
				append(list, token, TOKEN_DOUBLE_REDIR);
				s++;
			}
		}
		else if (*s == '\'')
		{
			//s++;
			token[i++] = *s++;
			while (*s && *s != '\'')
				token[i++] = *s++;
			if (*s == '\'')
				token[i++] = *s;
			token[i] = '\0';
			append(list, token, TOKEN_SINGLE_QUOTES);
		}
		else if (*s == '\"')
		{
			token[i++] = *s++;
			while (*s && *s != '\"')
				token[i++] = *s++;
			token[i] = '\0';
			append(list, token, TOKEN_DOUBLE_QUOTES);
		}
		s++;
	}

	return (list);
}

int main(int ac, char **av)
{
    print_list(tokenize(av[1]));
    return 0;
}
