/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemirta <gdemirta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:35:37 by gdemirta          #+#    #+#             */
/*   Updated: 2022/10/09 18:22:06 by gdemirta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_add_redirection(char *arg, char *type, t_redirection **redir,\
	int *check_redir)
{
	char	*ptr;
	char	*tmp;

	ptr = ft_calloc(sizeof(char) * (ft_strlen(arg) + 1),sizeof(char));
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

//tmp = ft_substr(str, *index, 
//ft_get_chrindex(&str[*index + 1], str[*index]) + 2);
char	*build_arger(char *str, int *index, int *check_redir)
{
	int		start_index;
	char	*tmp;

	start_index = *index;
	if (str[*index] == '"' || str[*index] == '\'')
	{
		tmp = build_quote(str, index);
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
	if (*tmp == '\0')
		return NULL;
	else
		*check_redir = 2;
	return (tmp);
}

//type'ın tırkan içinde olma durumu
//type = NULL;
//arg = NULL;

int 	check_arger(char **cmd, int idx)
{
	if (is_redir(&cmd[0][idx]))
	{
		g_data.syntax_err = 1;
		return 0;
	}
	else if (cmd[0][idx] != ' ')
		return 1;
	return  0;
}

void	build_redirection(t_redirection **redir, char	**cmd)
{
	int		check_redir;
	char	*type;
	char	*arg;
	int		idx;

	idx = -1;
	check_redir = 0;
	g_data.syntax_err = 0;
	while (++idx < (int)ft_strlen(cmd[0]))
	{
		if (check_redir == 0 && (cmd[0][idx] == '"' || cmd[0][idx] == '\''))
			idx += ft_strchr(&(cmd[0][idx + 1]), cmd[0][idx]) - &(cmd[0][idx]);
		if (is_redir(&(cmd[0][idx])))
			type = build_typer(cmd[0], &idx, &check_redir);
		if (check_redir == 1 && check_arger(cmd, idx))
			arg = build_arger(cmd[0], &idx, &check_redir);
		if (check_redir == 2)
		{
			build_add_redirection(arg, type, redir, &check_redir);
			type = NULL;
			arg = NULL;
		}
	}
	if (check_redir == 1)
	{
		g_data.syntax_err = 1;
		printf("------------\nsyntaxerror\n--------\n");
	}
	if (!*redir)
		*redir = NULL;
}