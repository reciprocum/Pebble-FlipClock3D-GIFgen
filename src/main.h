/*
   Project: GIFgen
   File   : main.h
   Author : Afonso Santos, Portugal

   Last revision: 13h35 August 18 2016
*/

#include <pebble.h>


// GIF related
#define GIF_FRAME_STOP        0
#define GIF_SLOWDOWN_FACTOR   3

/* GIF#01 */
#define GIF_BASE_DD  29
#define GIF_BASE_HH  23
#define GIF_BASE_MM  57
#define GIF_BASE_SS  26

/* GIF#02
#define GIF_BASE_DD  31
#define GIF_BASE_HH  19
#define GIF_BASE_MM  49
#define GIF_BASE_SS  26
*/

/* GIF#03
#define GIF_BASE_DD  27
#define GIF_BASE_HH   9
#define GIF_BASE_MM  57
#define GIF_BASE_SS  26
*/


//#define TRANSPARENCY_DEFAULT      MESH3D_TRANSPARENCY_XRAY
#define TRANSPARENCY_DEFAULT      MESH3D_TRANSPARENCY_SOLID

// Animation related
#define ANIMATION_INTERVAL_MS     40
#define ANIMATION_FLIP_STEPS      50
#define ANIMATION_SPIN_STEPS      75
