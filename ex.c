#include <stdio.h>
#include "libft/libft.h"



int main()
{
	char *str = "0-1";
	char *tmp = ft_strchr(str, '-');
	char *name_f = ft_strsub(str, 0, tmp - str);
	char *end = str;
	printf("%s\n", name_f);
	while (*end)
		end++;
	char *name_s = ft_strsub(str, tmp - str + 1, end - tmp);
	printf("%s\n", name_s);
}