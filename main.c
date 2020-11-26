#include "includes/string_utils.h"

int main(int ac, char **av)
{
	int i;

	i = 0;
	
	init_string();
	while(ac > 1)
	{
		string_append_line(av[ac - 1]);
		ac--;
	}
	print_string();
	return 0;
}