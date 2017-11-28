#pragma once

#include "tiki_core.h"
#include "tiki_st7735.h"

namespace tiki
{
	typedef ST7735 GraphicsTft;

	enum
	{
		GraphicsScreenWidth		= s_displayWidth,
		GraphicsScreenHeight	= s_displayHeight,

		GraphicsColorBlack		= 0x0000u,
		GraphicsColorWhite		= 0xffffu,
	};

	struct GraphicsImage
	{
		uint8	width;
		uint8	height;
		uint8	format;
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

		void			initialize();

		GraphicsTft&	getTft() { return m_tft; }

		void			fillScreen( uint16_t color );
		void			drawPixel( uint8 x, uint8 y, uint16_t color );
		void			drawRectangle( const Rectangle& rect, uint16_t color );
		void			drawRectangle( uint8 x, uint8 y, uint8 width, uint8 height, uint16_t color );
		void			drawImage( uint8 x, uint8 y, const uint8* pImage );
		void			drawImageProgramMemory( uint8 x, uint8 y, const uint8* pImage );
		void			drawTexture( uint8 x, uint8 y, uint8 width, uint8 height, const Color* pPixels );
		void			drawText( uint8 x, uint8 y, const void* pFont, const char* pText, uint16_t color, uint8 size = 1 );
		void			drawChar( uint8 x, uint8 y, const void* pFont, char c, uint16_t color, uint8 size = 1 );

	private:

		GraphicsTft	m_tft;

		void		transformCoordinates( uint8* pX, uint8* pY );
	};
}