/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redirection2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saksoy <saksoy@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 04:03:14 by saksoy            #+#    #+#             */
/*   Updated: 2022/10/09 04:03:37 by saksoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_types.h"

void	build_redirection(t_redirection **redir, char	**cmd)
{
	int		check_redir;
	char	*type;
	char	*arg;
	int		idx;

	idx = -1;
	check_redir = 0;
	while (++idx < (int)ft_strlen(cmd[0]))
	{
		if (check_redir == 0 && (cmd[0][idx] == '"' || cmd[0][idx] == '\''))
			idx += ft_strchr(&(cmd[0][idx + 1]), cmd[0][idx]) - &(cmd[0][idx]);
		if (is_redir(&(cmd[0][idx])))
			type = build_typer(cmd[0], &idx, &check_redir);
		if (check_redir == 1 && cmd[0][idx] != ' ' && !is_redir(&cmd[0][idx]))
			arg = build_arger(cmd[0], &idx, &check_redir);
		if (check_redir == 2)
		{
			build_add_redirection(arg, type, redir, &check_redir);
			type = NULL;
			arg = NULL;
		}
	}
	if (!*redir)
		*redir = NULL;
}
