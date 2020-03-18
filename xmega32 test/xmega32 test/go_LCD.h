#include "include_file.h"

void lcd_command(uint8_t command);
void lcd_symbol(uint8_t symbol);
void lcd_position(uint8_t line, uint8_t position);
void lcd_string(uint8_t line, uint8_t position, char *data);
void lcd_init();
void lcd_int(uint8_t line, uint8_t position, int32_t number);