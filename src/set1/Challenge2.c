#include <stdio.h>
#include <stdlib.h>
#include "BytestreamUtilities.h"

// Challenge2.c contains a function that taken in two equal length hex strings and xors them together, returning their xor


int main(int argc, char *argv[]){
  if(argc != 3){
    printf("Usage: %s byte_stream_1 byte_stream_2\n",argv[0]);
    exit(1);
  }

  unsigned char *bytes1 = convert_hex_str_to_bytes(argv[1]);
  unsigned char *bytes2 = convert_hex_str_to_bytes(argv[2]);
  
  unsigned char *xorbytestream = xor_byte_streams(bytes1,bytes2);
  char *xorbytestreamhex = convert_bytes_to_hex_str(xorbytestream);
  
  printf("\nBytestream 1: %s\nBytestream 2: %s\nBytestream  : %s\n\n",argv[1],argv[2],xorbytestreamhex);
  
  free(bytes1);
  free(bytes2);
  free(xorbytestream);
  free(xorbytestreamhex);

  exit(0);
}

