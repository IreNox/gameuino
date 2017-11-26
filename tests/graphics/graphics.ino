#include "tiki_graphics.h"

tiki::Graphics graphics;

int x = 0;
int y = y;
int color = 0xffff;

void setup()
{
	graphics.initialize();
	graphics.fillScreen( 0x0000u );

	//tiki::GraphicsTft& tft = graphics.getTft();
	//widtft.drawString(0, 0, "Test", color );
}

void loop()
{
	graphics.drawPixel( x, y, color );

	x++;
	if( x > tiki::GraphicsScreenWidth )
	{
		x = 0;
		y++;                                        
		if( y > tiki::GraphicsScreenHeight )
		{
			y = 0;
			color = (color == 0x0000u ? 0xffff : 0x0000);

			//tiki::GraphicsTft& tft = graphics.getTft();
			//tft.drawString(0, 0, "Test", color );
		}
	}
}

