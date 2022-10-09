/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saksoy <saksoy@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 03:58:56 by saksoy            #+#    #+#             */
/*   Updated: 2022/10/09 04:04:34 by saksoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_add_redirection(char *arg, char *type, t_redirection **redir, \
	int *check_redir)
{
	char	*ptr;
	char	*tmp;

	ptr = ft_calloc(sizeof(char) * ft_strlen(arg) + 1, sizeof(char));
	tmp = ft_str_clearquotes(arg, ptr);
	ft_lstadd_back_redir(redir, new_s_redirection(type, tmp));
	free(arg);
	*check_redir = 0;
}

char	*build_typer(char *str, int *index, int *check_redir)
{
	char	*tmp;

	if (*check_redir == 1)
		printf("SYNTAX ERROR redir çift redir falan\n");
	tmp = ft_substr(str, *index, is_redir(&(str[*index])));
	ft_memset(&str[*index], ' ', ft_strlen(tmp));
	*index += ft_strlen(tmp);
	*check_redir = 1;
	return (tmp);
}

char	*build_qouete_join(char *str, int *index)
{
	int		i;
	char	*tmp;
	char	*n_str;
	int		len;

	i = 0;
	len = 0;
	n_str = malloc(sizeof(char));
	*n_str = '\0';
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			len = parser_quote_endidx(&str[i + 1], str[i]);
			tmp = ft_substr(&str[i + 1], 0, len);
			n_str = ft_free_strjoin(n_str, tmp);
			i += len + 2;
			free(tmp);
		}
		else
			break ;
	}
	*index += i;
	return (n_str);
}

//leak
char	*build_qoete(char *str, int *index)
{
	char	*tmp;
	char	*n_str;
	char	quote;

	n_str = ft_calloc(1, sizeof(char));
	while (str[*index])
	{
		if (str[*index] == '"' || str[*index] == '\'')
		{
			quote = str[*index];
			tmp = build_qouete_join(&str[*index], index);
			n_str = ft_free_strjoin(n_str, tmp);
			n_str = ft_strappend(n_str, quote);
			free(tmp);
		}
		else if (str[*index] != ' ' && !is_redir(&str[*index]))
		{
			n_str = ft_free_strjoin(n_str, ft_substr(str, *index, 1));
			n_str = ft_strappend(n_str, '"');
			(*index)++;
		}
		else
			break ;
	}
	return (n_str);
}

char	*build_arger(char *str, int *index, int *check_redir)
{
	int		start_index;
	char	*tmp;

	start_index = *index;
	if (str[*index] == '"' || str[*index] == '\'')
	{
		tmp = build_qoete(str, index);
		ft_memset(&str[start_index], ' ', *index - start_index);
		(*index)--;
	}
	else
	{
		while (str[*index] && (str[*index] != ' ' && !is_redir(&str[*index])))
			(*index)++;
		tmp = ft_substr(str, start_index, *index - start_index);
		ft_memset(&str[start_index], ' ', ft_strlen(tmp));
		(*index)--;
	}
	*check_redir = 2;
	return (tmp);
}
