#include <stdio.h>
#include <stdlib.h>
#include "BytestreamUtilities.h"
#include "CheckDecryptUtilities.h"

// Challenge3.c contains a function that takes in a hex encoded string that has been
// encrypts by XORing with a single character, and returns that most likely character
// for it to have been XORed with and the result decrypt


int main(int argc, char *argv[]){
  if(argc != 2){
    printf("Usage: %s byte_stream\n",argv[0]);
    exit(1);
  }

  unsigned char *bytes1 = convert_hex_str_to_bytes(argv[1]);
  
  
  free(bytes1);

  exit(0);
}

