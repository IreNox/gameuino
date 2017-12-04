#include "tiki_renderer.h"

namespace tiki
{
	static bool checkBoundingRectangleIntersection( const BoundingRectangle& lhs, const BoundingRectangle& rhs )
	{
		return !(rhs.min.x > lhs.max.x ||
				rhs.max.x < lhs.min.x ||
				rhs.min.y > lhs.max.y ||
				rhs.max.y < lhs.min.y);
	}

	Renderer::Renderer()
	{
	}

	void Renderer::initialize( Graphics* pGraphics )
	{
		m_pGraphics = pGraphics;

		memset( m_sprites, 0u, sizeof( m_sprites ) );
		memset( m_dirtyTiles, 0u, sizeof( m_dirtyTiles ) );
	}

	void Renderer::render()
	{
		uint8 bitMask = 0x1u;
		uint8* pByte = m_dirtyTiles;
		for( uint16 tileIndex = 0u; tileIndex < TileCount; ++tileIndex )
		{
			const bool isDirty = ((*pByte) & bitMask);
			if( isDirty )
			{
				renderTile( tileIndex );
			}

			bitMask = (bitMask << 1u);
			if( bitMask == 0x0u )
			{
				bitMask = 0x1u;
				*pByte = 0u;
				pByte++;
			}
		}
		TIKI_ASSERT( pByte == (m_dirtyTiles + TilesBytes) );
	}

	void* Renderer::addSolidColorSprite( const Rectangle& rect, Color color, bool inFront /*= false*/ )
	{
		Sprite* pSprite = addSprite( RendererSpriteType_SolidColor, rect, inFront );
		if( pSprite == nullptr )
		{
			return nullptr;
		}

		pSprite->data.color.color = color;

		return pSprite;
	}

	void* Renderer::addSolidImageSprite( const Rectangle& rect, const uint8* pImage, bool inFront /*= false*/ )
	{
		const uint8x2 imageOffset = { 0u, 0u };
		return addSolidImageSprite( rect, pImage, imageOffset, inFront );
	}

	void* Renderer::addSolidImageSprite( const Rectangle& rect, const uint8* pImage, uint8x2 imageOffset, bool inFront /*= false*/ )
	{
		const GraphicsImage* pGraphicsImage = (const GraphicsImage*)pImage;
		const uint8x2 imageSize = { pGraphicsImage->width, pGraphicsImage->width };
		return addSolidImageSprite( rect, pImage, imageOffset, imageSize, inFront );
	}

	void* Renderer::addSolidImageSprite( const Rectangle& rect, const uint8* pImage, uint8x2 imageOffset, uint8x2 imageSize, bool inFront /*= false*/ )
	{
		Sprite* pSprite = addSprite( RendererSpriteType_SolidImage, rect, inFront );
		if( pSprite == nullptr )
		{
			return nullptr;
		}

		pSprite->data.image.pImage		= pImage;
		pSprite->data.image.imageOffset	= imageOffset;
		pSprite->data.image.imageSize	= imageSize;

		return pSprite;
	}

	void Renderer::removeSprite( void* pSpriteVoid )
	{
		Sprite* pSprite = (Sprite*)pSpriteVoid;

		invalidateTiles( pSprite->rect );

		pSprite->type = RendererSpriteType_Invalid;
	}

	void Renderer::moveSprite( void* pSpriteVoid, const Point& pos )
	{
		Sprite* pSprite = (Sprite*)pSpriteVoid;

		if( pos.x == pSprite->rect.min.x &&
			pos.y == pSprite->rect.min.y )
		{
			return;
		}

		invalidateTiles( pSprite->rect );

		pSprite->rect.max.x	= (pSprite->rect.max.x - pSprite->rect.min.x) + pos.x;
		pSprite->rect.max.y	= (pSprite->rect.max.y - pSprite->rect.min.y) + pos.y;
		pSprite->rect.min = pos;

		invalidateTiles( pSprite->rect );
	}

	void Renderer::moveSprite( void* pSpriteVoid, const Rectangle& rect )
	{
		Sprite* pSprite = (Sprite*)pSpriteVoid;

		invalidateTiles( pSprite->rect );

		pSprite->rect.min	= rect.pos;
		pSprite->rect.max.x	= rect.pos.x + rect.size.x;
		pSprite->rect.max.y	= rect.pos.x + rect.size.y;

		invalidateTiles( pSprite->rect );
	}

