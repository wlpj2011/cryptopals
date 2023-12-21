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
  print_hex(bytes1);
  
  int length = bytes1[0];
  for(int i = 0; i < 256; i++){
    unsigned char *testkey = malloc(sizeof(unsigned char) * (length + 1));
    testkey[0] = length;
    for(int j = 0; j < length; j++){
      testkey[j+1] = i;
    }
    unsigned char *testdecrypt = xor_byte_streams(bytes1,testkey);
    if(byte_stream_is_ascii(testdecrypt)){
      printf("The key %02x gives the decrypt ",i);
      print_ascii(testdecrypt);
    }
    if(i == 0x5f){
      float value = byte_stream_compare_character_distribution(testdecrypt);
    }
    free(testkey);
    free(testdecrypt);
  }
  
  free(bytes1);

  exit(0);
}

