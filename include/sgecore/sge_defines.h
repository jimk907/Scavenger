#pragma once

#include <stdint.h>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

//-------------------------------------------------------------
//_DEBUG and NDEBUG (needed for assert.h) may be
// specific to the Microsoft compilers. Change this
// definition as needed to conform to other development
// tools or environments
//-------------------------------------------------------------
#ifndef _DEBUG
#ifndef NDEBUG
#define NDEBUG
#endif
#endif
#include <assert.h>


//-------------------------------------------------------------
// Only Windows builds are supported at this time.
// Note: _WIN32 is defined for both x32 and x64 builds.
//-------------------------------------------------------------
#if defined (_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "sge_win32.h"
#else
#error "Only Win32 platform is supported."
#endif

#  ifdef _DLL
#    define SGEAPI __declspec(dllexport)
#  else
#    define SGEAPI __declspec(dllimport)
#  endif


//-------------------------------------------------------------
//  Win32 memory leak detector
//  Only active in _DEBUG configurations
//-------------------------------------------------------------
#if defined WIN32 && defined _DEBUG
#  define _CRTDBG_MAP_ALLOC  
#  include <stdlib.h>  
#  include <crtdbg.h>  
#  define SGE_MEM_LEAK_CHECK    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF); 
#  define SGE_MEM_LEAK_BREAK(n) _CrtSetBreakAlloc(n);
#else
#  define SGE_MEM_LEAK_CHECK
#  define SGE_MEM_LEAK_BREAK
#endif


typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;
typedef int64_t  i64;
typedef int32_t  i32;
typedef int16_t  i16;
typedef int8_t   i8;
typedef double   f64;
typedef float    f32;


typedef uint32_t u32ptr;
typedef uint32_t handle;


//-------------------------------------------------------------
// Provide short-hand definitions for std string types
//-------------------------------------------------------------
typedef std::wstring WString;
typedef std::string  String;


//-------------------------------------------------------------
// Frequently used constants for Jackal math functions
//-------------------------------------------------------------
const f64 PI64 =  3.141592653589793;
const f64 RAD64 = 0.017453292519943;		// radians per degree
const f64 DEG64 = 57.29577951308233;		// degrees per radian
const f64 EPS64 = 2.2204460492503131e-016;
const f32 PI32 =  3.14159265f;
const f32 RAD32 = 0.01745329f;
const f32 DEG32 = 57.29577958f;
const f32 EPS32 = 1.192092896e-07f;

//-------------------------------------------------------------
// Define this symbol to convert all Jackal math funtions
//    to 64-bit precision.
//-------------------------------------------------------------
#ifndef JGE_PRECISION_64
typedef float       real;
typedef i32         intr;
typedef u32         uintr;
#define COS         cosf
#define SIN         sinf
#define TAN         tanf
#define ACOS        acosf
#define ASIN        asinf
#define SQRT        sqrtf
const f32 R_PI  =   PI32;
const f32 R_DEG =   DEG32;
const f32 R_RAD =   RAD32;
const f32 R_EPS =   EPS32;
const f32 EPSILON = EPS32;
//-------------------------------------------------------------
// The following constants are defined for legacy code.
// For example - convertion of 62.0f degrees to radians:
//    radians = 62.0f * DEGREES;
// To convert radians to degrees:
//    degrees = 3.14 * RADIANS;
//-------------------------------------------------------------
const f32 DEGREES = RAD32;
const f32 RADIANS = DEG32;
#else
typedef double      real;
typedef i64         intr;
typedef u64         uintr;
#define COS         cos
#define SIN         sin
#define TAN         tan
#define ACOS        acos
#define ASIN        asin
#define SQRT        sqrt
const f64 R_PI  =   PI64;
const f64 R_DEG =   DEG64;
const f64 R_RAD =   RAD64;
const f64 R_EPS =   EPS64;
const f64 EPSILON = EPS64;
//-------------------------------------------------------------
// see prior comment for use of DEGREES and RADIANS
//-------------------------------------------------------------
const f64 DEGREES = RAD64;
const f64 RADIANS = DEG64;
#endif

