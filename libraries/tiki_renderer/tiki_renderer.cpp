#include "tiki_renderer.h"

namespace tiki
{
	Renderer::Renderer()
	{
	}

	void Renderer::initialize( Graphics* pGraphics )
	{
		m_pGraphics = pGraphics;
	}

	void Renderer::render()
	{

	}

	void* Renderer::addSolidColorSprite( const Rectangle& rect, Color color, bool inFront /*= false*/ )
	{
		Sprite* pSprite = findFreeSprite( inFront );
		if( pSprite == nullptr )
		{
			return nullptr;
		}

		pSprite->type		= RendererSpriteType_SolidColor;
		pSprite->rect		= rect;
		pSprite->data.color	= color;

		return pSprite;
	}

	void* Renderer::addSolidImageSprite( const Rectangle& rect, const uint8* pImage, bool inFront /*= false*/ )
	{
		Sprite* pSprite = findFreeSprite( inFront );
		if( pSprite == nullptr )
		{
			return nullptr;
		}

		pSprite->type			= RendererSpriteType_SolidImage;
		pSprite->rect			= rect;
		pSprite->data.pImage	= pImage;

		return pSprite;
	}

	void Renderer::removeSprite( void* pSpriteVoid )
	{
		Sprite* pSprite = (Sprite*)pSpriteVoid;
		pSprite->type = RendererSpriteType_Invalid;
	}

	void Renderer::moveSprite( void* pSpriteVoid, const Point& pos )
	{

	}

	void Renderer::moveSprite( void* pSpriteVoid, const Rectangle& rect )
	{

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

	void Renderer::renderTile( uint16 tileIndex )
	{

	}
}
