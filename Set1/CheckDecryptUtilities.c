#include <stdio.h>
#include <stdbool.h>

const float ascii_frequencies[] = {0.2254, 0.0727, 0.0133, 0.0248, 0.0381, 0.1126, 0.0195, 0.0177, 0.0541, 0.0621, 0.0013, 0.0068, 0.0355, 0.0213, 0.0594, 0.0665, 0.0169, 0.0008, 0.0532, 0.0559, 0.0807, 0.0248, 0.0087, 0.0213, 0.0013, 0.0177, 0.0007};
//This is space, then A-Z. Does not account for upper vs. lower case
// 32 = 0x20 and either 65 = 0x41 - 90 = 0x5A or 97 = 0x61 - 122 = 0x7A.
//Need to convert everything to either upper or lower case and work with that

bool byte_stream_is_ascii(unsigned char *bytes){
  int length = bytes[0];
  for(int i =0; i < length; i++){
    if((bytes[i+1] > 127) || (bytes[i+1] < 32)){
      return false;
    }
  }
  return true;
}

float byte_stream_compare_character_distribution(unsigned char *bytes){
  float byte_frequencies[] = {0};
  int length = bytes[0];
  for(int i = 1; i < length; i++){
    if(bytes[i] == 0x20){
      byte_frequencies[0] += 1/length;
    } else if((bytes[i] > 0x41) && (bytes[i] < 0x5A)){
      byte_frequencies[bytes[i] - 0x40] += 1/length;
    } else if((bytes[i] > 0x61) && (bytes[i] < 0x7A)){
      byte_frequencies[bytes[i] - 0x60] += 1/length;
    }
  }
  for(int i = 0; i < 27; i++){
    printf("%f\n",byte_frequencies[i]);
  }
  return 0.0;
}
