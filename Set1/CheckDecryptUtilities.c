#include <stdbool.h>

bool byte_stream_is_ascii(unsigned char *bytes){
  int length = bytes[0];
  for(int i =0; i < length; i++){
    if((bytes[i+1] > 127) || (bytes[i+1] < 32)){
      return false;
    }
  }
  return true;
}

int byte_stream_compare_character_distribution(unsigned char *bytes){

  return 0;
}
