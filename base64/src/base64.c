#include "base64.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                   "abcdefghijklmnopqrstuvwxyz"
                                   "0123456789+/";

static unsigned char decoding_table[256];
static int table_built = 0;
static void build_decoding_table() {
  if (table_built) {
    return;
  }

  for (int i = 0; i < 64; i++) {
    decoding_table[(unsigned char)base64_table[i]] = i;
  }
  table_built = 1;
}

static int is_base64_char(char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
         (c >= '0' && c <= '9') || (c == '+') || (c == '/');
}

static int calc_padding(const char *data, size_t len) {
  if (len < 2) {
    return 0;
  }

  if (data[len - 1] == '=' && data[len - 2] == '=') {
    return 2;
  } else if (data[len - 1] == '=') {
    return 1;
  } else {
    return 0;
  }
}

char *base64_encode(const unsigned char *data, size_t input_length,
                    size_t *output_length) {
  *output_length = 4 * (input_length + 2) / 3;
  char *encoded = malloc(*output_length + 1);
  if (!encoded) {
    return NULL;
  }

  for (size_t i = 0, j = 0; i < input_length;) {
    unsigned int octet_a = i < input_length ? data[i++] : 0;
    unsigned int octet_b = i < input_length ? data[i++] : 0;
    unsigned int octet_c = i < input_length ? data[i++] : 0;

    unsigned int triple = 
      (octet_a << 16) | 
      (octet_b << 8) | 
      octet_c;

    encoded[j++] = base64_table[(triple >> 18) & 0x3F];
    encoded[j++] = base64_table[(triple >> 12) & 0x3F];
    encoded[j++] = base64_table[(triple >> 6) & 0x3F];
    encoded[j++] = base64_table[triple & 0x3F];
  }

  int mod = input_length % 3;
  if (mod) {
    encoded[*output_length - 1] = '=';
    if (mod == 1) {
      encoded[*output_length - 2] = '=';
    }
  }

  encoded[*output_length] = '\0';
  return encoded;
}

unsigned char *base64_decode(const unsigned char *data, size_t input_length, size_t *output_length) {
  if (input_length % 4 != 0) {
    return NULL;
  }

  build_decoding_table();

  int padding = calc_padding(data, input_length);
  *output_length = (input_length / 4) * 3 - padding;

  unsigned char *decoded = malloc(*output_length);
  if (!decoded) {
    return NULL;
  }

  for (size_t i = 0, j = 0; i < input_length;) {
    unsigned int sextet_a = data[i] == '=' ? 0 : decoding_table[(unsigned char)data[i]];i++;
    unsigned int sextet_b = data[i] == '=' ? 0 : decoding_table[(unsigned char)data[i]];i++;
    unsigned int sextet_c = data[i] == '=' ? 0 : decoding_table[(unsigned char)data[i]];i++;
    unsigned int sextet_d = data[i] == '=' ? 0 : decoding_table[(unsigned char)data[i]];i++;

    unsigned int triple = 
      (sextet_a << 18) |
      (sextet_b << 12) |
      (sextet_c << 6) |
      sextet_d;

    if (expression) {
    
    }
  }
}

int base64_encode_file(const char *filename) {}

int base64_decode_file(const char *filename) {}