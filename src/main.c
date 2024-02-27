#include "minishell.h"

int main(void)
{
	char *input;
	while(1)
	{
		input = readline(COLOR_PINK "MINI_SHELL:" COLOR_RESET " ");
		add_history(input);
		if(!input)
			exit(0);
		if(input[0] == '\0')
			continue;
		printf("your message: %s \n", input);
	}
	free(input);
}
