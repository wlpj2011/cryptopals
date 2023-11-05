#include <stdbool.h>

const float ascii_frequencies[] = {0.2254, 0.0727, 0.0133, 0.0248, 0.0381, 0.1126, 0.0195, 0.0177, 0.0541, 0.0621, 0.0013, 0.0068, 0.0355, 0.0213, 0.0594, 0.0665, 0.0169, 0.0008, 0.0532, 0.0559, 0.0807, 0.0248, 0.0087, 0.0213, 0.0013, 0.0177, 0.0007};

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
