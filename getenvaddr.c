#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {

    if (argc != 2 && argc != 3) {
	printf("Usage: %s <var_name> [<path_to_prog>]\n", argv[0]);
	printf("ex: %s SHELL /tmp/test\n", argv[0]);
	exit(EXIT_SUCCESS);
    }

    char *p = NULL;
    p = getenv(argv[1]);
    if (p == NULL) {
	printf("Couldn't find variable %s in environment\n", argv[1]);
	exit(EXIT_FAILURE);
    }

    if (argc == 3) {
	p += (strlen(argv[0]) - strlen(argv[2])) * 2;
    }

    printf("%s will be at %p\n", argv[1], p);

    return EXIT_SUCCESS;
}
