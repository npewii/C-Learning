#include "base64.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_usage() {
  printf("Usage:\n");
  printf("  base64 -e <text>        Encode string\n");
  printf("  base64 -d <text>        Decode string\n");
  printf("  base64 -e -f <file>     Encode file\n");
  printf("  base64 -d -f <file>     Decode file\n");
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    print_usage();
    return 1;
  }

  bool encode_mode = false;
  bool decode_mode = false;
  bool file_mode = false;
  char *input = NULL;

  for (int i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "-e")) {
      encode_mode = true;
    } else if (!strcmp(argv[i], "-d")) {
      decode_mode = true;
    } else if (!strcmp(argv[i], "-f")) {
      file_mode = true;
      if (i + 1 < argc) {
        input = argv[++i];
      } else {
        fprintf(stderr, "Error: Missing filename after -f\n");
        return 1;
      }
    } else {
      input = argv[i];
    }
  }

  if (encode_mode == decode_mode) {
    fprintf(stderr, "Error: Must specify either -e or -d\n");
    return 1;
  }

  if (!input) {
    fprintf(stderr, "Error: No input provided\n");
    return 1;
  }

  if (!file_mode) {
    if (encode_mode) {
      size_t output_len;
      char *encoded =
          base64_encode((unsigned char *)input, strlen(input), &output_len);
      if (!encoded) {
        fprintf(stderr, "Error: Encode failed\n");
        return 1;
      }

      printf("%s\n", encoded);
      free(encoded);
    } else {
      size_t output_len;
      unsigned char *decoded =
          base64_decode((unsigned char *)input, strlen(input), &output_len);
      if (!decoded) {
        fprintf(stderr, "Error: Invalid base64 input\n");
        return 1;
      }

      printf("%.*s\n", (int)output_len, decoded);
      free(decoded);
    }
  } else {
    if (encode_mode) {
      return base64_encode_file(input);
    } else {
      return base64_decode_file(input);
    }
  }

  return 0;
}
