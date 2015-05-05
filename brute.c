#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/md5.h>

void print_hash(unsigned char *hash) {
    for (int i = 0; i < 16; ++i) {
        printf("%02x", hash[i]);
    }
}

int inline check(unsigned char* digest) {
    if (digest[0] == 0xe) {
        for (int j = 1; j < 16; j++) {
            if ((unsigned char)(digest[j] >> 4) > 9 
                    || (unsigned char)(digest[j] & 0xf) > 9) {
                return 0;
            }
        }
    } else {
        return 0;
    }
    return 1;
}


int main(int argc, char **argv) {
    char low = 0x30;
    char high = 0x39;

    char digest[17];
    int cntr = 0;

    clock_t start = clock() / (CLOCKS_PER_SEC / 1000);

    if (argc != 2) {
        printf("Usage: %s prefix", argv[0]);
        return -1;
    }

    int length = strlen(argv[1]);
    char* data = calloc(1, length + 128);
    strcpy(data, argv[1]);

    printf("Input: %s\n", data);

    while(1) {
        char* cur = data + length;

        while(*cur == high) {
            *cur = low;
            cur++;
        }

        if (*cur == 0) {
            *cur = low;
        } else {
            *cur = *cur + 1;
        }

        MD5((unsigned char*)data, strlen((void *)data), (unsigned char*) digest);

        if (check((unsigned char*) digest)) {
            printf("\nFound hash after %d iterations! \nInput: \"%s\"\nHash: ", cntr, data);
            print_hash((unsigned char*) digest);
            break;
        }


        // output progress
        if (++cntr % (int)1e7 == 0) {
            clock_t end = clock() / (CLOCKS_PER_SEC / 1000);
            float mHashes = ((1e7 / (end - start)) / 1000);

            printf("[%d MHashes | %.02f MHashes/s] [ ", (int) (cntr / 1000000.0), mHashes);
            print_hash((unsigned char*) digest);
            printf(" ]\n");
            start = end;
        }
    }

    return 0;

}


