#include "base64.h"
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
    const char *text = "Hello, World!";
    
    size_t encoded_len;
    char *encoded = base64_encode((const unsigned char *)text, strlen(text), &encoded_len);

    printf("Encoded: %s\n", encoded);

    size_t decoded_len;
    unsigned char *decoded = base64_decode(encoded, encoded_len, &decoded_len);

    printf("Decoded: %.*s\n", (int)decoded_len, decoded);

    free(encoded);
    free(decoded);
    return 0;
}
