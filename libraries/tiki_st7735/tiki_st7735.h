#pragma once

#include "tiki_core.h"

namespace tiki
{
	static const uint8 s_displayCs		= 53u;
	static const uint8 s_displayDc		= 9u;
	//static const uint8 s_displayMosi	= 51u;
	//static const uint8 s_displaySclk	= 52u;
	static const uint8 s_displayRst		= 8u;  // you can also connect this to the Arduino reset

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

		void					setArea( uint8 x0, uint8 y0, uint8 x1, uint8 y1 );
		void					setPartialArea( uint8 top, uint8 bottom );

		DisplayMode 			getMode();
		void					changeMode( DisplayMode mode);

		void					clearScreen();
		void					fillScreen( Color color );
		void					drawPixel( uint8 x, uint8 y, Color color);
		void					drawRectangle( uint8 x, uint8 y, uint8 width, uint8 height, Color color );

	private:

		rtype*					m_pDataPort;
		rtype*					m_pClkPort;
		rtype*					m_pCsPort;
		rtype*					m_pRsPort;

		ruint					m_dataPinMask;
		ruint					m_ClkPinMask;
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
		TIKI_FORCE_INLINE void	writeData8Last( uint8 data );
		TIKI_FORCE_INLINE void	writeData16Last( uint16 data );

	// /* ========================================================================
	// 						Helpers
	// ========================================================================*/

	// 	void 		setArcParams(float arcAngleMax, int arcAngleOffset);
	// 	float 		cosDeg_helper(float angle);
	// 	float 		sinDeg_helper(float angle);
	// 	void 		clearMemory(void);

	// 	#if defined(_ST7735_SIZEOPTIMIZER)
	// 		#if !defined(__MK20DX128__) && !defined(__MK20DX256__) && !defined(__MK64FX512__) && !defined(__MK66FX1M0__)
	// 			void 		writecommand_cont(const uint8_t c);
	// 			void 		writedata8_cont(uint8_t c);
	// 			void 		writedata16_cont(uint16_t d);
	// 			void 		writecommand_last(const uint8_t c);
	// 			void 		writedata8_last(uint8_t c);
	// 			void 		writedata16_last(uint16_t d);
	// 		#endif
	// 		void 		setAddrWindow_cont(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, bool disComp=false);
	// 		void 		drawFastHLine_cont(int16_t x, int16_t y, int16_t w, uint16_t color);
	// 		void 		drawFastVLine_cont(int16_t x, int16_t y, int16_t h, uint16_t color);
	// 		void 		drawPixel_cont(int16_t x, int16_t y, uint16_t color);
	// 		bool 		boundaryCheck(int16_t x,int16_t y);
	// 		int16_t 	sizeCheck(int16_t origin,int16_t len,int16_t maxVal);
	// 	#endif
	};
}
