#include <stdio.h>
#include <stdlib.h>
#include "BytestreamUtilities.h"
#include "CheckDecryptUtilities.h"

// Challenge4.c contains a function that takes in a file with multiple hex encoded strings that have been
// encrypted and detects which ones have been encrypted using a single-character XOR
// It then decrypts and prints those strings


int main(int argc, char *argv[]){
  if(argc != 2){
    printf("Usage: %s file_of_byte_streams.txt\n",argv[0]);
    exit(1);
  }

  unsigned char *bytes1 = convert_hex_str_to_bytes(argv[1]);
  //print_hex(bytes1);

  /*
  int length = bytes1[0];
  float minimum_decrypt_score = 27.0;
  int minimum_decrypt_key = 0x00;
  for(int i = 0; i < 256; i++){
    unsigned char *testkey = malloc(sizeof(unsigned char) * (length + 1));
    testkey[0] = length;
    for(int j = 0; j < length; j++){
      testkey[j+1] = i;
    }
    unsigned char *testdecrypt = xor_byte_streams(bytes1,testkey);
    if(byte_stream_is_ascii(testdecrypt)){
      //printf("The key %02x gives the decrypt ",i);
      //print_ascii(testdecrypt);
      float value = byte_stream_compare_character_distribution(testdecrypt);
      if(value < minimum_decrypt_score){
	minimum_decrypt_score = value;
	minimum_decrypt_key = i;
	printf("The key 0x%02x gives the decrypt ", i);
	print_ascii(testdecrypt);
      }
      
    }
    free(testkey);
    free(testdecrypt);
  }
  
  free(bytes1);
  */
  exit(0);
}

