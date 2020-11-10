#include <stdio.h>
#include "libft/libft.h"

int	new(int *num)
{
	if (!*num)
		return (*num = 1);
	
}

int main()
{
	int fl = 0;
	new(&fl);
	printf("%d\n", fl);
}