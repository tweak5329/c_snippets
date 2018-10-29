#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/* Several ways to test a machine's endianness... */

int main(int argc, char *argv[]) {

    // print the value from memory and see for yourself
    uint32_t n = 0x01234567;
    printf("Reading 0x01234567 from memory... ");
    uint8_t *p = (uint8_t *) &n;
    for (uint8_t i = 0; i < 4; i++)
	printf("%.2x ", (uint32_t) *(p+i));
    printf("\n");

    uint32_t i = 1;                // i = 0x00000001
    uint8_t *c = (uint8_t *) &i;   // keep only first stored byte:
    if (*c)                        // - 0x0001 was stored first
	printf("Little endian\n"); //   => little endian
    else                           // - 0x0000 was stored first
	printf("Big endian\n");    //   => big endian

    return EXIT_SUCCESS;
}
