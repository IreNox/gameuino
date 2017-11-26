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

		const void* pImage = m_assets.getAsset( AssetName_Blocks );
		m_graphics.drawImage( 5, 5, pImage );
	}

	void Tetris::loop()
	{
		const int frameStartTime = millis();

		m_input.update();

		const void* pImage = m_assets.getAsset( AssetName_Blocks );
		m_graphics.drawImage( 5, 15, pImage );
		
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
