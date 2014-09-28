#if !defined(__CTERRAIN_H)
#define __CTERRAIN_H
#include "allegro.h"
#include "common_definitions.h"

class CTerrain {
private:
	POINT			terrainPoints[NUMPOINTS];
	int				terrainWidth;
	int				terrainHeight;
	void			generate_terrain();
	void			generate_sub_terrain(POINT *t, int xi1, int xi2);
	void			perturb(int *value, int lower, int upper, double percent);
public:
	void			Draw(BITMAP *bmp, int start, int end, int relX, int relY,
							int ww, int wh, int erase);
	void			SetTerrain(int h, int w);
	void			PrintTerrainPoints();
	POINT			GetTerrainPoint(int index);
}; // CTerrain
#endif // __CTERRAIN_H