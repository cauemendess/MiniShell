#include "minishell.h"

t_core	*get_core(void)
{
	static t_core	core;

	return (&core);
}
t_bool	simple_error(void)
{
	char	*temp;
	int		i;

	i = 0;
	temp = ft_strtrim(get_core()->input, " ");
	if (temp[0] == '|')
	{
		ft_putendl_fd("bash: syntax error near unexpected token `newline'", 2);
		free(temp);
		return (TRUE);
	}
	while (temp[i])
		i++;
	if (temp[i - 1] == '<' || temp[i - 1] == '>' || temp[i - 1] == '|')
	{
		ft_putendl_fd("bash: syntax error near unexpected token `newline'", 2);
		free(temp);

		return (TRUE);
	}
	free(temp);
	return (FALSE);
}


void	ft_translate_type(int type, int i)
{
	printf("| Type [%d]:", i);
	if (type == 1)
		printf("SPACES \n");
	else if (type == 2)
		printf("VAR \n");
	else if (type == 3)
		printf("WORD \n");
	else if (type == 4)
		printf("PIPE \n");
	else if (type == 5)
		printf("INPUT \n");
	else if (type == 6)
		printf("TRUNC \n");
	else if (type == 7)
		printf("APPEND \n");
	else if (type == 8)
		printf("HEREDOC \n");
}

void	ft_print_stack(void)
{
	int	i;
	t_token *stack;
	stack = get_core()->token;
	i = 0;
	printf("%p\n", stack);
	while (stack)
	{
		printf("-----------------------------\n");
		printf("| Token[%d]:%s.\n", i, stack->command);
		ft_translate_type(stack->token, i);
		printf("| Stack[%d]:%p\n", i, stack);
		printf("| Next [%d]:%p\n", i, stack->next);
		printf("| Prev [%d]:%p\n", i, stack->prev);
		printf("-----------------------------\n");
		i++;
		stack = stack->next;
	}
}



t_token	*create_tkn_lst(char *command, int type)
{
	t_token *node;
	node = ft_calloc(sizeof(t_token), 1);
	if(!node)
		printf("ERRADO!\n");
	node->command = ft_strdup(command);
	node->token = type;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_token(t_token **token, char *command, int type)
{
	t_token *cur;

	if(!*token)
	{
		cur = create_tkn_lst(command, type);
		return ;
	}
	cur = *token;
	while(cur->next)
		cur = cur->next;
	cur->next = create_tkn_lst(command, type);
	cur->next->prev = cur;
	ft_print_stack();

}

void	save_words(char *input, int start, int end)
{
	t_core *core;
	core = get_core();
	char *str;
	str = malloc(start - end * sizeof(char));
	ft_memmove(str, input + start, start - end);
	add_token(&core->token, str, WORD);
	free(str);

}

void	save_separator(char *input, int pos, int type)
{
	char *str;

	t_core *core;
	core = get_core();
	if(type == APPEND || type == HEREDOC)
	{
		str = malloc(3 * sizeof(char));
		ft_memmove(str, input + pos, 2);
		add_token(&core->token, str, type);
		free(str);
	}
	else
	{
		str = malloc(2 * sizeof(char));
		ft_memmove(str, input + pos, 1);
		add_token(&core->token, str, type);
		free(str);
	}
}


int	check_token(char *str)
{
	if(!ft_strncmp(str, ">>", 2))
		return(APPEND);
	else if(!ft_strncmp(str, "<<", 2))
		return(HEREDOC);
	else if(!ft_strncmp(str, ">", 1))
		return (REDIRECT);
	else if(!ft_strncmp(str, "<", 1))
		return(TRUNC);
	else if(!ft_strncmp(str, "|", 1))
		return(PIPE);
	else if(!ft_strncmp(str, " ", 1))
		return(SPACES);
	else
		return(0);
	
}

void	lexing(char *input)
{
	int	type;
	int start;
	size_t i;
	start = 0;
	i = -1;
	while (++i < ft_strlen(input) + 1)
	{
		type = check_token(&input[i]);
		if(type)
		{
			if(type != VAR && type != SPACES)
			{
				save_separator(input, i, type);
				if(type == HEREDOC || type == APPEND)
					i++;
			}
			if(!check_token(&input[i - 1]) && i != 0)
				save_words(input, start, i);
		}
		start = i + 1;
	}
}

void	process(void)
{
	t_core *this;
	this = get_core();
	if (simple_error())
		return ;
	//if(!check_quotes())
	//	return ;
	lexing(this->input);
}

void	readlines(void)
{
	t_core	*core;

	core = get_core();
	while (1)
	{
		core->input = readline(COLOR_PINK "MINI_SHELL:" COLOR_RESET " ");
		process();
		add_history(core->input);
		if (!core->input)
			exit(0);
		if (core->input[0] == '\0')
			continue ;
	}
}

int	main(void)
{
	t_core	*core;

	core = get_core();
	readlines();
	free(core->input);
}
