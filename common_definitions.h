#if !defined(__COMMON_DEFINITIONS_H)
#define __COMMON_DEFINITIONS_H
#include "allegro.h"

#define WORLDWIDTH (SCREEN_W * 10)
#define WORLDHEIGHT (SCREEN_H * 2)

typedef struct POINT {
	int		x; // x location in game
	int		y; // y location in game
	int		z; // z location in game
} POINT;

#define NUMPOINTS 8000
#define ROUGHNESS (0.05)



#endif // __COMMON_DEFINITIONS_H