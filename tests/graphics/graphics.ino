#include "tiki_graphics.h"

tiki::Graphics graphics;

int x = 0;
int y = y;
int color = 0xffff;

void setup()
{
	graphics.initialize();
	graphics.fillScreen( 0x0000u );
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
			color = (color == 0x00ffu ? 0xff00 : 0x00ff);

			graphics.drawRectangle( 50u, 50u, 50u, 50u, color );
		}
	}
}

