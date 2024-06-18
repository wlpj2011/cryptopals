#pragma once
#include <stdbool.h>

extern const float ascii_frequencies[];
extern const float ascii_frequencies_sorted[];
bool byte_stream_is_ascii(unsigned char *bytes);
float byte_stream_compare_character_distribution(unsigned char *bytes);
