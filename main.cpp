#include <allegro.h>
#include <stdlib.h>
#include <string.h>

#include "CTerrain.h"
#include "common_definitions.h"

int main(void)
{
	int			ret = 0; // return value from function calls

	CTerrain	terrain;

	allegro_init();
	install_keyboard();
	set_color_depth(32);

	ret = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
	if (ret != 0) {
		allegro_message(allegro_error);
		return -1;
	} // if

	textprintf_ex(screen, font, 0, 0, 1, makecol(255,255,255), "%d %d", SCREEN_W, SCREEN_H);

	terrain.SetTerrain(SCREEN_H, SCREEN_W);
	terrain.Draw(screen, 0, SCREEN_W, 0, SCREEN_H, WORLDWIDTH, WORLDHEIGHT, 1);

	while (!keypressed());

	allegro_exit();

	return 0;
} // main
END_OF_MAIN()