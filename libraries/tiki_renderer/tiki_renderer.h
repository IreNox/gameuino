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
		void*	addSolidImageSprite( const Rectangle& rect, const uint8* pImage, uint8x2 imageOffset, bool inFront = false );
		void*	addSolidImageSprite( const Rectangle& rect, const uint8* pImage, uint8x2 imageOffset, uint8x2 imageSize, bool inFront = false );
		void	removeSprite( void* pSprite );

		void	moveSprite( void* pSprite, const Point& pos );
		void	moveSprite( void* pSprite, const Rectangle& rect );

	private:

		enum
		{
			MaxSpriteCount		= 32u,
			TileSize 			= 8u,

			TilesInWidth		= GraphicsScreenWidth / TileSize,
			TilesInHeight		= GraphicsScreenHeight / TileSize,
			TileCount			= TilesInWidth * TilesInHeight,
			TilesBytes			= TileCount / 8u,
			PixelsPerTile		= TileSize * TileSize,
			StencilBytesPerTile	= PixelsPerTile / 8u
		};

		struct SpriteColorData
		{
			Color			color;
		};

		struct SpriteImageData
		{
			const uint8*	pImage;
			uint8x2			imageOffset;
			uint8x2			imageSize;
		};

		struct SpriteTextData
		{
			const uint8*	pFont;
			const char*		pText;
		};

		union SpriteData
		{
			SpriteColorData		color;
			SpriteImageData		image;
			SpriteTextData		text;
		};

		struct Sprite
		{
			RendererSpriteType	type;
			BoundingRectangle	rect;
			SpriteData			data;
		};

		Graphics*	m_pGraphics;

		Sprite		m_sprites[ MaxSpriteCount ];

		uint8		m_dirtyTiles[ TilesBytes ];

		Color		m_pixels[ TileSize ][ TileSize ];
		uint8		m_stencil[ StencilBytesPerTile ];

		Sprite*		findFreeSprite( bool inFront );
		Sprite*		addSprite( RendererSpriteType type, const Rectangle& rect, bool inFront );

		void		invalidateTiles( const BoundingRectangle& rect );

		void		renderTile( uint16 tileIndex );
		void		renderTileSolidColor( const Sprite& sprite, const BoundingRectangle& tileRect );
		void		renderTileSolidImage( const Sprite& sprite, const BoundingRectangle& tileRect );
		void		renderTileTransparentImage( const Sprite& sprite, const BoundingRectangle& tileRect );
		void		renderTileText( const Sprite& sprite, const BoundingRectangle& tileRect );
	};
}
