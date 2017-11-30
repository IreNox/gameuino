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

		m_renderer.initialize( &m_graphics );

		const uint8* pImage = m_assets.loadAsset( AssetName_Blocks );

		m_pSprite1 = m_renderer.addSolidColorSprite( Rectangle( 5, 5, 20, 20 ), 0x008f );
		//m_pSprite2 = m_renderer.addSolidImageSprite( Rectangle( 50, 50, 20, 5 ), pImage );
		m_pSprite3 = m_pSprite1;

		//m_graphics.drawImage( 5, 5, pImage );
	}

	void Tetris::loop()
	{
		static uint8 y = 10u;
		const long frameStartTime = millis();

		m_input.update();

		const Point pos = { y, y };
		m_renderer.moveSprite( m_pSprite1, pos );
		y += 5u;
		if( y == 100u )
		{
			y = 5u;
		}

		m_renderer.render();

		//const uint8* pImage = m_assets.getAsset( AssetName_Blocks );
		//m_graphics.drawImageProgramMemory( 5, 15, pImage );

		const long frameEndTime = millis();
		const long elapsedTime = frameEndTime - frameStartTime;
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
