#ifndef SCR_H_
#define SCR_H_


#define VIDEO_ADDRESS (void*)0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4

/* Screen i/o ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

/* Public kernel API */
void clear_screen();
void kprint_at(char *message, int col, int row, char attr);
void kprint(char *message);
void kprintcol(char *message, char attr);
int get_offset_col(int offset);
int get_offset_row(int offset);
int get_offset(int col, int row);
void set_cursor_offset(int offset);
int get_cursor_offset();
int print_char(char c, int col, int row, char attr);
void kprint_backspace();


#endif