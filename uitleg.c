#include <stdlib.h>
#include <stdio.h>



void	count_and_print()
{
	static int count = 0;
	printf("%i\n", count);
	count++;
}



int main(int argc, char const *argv[])
{
	size_t	i = 0;
	while (i <= 100)
	{
		count_and_print();	/* code */
		i++;
	}
	return 0;
}
