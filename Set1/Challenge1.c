#include <stdio.h>
#include <stdlib.h>

unsigned char* convert_hex_str_to_bytes(char *input, int length);
unsigned char* convert_bytes_to_hex_str(char *input, int length);
unsigned char* convert_base64_str_to_bytes(char *input, int length);
unsigned char* convert_bytes_to_base64(char *input, int length);

int main(int argc, char *argv[])
{
  if(argc != 2){
    printf("Usage: %s hexinput",argv[0]);
    exit(1);
  }

  printf("The input was %s.\n",argv[1]);

  int length = 0;
  while(argv[1][length] != 0x00){
    length += 1;
  }
    
  
  unsigned char *bytes = convert_hex_str_to_bytes(argv[1],length);
  length = length/2;
  for(int i = 0; i < length; i++){
    printf("%d ",bytes[i]);
  }
  printf("\n");
  free(bytes);
  exit(0);
}

unsigned char* convert_hex_str_to_bytes(char *input, int length){
  //Converts a string of length hex characters into an array of byte values 
  unsigned char *output = malloc((length/2)*sizeof(char));
  for(int i = 0; i < length/2; i++){
    if((input[2*i] > 47) && (input[2*i] < 58)){
      output[i] += 16*(input[2*i] - 48);
    } else if((input[2*i] > 96) && (input[2*i] < 103)){
      output[i] += 16*(input[2*i] - 87);
    } else if((input[2*i] > 64) && (input[2*i] < 71)){
      output[i] += 16*(input[2*i] - 55);
    } else {
      printf("Character in position %d is not a valid hex character.\n", 2*i);
      free(output);
      exit(1);
    }
    if((input[2*i+1] > 47) && (input[2*i+1] < 58)){
      output[i] += (input[2*i+1]-48);
    } else if((input[2*i+1] > 96) && (input[2*i+1] < 103)){
      output[i] += (input[2*i+1]-87);
    } else if((input[2*i+1] > 64) && (input[2*i+1] < 71)){
      output[i] += (input[2*i+1]-55);
    } else {
      printf("Character in position %d is not a valid hex character.\n", 2*i+1);
      free(output);
      exit(1);
    }
  }
  return output;
}


unsigned char* convert_bytes_to_hex_str(char *input, int length){


}
unsigned char* convert_base64_str_to_bytes(char *input, int length){


}
unsigned char* convert_bytes_to_base64(char *input, int length){

  
}