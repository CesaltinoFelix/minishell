#include "minishell.h"

char	*ft_strndup(const char *s, size_t	len)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, (len + 1));
	return (ptr);
}