	Renderer::Sprite* Renderer::findFreeSprite( bool inFront )
	{
		if( inFront )
		{
			for( uint8 i = MaxSpriteCount - 1u; i < MaxSpriteCount; --i )
			{
				if( m_sprites[ i ].type != RendererSpriteType_Invalid )
				{
					continue;
				}

				return &m_sprites[ i ];
			}
		}
		else
		{
			for( uint8 i = 0u; i < MaxSpriteCount; ++i )
			{
				if( m_sprites[ i ].type != RendererSpriteType_Invalid )
				{
					continue;
				}

				return &m_sprites[ i ];
			}
		}

		TIKI_TRACE( "[renderer] No free sprite." );
		return nullptr;
	}

	Renderer::Sprite* Renderer::addSprite( RendererSpriteType type, const Rectangle& rect, bool inFront )
	{
		Sprite* pSprite = findFreeSprite( inFront );
		if( pSprite == nullptr )
		{
			return nullptr;
		}

		pSprite->type		= type;
		pSprite->rect.min	= rect.pos;
		pSprite->rect.max.x	= rect.pos.x + rect.size.x - 1u;
		pSprite->rect.max.y	= rect.pos.y + rect.size.y - 1u;

		//Serial.print( "r: " );
		//Serial.print( rect.pos.x );
		//Serial.print( ":" );
		//Serial.print( rect.pos.y );
		//Serial.print( "-" );
		//Serial.print( rect.size.x );
		//Serial.print( ":" );
		//Serial.println( rect.size.y );

		invalidateTiles( pSprite->rect );

		return pSprite;
	}

	void Renderer::invalidateTiles( const BoundingRectangle& rect )
	{
		const uint8 firstTileX		= rect.min.x / TileSize;
		const uint8 lastTileX		= rect.max.x / TileSize;
		const uint8 firstTileY		= rect.min.y / TileSize;
		const uint8 lastTileY		= rect.max.y / TileSize;

		//Serial.print( "r: " );
		//Serial.print( rect.min.x );
		//Serial.print( "-" );
		//Serial.print( rect.max.x );
		//Serial.print( ":" );
		//Serial.print( rect.min.y );
		//Serial.print( "-" );
		//Serial.println( rect.max.y );

		//Serial.print( "t: " );
		//Serial.print( firstTileX );
		//Serial.print( "-");
		//Serial.print( lastTileX );
		//Serial.print( ":" );
		//Serial.print( firstTileY );
		//Serial.print( "-" );
		//Serial.println( lastTileY );

		for( uint8 y = firstTileY; y <= lastTileY; ++y )
		{
			for( uint8 x = firstTileX; x <= lastTileX; ++x )
			{
				const uint16 bitIndex	= (y * TilesInWidth) + x;
				const uint8 byteIndex	= bitIndex / 8u;
				const uint8 byteBit		= bitIndex % 8u;

				//Serial.print( "d: " );
				//Serial.print( x );
				//Serial.print( ":");
				//Serial.print( y );
				//Serial.print( " - bit: " );
				//Serial.print( bitIndex );
				//Serial.print( " - byte: " );
				//Serial.print( byteIndex );
				//Serial.print( " - mask: " );
				//Serial.println( byteBit );

				m_dirtyTiles[ byteIndex ] |= 1u << byteBit;
			}
		}
	}

