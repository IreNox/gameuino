#include "tiki_graphics.h"

namespace tiki
{
	static const uint8_t s_displayCs	= 6u;
	static const uint8_t s_displayDc	= 7u;
	static const uint8_t s_displayMosi	= 5u;
	static const uint8_t s_displaySclk	= 4u;
	static const uint8_t s_displayRst	= 8u;  // you can also connect this to the Arduino reset

	Graphics::Graphics()
		: m_tft( s_displayCs, s_displayDc, s_displayMosi, s_displaySclk, s_displayRst )
	{
	}

	void Graphics::initialize()
	{
		m_tft.initR();
		m_tft.writecommand( ST7735_DISPON );
	}
	
	void Graphics::fillScreen( uint16_t color )
	{
		m_tft.fillScreen( color );
	}
	
	void Graphics::drawPixel( uint8_t x, uint8_t y, uint16_t color )
	{
		transformCoordinates( &x, &y );
		m_tft.drawPixel( x, y, color );
	}

	void Graphics::drawLine( uint8_t x, uint8_t y, uint16_t color )
	{

	}

	void Graphics::drawRectangle( const Rectangle& rect, uint16_t color )
	{
		drawRectangle( rect.pos.x, rect.pos.y, rect.size.x, rect.size.y, color );
	}

	void Graphics::drawRectangle( uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color )
	{
		transformCoordinates( &x, &y );
		y -= width;

		m_tft.fillRect( x, y, height, width, color );
	}

	void Graphics::transformCoordinates( uint8_t* pX, uint8_t* pY )
	{
		const uint8_t x = *pX;
		*pX = *pY;
		*pY = ST7735::height - x;
	}
}
