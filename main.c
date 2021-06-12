#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int ac, char **av)
 {
	int id;
	id = fork();

	printf("Hello, World! from id : %d\n", id);
	return 0;
}
