/*
   File  : Binary.h
   Author: Afonso Santos, Portugal

   Last revision: 12h45 August 05 2016
*/

#pragma once


#include <pebble.h>


typedef struct
{ unsigned int  nBits ;
  unsigned char *bits ;
} BitString ;


/*  Code TEMPLATEs for bits initialization
const unsigned char *SOME_CONSTANT_MAP_L2R[??]
// Bit index ruller      [00..07]    [08..15]    [16..23]    [24..31]    [32..39]    [40..47]    [48..55]    [56..63]
//                       00000000    00111111    11112222    22222233    33333333    44444444    44555555    55556666
//                       01234567    89012345    67890123    45678901    23456789    01234567    89012345    67890123
= { (unsigned char[]){ 0b????????, 0b????????, 0b????????, 0b????????, 0b????????, 0b????????, 0b????????, 0b???????? }
  , (unsigned char[]){ 0b????????, 0b????????, 0b????????, 0b????????, 0b????????, 0b????????, 0b????????, 0b???????? }
  , ...
  }
;

const unsigned char *SOME_CONSTANT_MAP_L2R
= (unsigned char[])
  { 0b????????    //   0..  7
  , 0b????????    //   8.. 15
  , 0b????????    //  16.. 23
  , 0b????????    //  24.. 31
  , 0b????????    //  32.. 39
  , 0b????????    //  40.. 47
  , 0b????????    //  48.. 55
  , 0b????????    //  56.. 63
  , 0b????????    //  64.. 71
  , 0b????????    //  72.. 79
  , 0b????????    //  80.. 87
  , 0b????????    //  88.. 95
  , 0b????????    //  96..103
  , 0b????????    // 104..111
  , 0b????????    // 112..119
  , 0b????????    // 120..127
  , 0b????????    // 128..135
  , 0b????????    // 136..143
  , 0b????????    // 144..151
  , 0b????????    // 152..159
  , 0b????????    // 160..167
  , 0b????????    // 168..175
  , 0b????????    // 176..183
  }
;
*/


// Left to right bit indexing.

bool
Binary_isSetL2R
( const unsigned char *bits
, const unsigned int   bitIndex
) ;


bool
Binary_setL2R
( unsigned char       *bits
, const unsigned int   bitIndex
) ;


// Right to left bit indexing.

bool
Binary_isSetR2L
( const unsigned char *bits
, const unsigned int   bitIndex
) ;

bool
Binary_setR2L
( unsigned char       *bits
, const unsigned int   bitIndex
) ;