	void Renderer::renderTile( uint16 tileIndex )
	{
		const uint8 x = tileIndex % TilesInWidth;
		const uint8 y = tileIndex / TilesInWidth;

		BoundingRectangle tileRect;
		tileRect.min.x	= x * TileSize;
		tileRect.min.y	= y * TileSize;
		tileRect.max.x	= tileRect.min.x + TileSize - 1u;
		tileRect.max.y	= tileRect.min.y + TileSize - 1u;

		memset( m_pixels, 0xffu, sizeof( m_pixels ) );
		memset( m_stencil, 0u, sizeof( m_stencil ) );

		//for( uint16 i = 0u; i < PixelsPerTile; ++i )
		//{
		//	m_pixels[ 0u ][ i ] = 0x8f00u;
		//}

		for( uint8 spriteIndex = MaxSpriteCount - 1u; spriteIndex < MaxSpriteCount; --spriteIndex )
		{
			const Sprite& sprite = m_sprites[ spriteIndex ];
			if( sprite.type == RendererSpriteType_Invalid ||
				!checkBoundingRectangleIntersection( tileRect, sprite.rect ) )
			{
				continue;
			}

			switch( sprite.type )
			{
				case RendererSpriteType_SolidColor:
					renderTileSolidColor( sprite, tileRect );
					break;

				case RendererSpriteType_SolidImage:
					renderTileSolidImage( sprite, tileRect );
					break;

				case RendererSpriteType_TransparentImage:
					renderTileTransparentImage( sprite, tileRect );
					break;

				case RendererSpriteType_Text:
					renderTileText( sprite, tileRect );
					break;

				default:
					break;
			}
		}

		m_pGraphics->drawTexture( tileRect.min.x, tileRect.min.y, TileSize, TileSize, m_pixels[ 0u ] );
	}

	void Renderer::renderTileSolidColor( const Sprite& sprite, const BoundingRectangle& tileRect )
	{
		const uint8 beginX		= max( tileRect.min.x, sprite.rect.min.x ) - tileRect.min.x;
		const uint8 beginY		= max( tileRect.min.y, sprite.rect.min.y ) - tileRect.min.y;
		const uint8 endX		= min( tileRect.max.x, sprite.rect.max.x ) - tileRect.min.x;
		const uint8 endY		= min( tileRect.max.y, sprite.rect.max.y ) - tileRect.min.y;

		uint8 x = beginX;
		uint8 y = beginY;
		while( true )
		{
			m_pixels[ y ][ x ] = sprite.data.color.color;

			x++;
			if( x > endX )
			{
				x = beginX;
				y++;
				if( y > endY )
				{
					break;
				}
			}
		}
		TIKI_ASSERT( x <= TileSize );
		TIKI_ASSERT( y <= TileSize );
	}

	void Renderer::renderTileSolidImage( const Sprite& sprite, const BoundingRectangle& tileRect )
	{
		const uint8 beginX		= max( tileRect.min.x, sprite.rect.min.x ) - tileRect.min.x;
		const uint8 beginY		= max( tileRect.min.y, sprite.rect.min.y ) - tileRect.min.y;
		const uint8 endX		= min( tileRect.max.x, sprite.rect.max.x ) - tileRect.min.x;
		const uint8 endY		= min( tileRect.max.y, sprite.rect.max.y ) - tileRect.min.y;

		const sint16 imageBeginX	= (sint16)tileRect.min.x - sprite.rect.min.x;
		const sint16 imageBeginY	= (sint16)tileRect.min.y - sprite.rect.min.y;

		const GraphicsImage* pImage = (const GraphicsImage*)sprite.data.image.pImage;
		const Color* pPixels = (const Color*)pImage->imageData;

		uint8 x = beginX;
		uint8 y = beginY;
		while( true )
		{
			const sint16 imageX	= (max( imageBeginX + x, 0 ) % sprite.data.image.imageSize.x) + sprite.data.image.imageOffset.x;
			const sint16 imageY	= (max( imageBeginY + y, 0 ) % sprite.data.image.imageSize.y) + sprite.data.image.imageOffset.y;
			const uint8 imageIndex = (imageY * pImage->width) + imageX;

			m_pixels[ y ][ x ] = pPixels[ imageIndex ];

			x++;
			if( x > endX )
			{
				x = beginX;
				y++;
				if( y > endY )
				{
					break;
				}
			}
		}
		TIKI_ASSERT( x <= TileSize );
		TIKI_ASSERT( y <= TileSize );
	}

	void Renderer::renderTileTransparentImage( const Sprite& sprite, const BoundingRectangle& tileRect )
	{
		const GraphicsImage* pImage = (const GraphicsImage*)sprite.data.image.pImage;
		const Color* pPixels = (const Color*)pImage->imageData;

		for( uint16 i = 0u; i < PixelsPerTile; ++i )
		{
			m_pixels[ 0u ][ i ] = pPixels[ i ];
		}
	}

	void Renderer::renderTileText( const Sprite& sprite, const BoundingRectangle& tileRect )
	{
		for( uint16 i = 0u; i < PixelsPerTile; ++i )
		{
			m_pixels[ 0u ][ i ] = 0x8f00u;
		}
	}
}
