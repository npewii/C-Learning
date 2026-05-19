#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>
char* base64_encode(const unsigned char *data, size_t input_length, size_t *output_length);
unsigned char* base64_decode(const unsigned char *data, size_t input_length, size_t *output_length);

int base64_encode_file(const char *filename);
int base64_decode_file(const char *filename);

#endif