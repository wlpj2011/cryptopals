#include <stdio.h>
#include <stdlib.h>

unsigned char* convert_hex_str_to_bytes(char *input);
char* convert_bytes_to_hex_str(unsigned char *input);
void print_hex(unsigned char *input);

unsigned char* convert_base64_str_to_bytes(char *input);
char* convert_bytes_to_base64_str(unsigned char *input);
void print_base64(unsigned char *input);

unsigned char convert_hex_char_to_int(char input);
unsigned char convert_base64_char_to_int(char input);

int main(int argc, char *argv[]){
  if(argc != 2){
    printf("Usage: %s hexinput",argv[0]);
    exit(1);
  }
  printf("\n");
  printf("The input was %s.\n",argv[1]);

  unsigned char *bytes = convert_hex_str_to_bytes(argv[1]);
  print_hex(bytes);
  free(bytes);

  printf("\n\n");
  exit(0);
}

unsigned char convert_hex_char_to_int(char input){
  // Outputs that value of the nibble that corresponds to the input hex character, or outputs 255 in the case of an invalid hex character
  if((input > 47) && (input < 58)){
    return input - 48;
  } else if((input > 96) && (input < 103)){
    return input - 87;
  } else if((input > 64) && (input < 71)){
    return input - 55;
  } else {
    return 255;
  }
}

unsigned char* convert_hex_str_to_bytes(char *input){
  // Converts a string of null terminated hex characters into an array of byte values
  // Note that we will make the 0th byte of the output be the number of bytes stored, so we can only return up to 255 bytes for now.
  // #TODO: Fix this so it can hold at least 65535 bytes, maybe more.
  int length = 0;
  while(input[length] != 0x00){
    length +=1;
  }
  unsigned char *output = malloc((1+(length/2))*sizeof(char));
  output[0] = length/2;
  for(int i = 0; i < length/2; i++){
    unsigned char temp = convert_hex_char_to_int(input[2*i]);
    if(temp == 255){
      printf("Character %c in position %d is not a valid hex character.\n\n",input[2*i] ,2*i);
      free(output);
      exit(1);
    }
    output[i+1] = (temp << 4);
    temp = convert_hex_char_to_int(input[2*i+1]);
    if(temp == 255){
      printf("Character %c in position %d is not a valid hex character.\n\n",input[2*i+1], 2*i+1);
      free(output);
      exit(1);
    }
    output[i+1] += temp;
  }
  return output;
}


char* convert_bytes_to_hex_str(unsigned char *input){
  // Converts a char array of bytes into a hex string
  // Note that the output here is a null terminated string with length length*2+1 including the null terminator
  int length = input[0];
  char *output = malloc(sizeof(char)*(length*2+1));

  for(int i = 0; i < length; i++){
    if(((input[i+1]&0xf0)>>4)>9){
      output[2*i] = ((input[i+1] & 0xf0) >> 4) + 87;
    } else {
      output[2*i] = ((input[i+1] & 0xf0) >> 4) + 48;
    }
    if((input[i+1]&0x0f) > 9){
      output[2*i+1] = (input[i+1] & 0x0f) + 87;
    }
    else {
      output[2*i+1] = (input[i+1] & 0x0f) + 48;

    }
  }
  output[length*2] = 0x00;
  return output;
}

void print_hex(unsigned char *input){
  // Prints a array of chars storing a list of bytes as a hex string
  char *hex_str = convert_bytes_to_hex_str(input);
  printf("0x%s",hex_str);
  free(hex_str);
  return;
}

unsigned char convert_base64_char_to_int(char input){
  if((input > 64) && (input < 91)){
    return input -65;
  } else if((input > 96) && (input < 123)){
    return input - 97 + 26;
  } else if((input > 47) && (input < 58)){
    return input - 48 + 52;
  } else if(input == 43){
    return 62;
  } else if(input == 47){
    return 63;
  } else if(input == 61){
    return 64;
  } else {
    return 255;
  }
}

unsigned char* convert_base64_str_to_bytes(char *input){
  // Converts a null terminated base64 string into a list of bytes where the 0th position stores the number of bytes
  // TODO: make this so it can store 65535 bytes instead of only 255
  int length = 0;
  while(input[length] != 0x00){
    length += 1;
  }
  unsigned char *output = malloc(sizeof(unsigned char)*(((3*length)/4)+1));
  output[0] = length;

  for(int i = 0; i < (length/4); i++){
    
  }
  
  return output;
}

char* convert_bytes_to_base64_str(unsigned char *input){
  int length = input[0];
  char *output = malloc(sizeof(char)*length);

  
  return output;
}

void print_base64(unsigned char *input){
  char *base64_str = convert_bytes_to_base64_str(input);
  printf("%s",base64_str);
  free(base64_str);
  return;
}
