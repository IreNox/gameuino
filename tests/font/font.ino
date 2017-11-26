#include "tiki_graphics.hpp"
#include "tiki_assets.hpp"

void setup()
{
	const GraphicsFont& font = *(const GraphicsFont*)pFont;

	Serial.println( font.characterWidth );
	Serial.println( font.characterHeight );
	Serial.println( font.firstCharacter );
	Serial.println( font.lastCharacter );
	
	const uint16 charCount = font.lastCharacter - font.firstCharacter;
	const uint16 charSize = font.characterWidth * font.characterHeight;
	const uint16 lengthBits = charCount * charSize;
	const uint16 lengthBytes = lengthBits / 8u;

	Serial.println( lengthBits );
	
	const uint8* pSource = font.imageData;
	uint8 bit = 0u;
	uint8 x = 0u;
	uint8 y = 0u;
	for( uint16 i = 0u; i < lengthBits; ++i )
	{
		const uint8 isSet = ((*pSource) >> bit) & 1u;

		bit++;
		if( bit == 8u )
		{
			pSource++;
			bit = 0u;
		}

		if( isSet )
		{
			m_graphics.drawPixel( x, y, GraphicsColorWhite );
		}

		x++;
		if( x == charSize )
		{
			x = 0u;
			y++;
		}
	}
}
