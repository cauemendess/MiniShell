#include "minishell.h"

int    ft_quotes_status(char c, int status)
{
    if (c == '\'' && status == 0)
        status = 2;
    else if (c == '\'' && status == 2)
        status = 0;
    else if (c == '"' && status == 0)
        status = 1;
    else if (c == '"' && status == 1)
        status = 0;
    return (status);
}
