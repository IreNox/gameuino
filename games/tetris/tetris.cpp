#include "tetris.h"

#include "asset_data.h"

namespace tiki
{
	struct Block
	{
		sint8x2	positions[ 4u ];
		Color	color;
	};

	static const Block s_blocks[] =
	{
		// BlockType_I
		{
			{
				{ 0u, -2u },
				{ 0u, -1u },
				{ 0u,  0u },
				{ 0u,  1u },
			},
			0x8f00
		},
		// BlockType_O
		{
			{
				{ -1u, 0u },
				{ -1u, 1u },
				{  0u, 0u },
				{  0u, 1u },
			},
			0x008f
		},
		// BlockType_T
		{
			{
				{  0u, 0u },
				{  0u, 1u },
				{ -1u, 1u },
				{  1u, 1u },
			},
			0x08f0
		},
		// BlockType_S
		{
			{
				{  0u, 0u },
				{  1u, 0u },
				{  0u, 1u },
				{ -1u, 1u },
			},
			0xf00f
		},
		// BlockType_Z
		{
			{
				{ -1u, 0u },
				{  0u, 0u },
				{  0u, 1u },
				{  1u, 1u },
			},
			0x0f0f
		},
		// BlockType_J
		{
			{
				{  0u, -1u },
				{  0u,  0u },
				{  0u,  1u },
				{ -1u,  1u },
			},
			0xf0f0
		},
		// BlockType_L
		{
			{
				{ 0u, -1u },
				{ 0u,  0u },
				{ 0u,  1u },
				{ 1u,  1u },
			},
			0x88ff
		}
	};

	void Tetris::initialize()
	{
		Serial.begin( 9600 );

		m_assets.initialize( s_assets, AssetName_Count );

		m_input.initialize();

		m_graphics.initialize();
		m_graphics.fillScreen( GraphicsColorBlack );

		m_renderer.initialize( &m_graphics );

		const uint8* pImage = m_assets.loadAsset( AssetName_Blocks );

		const uint8x2 wallImageOffset = { 35u, 0u };
		const uint8x2 wallImageSize = { 5u, 5u };
		m_pWall1 = m_renderer.addSolidImageSprite( Rectangle( 5u,    0u,  5u, 115u ), pImage, wallImageOffset, wallImageSize );
		m_pWall2 = m_renderer.addSolidImageSprite( Rectangle( 60u,   0u,  5u, 115u ), pImage, wallImageOffset, wallImageSize );
		m_pWall3 = m_renderer.addSolidImageSprite( Rectangle( 10u, 110u, 50u,   5u ), pImage, wallImageOffset, wallImageSize );

		m_pBlock1 = m_renderer.addSolidColorSprite( Rectangle( 0u, 0u, 5u, 5u ), 0x008f );
		m_pBlock2 = m_renderer.addSolidColorSprite( Rectangle( 0u, 0u, 5u, 5u ), 0x008f );
		m_pBlock3 = m_renderer.addSolidColorSprite( Rectangle( 0u, 0u, 5u, 5u ), 0x008f );
		m_pBlock4 = m_renderer.addSolidColorSprite( Rectangle( 0u, 0u, 5u, 5u ), 0x008f );

		//m_graphics.drawImage( 5, 5, pImage );
	}

	void Tetris::loop()
	{
		static uint8 y = 10u;
		const long frameStartTime = millis();

		m_input.update();

		const Point pos = { y, y };
		m_renderer.moveSprite( m_pBlock1, pos );
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
