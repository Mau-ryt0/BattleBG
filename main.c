#include <gb/gb.h>
#include <stdbool.h>

#include "Tiles/blackTile.h"
#include "Maps/TestMap.h"
#include "Include/Setup.h"

#define TRANS_VEL 2

uint8_t j = 0;
uint8_t z = 140;
bool battle = false;
bool pressingStart = false;
joypads_t joypads;

void LCD_ISR()
{
	if (LYC_REG == j)
	{
		while (STAT_REG & STATF_BUSY);
		if (j == 70) SHOW_WIN;
		else if (j != 70) HIDE_WIN;
		LYC_REG = z;
	}
	else if (LYC_REG == z)
	{
		while (STAT_REG & STATF_BUSY);
		SHOW_WIN;
		LYC_REG = 0;
	}
	else if (LYC_REG == 0)
	{
		while (STAT_REG & STATF_BUSY);
		SHOW_WIN;
		LYC_REG = j;
	}
}

void main()
{
	CRITICAL
	{
        add_LCD(LCD_ISR);
        LYC_REG = j;
        STAT_REG |= STATF_LYC;
    }

	set_interrupts(IE_REG | LCD_IFLAG | VBL_IFLAG);

	// Setup the level.
	level_set();

	//Set the Window.
	WX_REG = 7; WY_REG = 0;
	set_win_data(0x7F, 15, blackTile);
	fill_win_rect(0, 0, 20, 18, 0x7F);

	//Show all the elements except the sprites.
	SHOW_WIN; SHOW_BKG;
    DISPLAY_ON;
	
	//Initializes the joypad.
	joypad_init(1, &joypads);
	
	//Main loop.
	while(1)
	{
		joypad_ex(&joypads);
		if (joypads.joy0 & J_START && pressingStart == false)
		{
			if (battle == false)
			{
				battle = true;
				for (uint8_t i=0; i<(70/TRANS_VEL); i++)
				{
					j+=TRANS_VEL; 
					if (z <= 72) z=71;
					else z-=TRANS_VEL;
					wait_vbl_done();
				}
			}
			else if (battle == true)
			{
				for (uint8_t i=0; i<(70/TRANS_VEL); i++)
				{
					j-=TRANS_VEL;
					if (z == 139) z=140;
					else z+=TRANS_VEL;
					wait_vbl_done();
				}
				battle = false;
			}
			pressingStart = true;
		}
		else if (!(joypads.joy0 & J_START) && pressingStart == true) pressingStart = false;
		wait_vbl_done();
	}
}
