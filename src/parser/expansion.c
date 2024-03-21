#include "minishell.h"

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
		if(!ft_strncmp(env->key, "$?", 3))
			return(ft_itoa(get_core()->exit_status));
		if(!ft_strncmp(env->key, "$$", 3))
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

t_bool have_dollar(char *str)
{
	int i = 0;

	while(str[i])
	{
		if(str[i] == '$')
			return(TRUE);
		i++;
	}
	return(FALSE);

}



void	parsing_vars(void)
{
	t_token *cur;
	cur = get_core()->token;
	char *res;
	while (cur)
	{
		if(cur->token == WORD)
		{
			//if(have_dollar(cur->str))
			if(cur->str[0] == '$')
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
