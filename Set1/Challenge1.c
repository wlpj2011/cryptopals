#include <stdio.h>
#include <stdlib.h>
#include "BytestreamUtilities.h"

// Challenge1.c contains functions which can interconvert between null-terminated base64 strings and hexadecimal strings
// and bytes represented as a list of chars, where the 0th entry is the number of bytes present
// TODO: Fix memory issues where not all memory is cleaned up on a exit due to invalid input
// TODO: Do this by replacing exits with an returned invalid value and then handle cleanup?


int main(int argc, char *argv[]){
  // Challenge1.c is currently set up to read a hex str as a cmd line argument and print out 
  // that value again in hex and in base64.
  if(argc != 2){
    printf("Usage: %s hexinput",argv[0]);
    exit(1);
  }
  printf("\n");
  printf("The input was %s.\n",argv[1]);

  unsigned char *bytes = convert_hex_str_to_bytes(argv[1]);

  
  print_hex(bytes);
  printf("\n");
  print_base64(bytes);
  free(bytes);

  printf("\n\n");
  exit(0);
}

