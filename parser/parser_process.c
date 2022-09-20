#include "minishell.h"

char **parser_redirect(char **str)
{
	static char	*arr[5] = {">>", "<<", ">", "<", 0};
	char	**ret;

	if (!str)
		return (NULL);
	ret = malloc(sizeof(char **) * parse_non_redir_word_count(str, arr) + 1);
	if(ret == NULL)
		return NULL;
	if(parser_check_valid_syntax(str,arr)== -1)
	{
		free(ret);
		return NULL;
	}
	parser_redirect_split(str,&ret,arr);
	return (ret);
}

char **parser_process(char *str)
{
	char **ret;
	char **tmp;

	if(!ft_strlen(str))
		return NULL;
	tmp = malloc(sizeof(char**));
	ret = malloc(sizeof(char**));
	*tmp = ft_strtrim(str, " ");
	if(*tmp == NULL)
		return ft_double_free(tmp, 1);
	*ret = ft_str_clearspace(*tmp);
	if(*ret == NULL)
		return ft_double_free(tmp, 1);
	ft_double_free(tmp,1);
	tmp = parser_cmd_split(*ret, '|');
	if(tmp == NULL)
		return ft_double_free(ret, 1);
	ft_double_free(ret, 1);
	ret = parser_array_trim(tmp);
	if(ret == NULL)
		return ft_double_free(tmp, parser_array_getsize(tmp));
	ft_double_free(tmp, parser_array_getsize(tmp));
	//ret = parser_redirect(ret);
	//ft_double_free(tmp, parser_array_getsize(tmp));
	return (ret);
}