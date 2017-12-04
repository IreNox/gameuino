#pragma once

#include "tiki_core.h"

namespace tiki
{
	static const uint8 s_displayCs			= 53u;
	static const uint8 s_displayDc			= 9u;
	//static const uint8 s_displayMosi		= 51u;
	//static const uint8 s_displaySclk		= 52u;
	static const uint8 s_displayRst			= 8u;  // you can also connect this to the Arduino reset

	static const uint8 s_displayWidth		= 160u;
	static const uint8 s_displayHeight		= 128u;
	static const uint16 s_displayPixelCount	= s_displayWidth * s_displayHeight;

	enum DisplayMode
	{
		DisplayMode_Default,
		DisplayMode_Partial,
		DisplayMode_Idle,
		DisplayMode_Sleep,
		DisplayMode_Invert,
		DisplayMode_On,
		DisplayMode_Off
	};

	typedef uint16 Color;

	class ST7735
	{
	public:

								ST7735();

		bool   			  		initialize();

		void					clearScreen();
		void					fillScreen( Color color );
		void					drawPixel( uint8 x, uint8 y, Color color );
		void					drawRectangle( uint8 x, uint8 y, uint8 width, uint8 height, Color color );
		void					drawImage( uint8 x, uint8 y, uint8 width, uint8 height, const Color* pPixels );
		void					drawImageProgramMemory( uint8 x, uint8 y, uint8 width, uint8 height, const Color* pPixels );

	private:

		rtype*					m_pCsPort;
		rtype*					m_pDcPort;
		ruint					m_csPinMask;
		ruint					m_dcPinMask;

		TIKI_FORCE_INLINE void 	spiWrite8( uint8 data );
		TIKI_FORCE_INLINE void	spiWrite16( uint16 data );

		TIKI_FORCE_INLINE void	enableCommandStream();
		TIKI_FORCE_INLINE void	enableDataStream();

		TIKI_FORCE_INLINE void	startTransaction();
		TIKI_FORCE_INLINE void	endTransaction();

		TIKI_FORCE_INLINE void	disableCs();

		TIKI_FORCE_INLINE void	writeCommandFirst( uint8 command );
		TIKI_FORCE_INLINE void	writeCommand( uint8 command );
		TIKI_FORCE_INLINE void	writeCommandLast( uint8 command );
		TIKI_FORCE_INLINE void	writeData8First( uint8 data );
		TIKI_FORCE_INLINE void	writeData16First( uint16 data );
		TIKI_FORCE_INLINE void	writeData8( uint8 data );
		TIKI_FORCE_INLINE void	writeData16( uint16 data );
		TIKI_FORCE_INLINE void	writeDataArray8( const uint8* pData, uint8 length );
		TIKI_FORCE_INLINE void	writeDataArray16( const uint16* pData, uint16 length );
		TIKI_FORCE_INLINE void	writeData8Last( uint8 data );
		TIKI_FORCE_INLINE void	writeData16Last( uint16 data );

		TIKI_FORCE_INLINE void	setAddressRectangle( uint8 x0, uint8 y0, uint8 x1, uint8 y1 );
	};
}
