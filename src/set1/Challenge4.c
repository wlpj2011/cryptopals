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
  FILE *fptr;
  
  fptr = fopen(argv[1],"r");

  if(fptr == NULL) {
    printf("Not able to open %s.\n",argv[1]);
    exit(1);
  }

  rewind(fptr);
  //Need a loop over the number of lines in the file
  //Want to read a single line from fptr and store it as a string hex_bytes

  int LINELENGTH = 62;
  // This only supports things of known and fixed length
  char hex_bytes[LINELENGTH];

  while(fgets(hex_bytes,sizeof(hex_bytes), fptr) != NULL){
    printf("%s",hex_bytes);
    if(hex_bytes[LINELENGTH] == '\n'){
      // If the last character is a newline, make it null
      hex_bytes[LINELENGTH] = 0x00;
    }
    
    //Convert to a bytestring
    unsigned char *enc_bytes = convert_hex_str_to_bytes(hex_bytes);
    
    
    int length = enc_bytes[0];
    //Set initial decrypt parameters
    float minimum_decrypt_score = 27.0;
    int best_decrypt_key = 0x00;

    //Trial decrypt
    for(int i=0; i < 256; i++){
      // Create an array to be used as a bytestream and fill it with repeitions of the key
      // Should make a function for this that takes a sequence of key bytes to repeat and a total length
      unsigned char key[2] = {1,i};
      unsigned char *testkey = create_periodic_byte_stream(key,length);
      testkey[0] = length;
      for(int j = 0; j < length; j++){
	testkey[j+1] = i;
      }
      //      print_hex(enc_bytes);
      unsigned char *testdecrypt = xor_byte_streams(enc_bytes,testkey);
      if(byte_stream_is_ascii(testdecrypt)){
	float value = byte_stream_compare_character_distribution(testdecrypt);
	if(value < minimum_decrypt_score){
	  minimum_decrypt_score = value;
	  best_decrypt_key = i;
	  printf("The key 0x%02x gives the decrypt ", i);
	  print_ascii(testdecrypt);
	}
      }
      free(testkey);
      free(testdecrypt);
    }
    printf("\n");
    free(enc_bytes);
  }
 
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
  */
  //free(bytes1);

  fclose(fptr);
  
  exit(0);
}

