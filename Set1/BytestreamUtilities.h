
unsigned char* convert_hex_str_to_bytes(char *input);
char* convert_bytes_to_hex_str(unsigned char *input);
void print_hex(unsigned char *input);

unsigned char* convert_base64_str_to_bytes(char *input);
char* convert_bytes_to_base64_str(unsigned char *input);
void print_base64(unsigned char *input);

unsigned char convert_hex_char_to_int(char input);
char *convert_byte_to_hex_chars(unsigned char input);
unsigned char convert_base64_char_to_int(char input);

void print_ascii(unsigned char *input);

unsigned char* xor_byte_streams(unsigned char *bytes1, unsigned char *bytes2);
