#include <stdbool.h>

extern const float ascii_frequencies[];
bool byte_stream_is_ascii(unsigned char *bytes);
int byte_stream_compare_character_distribution(unsigned char *bytes);
