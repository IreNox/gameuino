#include "tiki_graphics.h"

namespace tiki
{
	Graphics::Graphics()
	{
	}

	void Graphics::initialize()
	{
		m_tft.initialize();
	}

	void Graphics::fillScreen( uint16_t color )
	{
		m_tft.fillScreen( color );
	}

	void Graphics::drawPixel( uint8 x, uint8 y, uint16_t color )
	{
		m_tft.drawPixel( x, y, color );
	}

	void Graphics::drawRectangle( const Rectangle& rect, uint16_t color )
	{
		drawRectangle( rect.pos.x, rect.pos.y, rect.size.x, rect.size.y, color );
	}

	void Graphics::drawRectangle( uint8 x, uint8 y, uint8 width, uint8 height, uint16_t color )
	{
		m_tft.drawRectangle( x, y, width, height, color );
	}

	void Graphics::drawImage( uint8 x, uint8 y, const uint8* pImage )
	{
		const GraphicsImage* pGraphicsImage = (const GraphicsImage*)pImage;
		m_tft.drawImage( x, y, pGraphicsImage->width, pGraphicsImage->height, (const Color*)pGraphicsImage->imageData );
	}

	void Graphics::drawImageProgramMemory( uint8 x, uint8 y, const uint8* pImage )
	{
		const uint16 imageValues = pgm_read_word( pImage );
		const uint8 width = imageValues;
		const uint8 height = imageValues >> 8u;

		m_tft.drawImageProgramMemory( x, y, width, height, (const Color*)(pImage + 3u) );
	}

	void Graphics::drawTexture( uint8 x, uint8 y, uint8 width, uint8 height, const Color* pPixels )
	{
		m_tft.drawImage( x, y, width, height, pPixels );
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
			else if( c == ' ' )
			{
				x += (font.characterWidth * size) + spacing;
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
}
