#include <stdio.h>
#include "CTerrain.h"

void CTerrain::SetTerrain(int h, int w)
{
	int			i = 0;
	POINT		p;

	for (i = 0; i < NUMPOINTS-1; i++)
		terrainPoints[i].x = terrainPoints[i].y = terrainPoints[i].z = 0;

	generate_terrain();

	return;
} // SetTerrain

POINT CTerrain::GetTerrainPoint(int index)
{
	if (index < 0 || index > NUMPOINTS-1)
		allegro_message("GetTerrrainPoint: bad index!");

	return terrainPoints[index];
} // GetTerrainPoint
void CTerrain::generate_terrain()
{
	terrainPoints[0].x = 0; 
	terrainPoints[0].y = SCREEN_H-200;
	terrainPoints[NUMPOINTS-1].x = WORLDWIDTH;
	terrainPoints[NUMPOINTS-1].y = SCREEN_H-300;

	generate_sub_terrain(terrainPoints, 0, NUMPOINTS-1);

	PrintTerrainPoints();
} // generate_terrain

void CTerrain::generate_sub_terrain(POINT *t, int xi1, int xi2)
{
	int		midxi; // Midpoint of line segment
	int		y1, y2, y3, tmp; 
	int		x1, x2, x3; // points inside line segment.

	midxi = (xi2 - xi1) / 2 + xi1; // Midpoint of line segment in x plane

	if (midxi == xi2 || midxi == xi1)
		return;

	y1 = t[xi1].y; // pull out first point in line segment array.
	y2 = t[xi2].y; //  pull out last pount in line segment array.
	if (y2 > y1) {
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	} // if

	y3 = ((y1 - y2) / 2) + y2;
	if (y3 > SCREEN_H)
		y3 = SCREEN_H / 2;
	if (y3 < 0)
		y3 = SCREEN_H / 2;

	x1 = t[xi1].x;
	x2 = t[xi2].x;
	if (x1 > x2) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	} // if

	x3 = ((x2 - x1) / 2) + x1;

	perturb(&x3, x2, x1, ROUGHNESS);
	perturb(&y3, y2, y1, ROUGHNESS);
	if (y3 > SCREEN_H)
		y3 = SCREEN_H / 2;
	if (y3 < 0)
		y3 = SCREEN_H / 2;

	t[midxi].x = x3;
	t[midxi].y = y3;

	generate_sub_terrain(t, xi1, midxi);
	generate_sub_terrain(t, midxi, xi2);
} // generate_sub_terrain

void CTerrain::perturb(int *value, int lower, int upper, double percent)
{
	double perterbation;

	perterbation = percent * (upper-lower) * ((0.0 + rand()) / (0.0 + RAND_MAX) - 0.5);

	*value += perterbation;
	return;
} // perturb

void CTerrain::Draw(BITMAP *bmp, int start, int end, int relX, int relY,
							int ww, int wh, int erase)
{
	int			i; // For array index
	int			drawX0; // First x location to draw line from.
	int			drawY0; // First Y location to draw line from.
	int			drawX1; // Second point to draw line to.
	int			drawY1; // Second point to draw line to.
	POINT		p; 
	POINT		p1;

	// Array bounds checking
	if ( (start < 0) || (start > (NUMPOINTS-1))) {
		allegro_message("DRAW start out of bounds!");
		return;
	} // if 

	if ( (end < 0) || (end > (NUMPOINTS-1))) {
		allegro_message("DRAW end out of bounds!");
		return;
	} // if

	p = terrainPoints[start];
	p1 = terrainPoints[end];

	drawX0 = p.x - relX;
	drawY0 = p.y;
	drawX1 = p1.x - relX;
	drawY1 = p1.y;

	if ( (drawX0 < 0) || (drawX0 > (ww+100))) return;
	if ( (drawX1 < 0) || (drawX1 > (ww+100))) return;
	//if ( (drawY0 < 0) || (drawY0 > (wh))) return;
	//if ( (drawY1 < 0) || (drawY1 > (wh))) return;

	line(bmp, drawX0, drawY0, drawX1, drawY1, makecol(0, 255, 0));
} // Draw

void CTerrain::PrintTerrainPoints()
{
	int	i;
	char buf[500];

	for (i = 0; i < NUMPOINTS-1; i++) {
		sprintf(buf, "%d p[%d %d]\n", i, terrainPoints[i].x, terrainPoints[i].y);
		TRACE(buf);
	} // for
} // PrintTerrainPoints
