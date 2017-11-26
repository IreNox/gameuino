#include "tiki_graphics.h"

namespace tiki
{
	static const uint8 s_displayCs	= 6u;
	static const uint8 s_displayDc	= 7u;
	static const uint8 s_displayMosi	= 5u;
	static const uint8 s_displaySclk	= 4u;
	static const uint8 s_displayRst	= 8u;  // you can also connect this to the Arduino reset

	Graphics::Graphics()
		: m_tft( s_displayCs, s_displayDc, s_displayMosi, s_displaySclk, s_displayRst )
	{
	}

	void Graphics::initialize()
	{
		m_tft.initR();
		m_tft.writecommand( ST7735_DISPON );
	}
	
	void Graphics::fillScreen( uint16_t color )
	{
		m_tft.fillScreen( color );
	}
	
	void Graphics::drawPixel( uint8 x, uint8 y, uint16_t color )
	{
		transformCoordinates( &x, &y );
		m_tft.drawPixel( x, y, color );
	}

	void Graphics::drawLine( uint8 x, uint8 y, uint16_t color )
	{

	}

	void Graphics::drawRectangle( const Rectangle& rect, uint16_t color )
	{
		drawRectangle( rect.pos.x, rect.pos.y, rect.size.x, rect.size.y, color );
	}

	void Graphics::drawRectangle( uint8 x, uint8 y, uint8 width, uint8 height, uint16_t color )
	{
		transformCoordinates( &x, &y );
		y -= width;

		m_tft.fillRect( x, y, height, width, color );
	}

	void Graphics::drawText( uint8 x, uint8 y, const void* pFont, const char* pText, uint16_t color, uint8 size /*= 1*/ )
	{
		const GraphicsFont& font = *(const GraphicsFont*)pFont;

		const uint8 startX	= x;
		const uint8 spacing	= (font.characterWidth * size) / 2u;

		uint8 index = 0u;
		while( pText[ index ] != '\0' )
		{
			const char c = pText[ index ];
			index++;

			if( c == '\n' )
			{
				x = startX;
				y += (font.characterHeight * size) + spacing;
				continue;
			}

			drawChar( x, y, pFont, c, color, size );
			x += (font.characterWidth * size) + spacing;
		}
	}

	void Graphics::drawChar( uint8 x, uint8 y, const void* pFont, char c, uint16_t color, uint8 size /*= 1*/ )
	{
		const GraphicsFont& font = *(const GraphicsFont*)pFont;
		const uint16 charBitSize = (font.characterWidth * font.characterHeight);

		const uint8 charIndex = c - font.firstCharacter;
		const uint16 charBitOffset = charIndex * charBitSize;

		const uint8* pCharSource = font.imageData + (charBitOffset / 8);		
		uint8 charBit = charBitOffset % 8u;

		for( uint8 charY = 0u; charY < font.characterHeight; ++charY )
		{
			for( uint8 charX = 0u; charX < font.characterWidth; ++charX )
			{
				const uint8 isSet = ((*pCharSource) >> charBit) & 1u;

				charBit++;
				if( charBit == 8u )
				{
					pCharSource++;
					charBit = 0u;
				}

				if( isSet )
				{
					const uint8 pointX = x + (charX * size);
					const uint8 pointY = y + (charY * size);
					drawRectangle( pointX, pointY, size, size, color );
				}
			}
		}
	}

	void Graphics::transformCoordinates( uint8* pX, uint8* pY )
	{
		const uint8 x = *pX;
		*pX = *pY;
		*pY = ST7735::height - x;
	}
}
