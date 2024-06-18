#include <stdbool.h>

bool byte_stream_is_1_byte_key_xor(unsigned char *bytes){
  int length = bytes[0];
  int counts[256] = {0};
  int count = 0;
  for(int i=0; i < length; i++){
    counts[bytes[i+1]] += 1;
    count += 1;
  }
  
  return false
}
