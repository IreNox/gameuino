#include "tetris.h"

#include "asset_data.h"

namespace tiki
{
	void Tetris::initialize()
	{
		Serial.begin( 9600 );

		m_assets.initialize( s_assets, AssetName_Count );

		m_input.initialize();

		m_graphics.initialize();
		m_graphics.fillScreen( GraphicsColorBlack );

		const void* pImage = m_assets.loadAsset( AssetName_Blocks );
		m_graphics.drawImage( 5, 5, pImage );

		for( uint16 i = 0u; i < 16*17; ++i )
		{
			const uint16 x = i % 16;
			const uint16 y = i / 16;

			const uint16_t r = x * 16;
			const uint16_t g = ((x + y) / 2) * 16;
			const uint16_t b = y * 16;

			const uint16_t r5 = ((r >> 3) & 0x1f) << 11;
			const uint16_t g6 = ((g >> 2) & 0x3f) << 5;
			const uint16_t b5 = ((b >> 3) & 0x1f);
			const uint16_t c = 0x008f; //r5 | g6 | b5;

			test[ i ] = c;
		}
	}

	void Tetris::loop()
	{
		const int frameStartTime = millis();

		m_input.update();

		const uint8* pImage = m_assets.getAsset( AssetName_Blocks );
		m_graphics.drawImageProgramMemory( 5, 15, pImage );

		//test[ 0u ] = 0x8f00u;

		for( uint8 y = 0u; y < 128 / 16; ++y )
		{
			for( uint8 x = 0u; x < 160 / 16; ++x )
			{
				//m_graphics.drawTexture( x * 16, y * 16, 16, 16, test );
			}
		}

		//m_graphics.drawRectangle( 50, 50, 50, 50, 0x8f00 );

		const int frameEndTime = millis();
		const int elapsedTime = frameEndTime - frameStartTime;
		Serial.println( elapsedTime );
		if( elapsedTime < 16 )
		{
			delay( 16 - elapsedTime );
		}
		else
		{
			Serial.println( "Frame time exeeded!" );
		}
	}
}
