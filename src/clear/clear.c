#include "minishell.h"

void	clear_tkn_lst(t_token **token)
{
	t_token	*temp;
	char	*temp_str;
	if (token != NULL)
	{
		while (*token)
		{
			temp_str = (*token)->str;
			temp = *token;
			*token = (*token)->next;
			free(temp_str);
			free(temp);
		}
		*token = NULL;
	}
}
void	ft_free_matrice(char **matrice)
{
	int	i;

	i = 0;
	while (matrice[i])
	{
		free(matrice[i]);
		i++;
	}
	free(matrice);
}

void	garbage_collect(void *ptr)
{
	t_list *gc;
	gc = malloc(sizeof(t_list));
	if(!gc)
		return ;
	gc->content = ptr;
	gc->next = get_core()->garbage;
	get_core()->garbage = gc;
	
}


void	clear_garbage(void)
{
	t_list *garbage;
	t_list *next;
	garbage = get_core()->garbage;
	while(garbage)
	{
		next = garbage->next;
		if(garbage->content != NULL)
			free(garbage->content);
		if(garbage != NULL)
			free(garbage);
		garbage = next;
	}
	get_core()->garbage = NULL; 
}

