#pragma once

#include "tiki_core.h"
#include "tiki_graphics.h"

namespace tiki
{
	enum RendererSpriteType : uint8
	{
		RendererSpriteType_Invalid,

		RendererSpriteType_SolidColor,
		RendererSpriteType_SolidImage,
		RendererSpriteType_TransparentImage,
		RendererSpriteType_Text,

		RendererSpriteType_Count
	};

	class Renderer
	{
	public:

				Renderer();

		void	initialize( Graphics* pGraphics );
		void	render();

		void*	addSolidColorSprite( const Rectangle& rect, Color color, bool inFront = false );
		void*	addSolidImageSprite( const Rectangle& rect, const uint8* pImage, bool inFront = false );
		void	removeSprite( void* pSprite );

		void	moveSprite( void* pSprite, const Point& pos );
		void	moveSprite( void* pSprite, const Rectangle& rect );

	private:

		enum
		{
			MaxSpriteCount		= 32u,
			TileSize 			= 16u,

			TilesInWidth		= GraphicsScreenWidth / TileSize,
			TilesInHeight		= GraphicsScreenHeight / TileSize,
			TileCount			= TilesInWidth * TilesInHeight,
			ChangedTilesBytes	= TileCount / 8u,
			PixelsPerTile		= TileSize * TileSize,
			StencilBytesPerTile	= PixelsPerTile / 8u
		};

		union SpriteData
		{
			Color			color;
			const uint8*	pImage;
			// TODO: text data
		};

		struct Sprite
		{
			RendererSpriteType	type;
			Rectangle			rect;
			SpriteData			data;
		};

		Graphics*	m_pGraphics;

		Sprite		m_sprites[ MaxSpriteCount ];

		uint8		m_changedTiles[ ChangedTilesBytes ];

		Color		m_pixels[ PixelsPerTile ];
		uint8		m_stencil[ StencilBytesPerTile ];

		Sprite*		findFreeSprite( bool inFront );

		void		renderTile( uint16 tileIndex );
	};
}
