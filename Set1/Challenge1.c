#include <stdio.h>
#include <stdlib.h>

// Challenge1.c contains functions which can interconvert between null-terminated base64 strings and hexadecimal strings
// and bytes represented as a list of chars, where the 0th entry is the number of bytes present
// TODO: Fix memory issues where not all memory is cleaned up on a exit due to invalid input
// TODO: Do this by replacing exits with an returned invalid value and then handle cleanup?

unsigned char* convert_hex_str_to_bytes(char *input);
char* convert_bytes_to_hex_str(unsigned char *input);
void print_hex(unsigned char *input);

unsigned char* convert_base64_str_to_bytes(char *input);
char* convert_bytes_to_base64_str(unsigned char *input);
void print_base64(unsigned char *input);

unsigned char convert_hex_char_to_int(char input);
char *convert_byte_to_hex_chars(unsigned char input);
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
  printf("\n");
  print_base64(bytes);
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

char *convert_byte_to_hex_chars(unsigned char input){
  //Converts a single byte into a pair of hex characters
  char *output = malloc(sizeof(char)*2);
  if(((input&0xf0)>>4)>9){
    output[0] = ((input & 0xf0)>>4)+87;
  } else {
    output[0] = ((input & 0xf0)>>4)+48;
  }
  if((input&0x0f) > 9){
    output[1] = (input & 0x0f) + 87;
  } else {
    output[1] = (input & 0x0f) + 48;
  }
  return output;
}

char* convert_bytes_to_hex_str(unsigned char *input){
  // Converts a char array of bytes into a hex string
  // Note that the output here is a null terminated string with length length*2+1 including the null terminator
  int length = input[0];
  char *output = malloc(sizeof(char)*(length*2+1));

  for(int i = 0; i < length; i++){
    char *temp = convert_byte_to_hex_chars(input[i+1]);
    output[2*i] = temp[0];
    output[2*i+1] = temp[1];
    free(temp);
  }
  output[length*2] = 0x00;
  return output;
}

void print_hex(unsigned char *input){
  // Prints a array of chars storing a list of bytes as a hex string
  char *hex_str = convert_bytes_to_hex_str(input);
  printf("0x%s\n",hex_str);
  free(hex_str);
  return;
}

unsigned char convert_base64_char_to_int(char input){
  //Converts a single base64 character into an int between 0 and 63. Returns 64 for padding character and 255 for illegal character
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
  output[0] = (3*length)/4;

  for(int i = 0; i < (length/4); i++){

    unsigned char temp = convert_base64_char_to_int(input[4*i]);
    int char3value = 0;
    if(temp == 255){
      printf("Character %c in position %d is not a valid base64 character.\n\n",input[4*i], 4*i);
      free(output);
      exit(1);
    }
    char3value += (temp << 18);

    temp = convert_base64_char_to_int(input[4*i+1]);
    if(temp == 255){
      printf("Character %c in position %d is not a valid base64 character.\n\n",input[4*i+1], 4*i+1);
      free(output);
      exit(1);
    } else if(temp == 64){
      printf("Character %c is position %d is not a valid padding of base64.\n\n", input[4*i+1], 4*i+1);
      free(output);
      exit(1);
    }
    char3value += (temp << 12);

    temp = convert_base64_char_to_int(input[4*i+2]);
    if(temp == 255){
      printf("Character %c in position %d is not a valid base64 character.\n\n",input[4*i+2], 4*i+2);
      free(output);
      exit(1);
    } else if(temp == 64){
      output[3*i+1] = ((char3value & 0xff0000) >> 16);
      output[0] = 3*i+1;
      return output;
    }
    char3value += (temp << 6);

    temp = convert_base64_char_to_int(input[4*i+3]);
    if(temp == 255){
      printf("Character %c in position %d is not a valid base64 character.\n\n",input[4*i+3], 4*i+3);
      free(output);
      exit(1);
    } else if(temp == 64){
      output[3*i+1] = ((char3value & 0xff0000) >> 16);
      output[3*i+2] = ((char3value & 0x00ff00) >> 8);
      output[0] = 3*i+2;
      return output;
    }
    char3value += temp;

    output[3*i+1] = ((char3value & 0xff0000) >> 16);
    output[3*i+2] = ((char3value & 0x00ff00) >> 8);
    output[3*i+3] = (char3value & 0x0000ff);
  }
  return output;
}

char convert_int_to_base64_char(unsigned char input){
  // Takes in a 6 bit input and converts to a base64 character output
  char output = -1;

  if((input < 26)){
    output = input + 65;
  } else if((input > 25) && (input < 52)){
    output = input - 26 + 97;
  } else if((input > 51) && (input < 62)){
    output = input - 52 + 48;
  } else if(input == 62){
    output = 43;
  } else if(input == 62){
    output = 47;
  }
  return output;
}

char* convert_bytes_to_base64_str(unsigned char *input){
  //Converts a list of bytes into a string with its base64 representation
  int length = input[0];
  char *output = malloc(sizeof(char)*(4*((length/3)+((length%3)!=0))+1));

  for(int i = 0; i < (length/3); i++){
    int char3value = (input[3*i+1] << 16);
    char3value += (input[3*i+2] << 8);
    char3value += input[3*i+3];

    output[4*i] = convert_int_to_base64_char((char3value >> 18) & 0x3f);
    output[4*i+1] = convert_int_to_base64_char((char3value >> 12) & 0x3f);
    output[4*i+2] = convert_int_to_base64_char((char3value >> 6) & 0x3f);
    output[4*i+3] = convert_int_to_base64_char((char3value) & 0x3f);

  }

  if((length - 3*(length/3)) == 2){
    int char2value = (input[length - 1] << 8);
    char2value += input[length];
    output[4*(length/3)] = convert_int_to_base64_char((char2value >> 10) & 0x3f);
    output[4*(length/3)+1] = convert_int_to_base64_char((char2value >> 4) & 0x3f);
    output[4*(length/3)+2] = convert_int_to_base64_char((char2value << 2) & 0x3c);
    output[4*(length/3)+3] = 61;
  } else if((length - 3*(length/3))==1){
    int char1value = input[length];
    output[4*(length/3)] = convert_int_to_base64_char((char1value >> 2) & 0x3f);
    output[4*(length/3)+1] = convert_int_to_base64_char((char1value << 4) & 0x30);
    output[4*(length/3)+2] = 61;
    output[4*(length/3)+3] = 61;
  }

  output[4*((length/3)+1)] = 0x00;
  
  return output;
}

void print_base64(unsigned char *input){
  //Prints a list of bytes as its base64 representation
  char *base64_str = convert_bytes_to_base64_str(input);
  printf("%s\n",base64_str);
  free(base64_str);
  return;
}
