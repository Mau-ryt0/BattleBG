#include <gb/gb.h>
#include <gb/cgb.h>
#include "Maps/TestMap.h"
#include "Tiles/Tiles.h"

UWORD BGPalette[4] = {RGB(30, 25, 20), RGB(18, 15, 10), RGB(14, 11, 6), RGB(3, 3, 3)};
UWORD DrawerPalette[4] = {RGB8(207, 174, 128), RGB8(207, 174, 128), RGB8(117, 83, 31), RGB8(32, 32, 32)};

inline void set_attributed_bkg_tiles(UBYTE x, UBYTE y, UBYTE w, UBYTE h, const UBYTE * map, const UBYTE * attr, const UBYTE MapWidth, uint8_t base)
{
    if (_cpu == CGB_TYPE)
    {
        VBK_REG = 1;
        set_bkg_submap(x, y, w, h, (UBYTE *)attr, MapWidth);
        VBK_REG = 0;
    }
    set_bkg_based_submap(x, y, w, h, (UBYTE *)map, MapWidth, base);
}

void level_set()
{
	// Set the Background.
	set_bkg_palette(0, 1, &BGPalette[0]);
	set_bkg_palette(1, 1, &DrawerPalette[0]);
	set_bkg_data(0, 33, TestRoomTiles);
	set_attributed_bkg_tiles(0, 0, 20, 18, TestMapPLN0, TestMapPLN1, TestMapWidth, 0);
}