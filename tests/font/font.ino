#include "tiki_graphics.h"
#include "tiki_assets.h"

#include "asset_data.h"

tiki::Assets assets;
tiki::Graphics graphics;

void setup()
{
	assets.initialize( tiki::s_assets, tiki::AssetName_Count );
	graphics.initialize();

	const void* pFont = assets.getAsset( tiki::AssetName_Font );
	const tiki::GraphicsFont& font = *(const tiki::GraphicsFont*)pFont;

	Serial.println( font.characterWidth );
	Serial.println( font.characterHeight );
	Serial.println( font.firstCharacter );
	Serial.println( font.lastCharacter );
	
	const uint16_t charCount = font.lastCharacter - font.firstCharacter;
	const uint16_t charSize = font.characterWidth * font.characterHeight;
	const uint16_t lengthBits = charCount * charSize;
	const uint16_t lengthBytes = lengthBits / 8u;

	Serial.println( lengthBits );
	
	const uint8_t* pSource = font.imageData;
	uint8_t bit = 0u;
	uint8_t x = 0u;
	uint8_t y = 0u;
	for( uint16_t i = 0u; i < lengthBits; ++i )
	{
		const uint8_t isSet = ((*pSource) >> bit) & 1u;

		bit++;
		if( bit == 8u )
		{
			pSource++;
			bit = 0u;
		}

		if( isSet )
		{
			graphics.drawPixel( x, y, tiki::GraphicsColorWhite );
		}

		x++;
		if( x == charSize )
		{
			x = 0u;
			y++;
		}
	}

	uint8_t y2 = 0u;
	for( uint8_t i = 1u; i < 5u; ++i )
	{
		graphics.drawText( 40, y2, pFont, "TEST", tiki::GraphicsColorWhite, i );
		y2 += (font.characterHeight * i) + 2u;
	}
}

void loop()
{
	delay( 1000 );
}

