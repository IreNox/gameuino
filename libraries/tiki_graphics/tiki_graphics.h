#pragma once

#include "tiki_core.h"

#include <Arduino.h>
#include <ST7735.h>

namespace tiki
{
	enum
	{
		GraphicsScreenWidth		= ST7735::height,
		GraphicsScreenHeight	= ST7735::width,

		GraphicsColorBlack		= 0x0000u,
		GraphicsColorWhite		= 0xffffu,
	};

	class Graphics
	{
	public:

				Graphics();

		void	initialize();

		ST7735&	getTft() { return m_tft; }

		void	fillScreen( uint16_t color );
		void	drawPixel( uint8_t x, uint8_t y, uint16_t color );
		void	drawLine( uint8_t x, uint8_t y, uint16_t color );
		void	drawRectangle( const Rectangle& rect, uint16_t color );
		void	drawRectangle( uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color );
		
	private:

		ST7735	m_tft;

		void	transformCoordinates( uint8_t* pX, uint8_t* pY );
	};
}