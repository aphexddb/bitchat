#include <stdio.h>
#include <sodium.h>

int main(void) {
    if (sodium_init() < 0) {
        fprintf(stderr, "libsodium initialization failed\n");
        return 1;
    }
    printf("Hello, world!\n");
    return 0;
}
