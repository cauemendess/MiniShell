#include "minishell.h"

char	*replace_occurrence(char *result, char *ptr, char *old, char *new)
{
	size_t	len;
	char	*subtemp;
	char	*tmp;

	len = ptr - result;
	subtemp = ft_substr(result, 0, len);
	tmp = ft_strjoin(subtemp, new);
	free(subtemp);
	subtemp = ft_strjoin(tmp, ptr + ft_strlen(old));
	free(result);
	free(tmp);
	return (subtemp);
}

char	*ft_replace(char *str, char *old, char *new)
{
	char	*result;
	char	*ptr;
	int		i;

	i = 0;
	if (ft_strlen(old) == 0)
		return (ft_strdup(str));
	result = ft_strdup(str);
	ptr = result;
	while (*ptr)
	{
		ptr = ft_strstr(ptr, old);
		if (!ptr)
			break ;
		i = ptr - result;
		result = replace_occurrence(result, ptr, old, new);
		ptr = result + ft_strlen(new) + i;
	}
	free(str);
	return (result);
}


char *my_get_env(char *key)
{
	t_env *env;
	env = get_core()->env_list;
	if(!key)
		return(NULL);
	while(env)
	{
		if(!ft_strncmp(env->key, key, ft_strlen(key)))
			return(ft_strdup(env->value));
		if(!ft_strncmp(key, "?", 2))
			return(ft_itoa(get_core()->exit_status));
		if(!ft_strncmp(key, "$", 3))
			return(ft_strdup("$"));

		env = env->next;
	}
	return(ft_strdup(""));
}

//void	expansion_domain()
//{

//}


//void	split_token(t_token *token)
//{

//}

t_bool have_dollar(char *str, int *status)
{
	int i = 0;
	while(str[i])
	{
		status = ft_quotes_status(str[i], status);
		if(str[i] == '$' && status == 0)
			return(TRUE);
		i++;
	}
	return (FALSE);

}



void	parsing_vars(void)
{
	t_token *cur;
	static int status;
	cur = get_core()->token;
	char *res;
	while (cur)
	{
		if(cur->token == WORD)
		{
			if(have_dollar(cur->str, &status))
			{
				res = my_get_env(cur->str + 1);
				free(cur->str);
				cur->str = res;
				cur->token = VAR;
			}
		}
		cur = cur->next; 	
	}
}
