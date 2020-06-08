#pragma once


// Types of specific sizes and behaviors regardless of platform
// TODO: Should we roll our own typedefs or use the int#_t ones defined in <stdint.h>?
typedef signed char        int8;
typedef short              int16;
typedef int                int32;
typedef long long          int64;
typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

static_assert(sizeof(int8) == 1, "sizeof(int8) expected to be 1 byte");
static_assert(sizeof(uint8) == 1, "sizeof(uint8) expected to be 1 byte");
static_assert(sizeof(int16) == 2, "sizeof(int16) expected to be 2 bytes");
static_assert(sizeof(uint16) == 2, "sizeof(uint16) expected to be 2 bytes");
static_assert(sizeof(int32) == 4, "sizeof(int32) expected to be 4 bytes");
static_assert(sizeof(uint32) == 4, "sizeof(uint32) expected to be 4 bytes");
static_assert(sizeof(int64) == 8, "sizeof(int64) expected to be 8 bytes");
static_assert(sizeof(uint64) == 8, "sizeof(uint64) expected to be 8 bytes");
