// INCLUDED IN BMPCH.HPP
#pragma once

#include <cinttypes>

// (Assuming 8 bit system ie. [CHAR_BIT == 8])
// Prefix:
//  'i' int
//  'ui' unsigned int
//  'f' float
//  'c' char
//  'uc' unsigned char
//  'b' unsigned char (single byte bool)
// 
// Infix:
//  type bit size
// 
// Suffix:
//  't' are of gauranteed bit size
//  'ut' are of non-gauranteed bit size
//  'bt' are unsigned ints indicating variable bit size

// strictly 08 bit signed int
using i8t = int8_t;
// strictly 16 bit signed int
using i16t = int16_t;
// strictly 32 bit signed int
using i32t = int32_t;
// strictly 64 bit signed int
using i64t = int64_t;

// strictly 08 bit unsigned int
using ui8t = uint8_t;
// strictly 16 bit unsigned int
using ui16t = uint16_t;
// strictly 32 bit unsigned int
using ui32t = uint32_t;
// strictly 64 bit unsigned int
using ui64t = uint64_t;

// strictly 08 bit unsigned 'byte count' int
using ui8bt = uint8_t;
// strictly 16 bit unsigned 'byte count' int
using ui16bt = uint16_t;
// strictly 32 bit unsigned 'byte count' int
using ui32bt = uint32_t;
// strictly 64 bit unsigned 'byte count' int
using ui64bt = uint64_t;

// probably 32 bit float
using f32ut = float;
// probably 64 bit float
using f64ut = double;

// structly 08 bit signed char
using c8t = signed char;
// structly 08 bit unsigned signed char
using uc8t = unsigned char;

// strictly 08 bit bool (unsigned char)
using b8t = unsigned char;

// strictly 08 bit byte (unsigned char)
using byte = unsigned char;

// OpenGL Unique Identifier
using gluid = ui32t;
