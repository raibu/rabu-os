#ifndef TYPES_H
#define TYPES_H

/* Instead of using 'chars' to allocate non-character bytes,
 * we will use these new type with no semantic meaning */
typedef unsigned int   u32;
typedef unsigned int   uint;
typedef          int   i32;
typedef unsigned short u16;
typedef          short i16;
typedef unsigned char  u8;
typedef          char  i8;

#define low_16(address) (u16)((address) & 0xFFFF)
#define high_16(address) (u16)(((address) >> 16) & 0xFFFF)

#define low_8(address) (u8)((address) & 0xFF)
#define high_8(address) (u8)(((address) >> 8) & 0xFF)

#endif