#pragma once

#include "tiki_core.h"

#include <Arduino.h>
#include <ST7735.h>

namespace tiki
{
	enum
	{
		GraphicsScreenWidth		= ST7735::height,
		GraphicsScreenHeight	= ST7735::width,

		GraphicsColorBlack		= 0x0000u,
		GraphicsColorWhite		= 0xffffu,
	};

	struct GraphicsFont
	{
		uint8	characterWidth;
		uint8	characterHeight;
		char	firstCharacter;
		char	lastCharacter;
		uint8	imageData[ 0u ];
	};

	class Graphics
	{
	public:

				Graphics();

		void	initialize();

		ST7735&	getTft() { return m_tft; }

		void	fillScreen( uint16_t color );
		void	drawPixel( uint8 x, uint8 y, uint16_t color );
		void	drawLine( uint8 x, uint8 y, uint16_t color );
		void	drawRectangle( const Rectangle& rect, uint16_t color );
		void	drawRectangle( uint8 x, uint8 y, uint8 width, uint8 height, uint16_t color );
		void	drawText( uint8 x, uint8 y, const void* pFont, const char* pText, uint16_t color, uint8 size = 1 );
		void	drawChar( uint8 x, uint8 y, const void* pFont, char c, uint16_t color, uint8 size = 1 );
		
	private:

		ST7735	m_tft;

		void	transformCoordinates( uint8* pX, uint8* pY );
	};
}