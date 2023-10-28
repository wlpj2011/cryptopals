#include <stdio.h>
#include <stdlib.h>

unsigned char* convert_hex_str_to_bytes(char *input, int length);
char* convert_bytes_to_hex_str(unsigned char *input, int length);
void print_hex(unsigned char *input);

unsigned char* convert_base64_str_to_bytes(char *input, int length);
char* convert_bytes_to_base64(unsigned char *input, int length);
void print_base64(unsigned char *input);


int main(int argc, char *argv[]){
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
  char *newhex = convert_bytes_to_hex_str(bytes,length);
  print_hex(bytes);
  free(bytes);
  free(newhex);

  printf("\n");
  exit(0);
}

unsigned char* convert_hex_str_to_bytes(char *input, int length){
  // Converts a string of "length" hex characters into an array of byte values
  // Note that we will make the 0th byte of the output be the number of bytes stored, so we can only return up to 255 bytes for now.
  // #TODO: Fix this so it can hold at least 65535 bytes, maybe more.
  unsigned char *output = malloc((1+(length/2))*sizeof(char));
  output[0] = length/2;
  for(int i = 0; i < length/2; i++){
    if((input[2*i] > 47) && (input[2*i] < 58)){
      output[i+1] += 16*(input[2*i] - 48);
    } else if((input[2*i] > 96) && (input[2*i] < 103)){
      output[i+1] += 16*(input[2*i] - 87);
    } else if((input[2*i] > 64) && (input[2*i] < 71)){
      output[i+1] += 16*(input[2*i] - 55);
    } else {
      printf("Character %c in position %d is not a valid hex character.\n",input[2*i] ,2*i);
      free(output);
      exit(1);
    }
    if((input[2*i+1] > 47) && (input[2*i+1] < 58)){
      output[i+1] += (input[2*i+1]-48);
    } else if((input[2*i+1] > 96) && (input[2*i+1] < 103)){
      output[i+1] += (input[2*i+1]-87);
    } else if((input[2*i+1] > 64) && (input[2*i+1] < 71)){
      output[i+1] += (input[2*i+1]-55);
    } else {
      printf("Character %c in position %d is not a valid hex character.\n",input[2*i+1], 2*i+1);
      free(output);
      exit(1);
    }
  }
  return output;
}


char* convert_bytes_to_hex_str(unsigned char *input, int length){
  // Converts a char array of "length" bytes into a hex string
  // Note that the output here is a null terminated string with length length*2+1 including the null terminator
  char *output = malloc(sizeof(char)*(length*2+1));

  for(int i = 0; i < length; i++){
    if(((input[i]&0xf0)>>4)>9){
      output[2*i] = ((input[i] & 0xf0) >> 4) + 87;
    } else {
      output[2*i] = ((input[i] & 0xf0) >> 4) + 48;
    }
    if((input[i]&0x0f) > 9){
      output[2*i+1] = (input[i] & 0x0f) + 87;
    }
    else {
      output[2*i+1] = (input[i] & 0x0f) + 48;

    }
  }
  output[length*2] = 0x00;
  return output;
}

void print_hex(unsigned char *input){
  int length = input[0];
  char *hex_str = convert_bytes_to_hex_str(input+1,length);
  printf("0x%s",hex_str);
  free(hex_str);
  return;
}

unsigned char* convert_base64_str_to_bytes(char *input, int length){
  unsigned char *output = malloc(sizeof(unsigned char)*length);
  return output;
}
char* convert_bytes_to_base64(unsigned char *input, int length){
  char *output = malloc(sizeof(char)*length);
  return output;
}

void print_base65(unsigned char *input){


  return;
}
