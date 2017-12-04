#include "tiki_st7735.h"
#include "tiki_st7735.inl"

namespace tiki
{
	ST7735::ST7735()
	{
		m_pCsPort	= nullptr;
		m_pDcPort	= nullptr;
		m_csPinMask	= 0u;
		m_dcPinMask	= 0u;
	}

	bool ST7735::initialize()
	{
		pinMode( s_displayCs, OUTPUT );
		pinMode( s_displayDc, OUTPUT );

#if TIKI_ENABLED( TIKI_AVR )
		m_pCsPort	= portOutputRegister( digitalPinToPort( s_displayCs ) );
		m_pDcPort	= portOutputRegister( digitalPinToPort( s_displayDc ) );
		m_csPinMask	= digitalPinToBitMask( s_displayCs );
		m_dcPinMask	= digitalPinToBitMask( s_displayDc );
#elif TIKI_ENABLED( TIKI_ARM_DUE )
		m_pCsPort	= digitalPinToPort( s_displayCs );
		m_pDcPort	= digitalPinToPort( s_displayDc );
		m_csPinMask	= digitalPinToBitMask( s_displayCs );
		m_dcPinMask	= digitalPinToBitMask( s_displayDc );
#endif

		SPI.begin();

		disableCs();
		enableDataStream();

		// reset
		pinMode( s_displayRst, OUTPUT );
		digitalWrite( s_displayRst, HIGH );
		delay(10);
		digitalWrite( s_displayRst, LOW );
		delay(10);
		digitalWrite( s_displayRst, HIGH );
		delay(10);

		// initialize chip
		startTransaction();

		//Software reset
		writeCommandFirst( CMD_SWRESET );
		delay( 122u ); // 500

		// Exit sleep
		writeCommand( CMD_SLPOUT );
		delay( 5u );

		// Frame Rate Control (In normal mode/Full colors)
		writeCommand( CMD_FRMCTR1 );
		writeData8First( TFT_ST7735_FRMCTR1[ 0u ] );
		writeData8( TFT_ST7735_FRMCTR1[ 1u ] );
		writeData8( TFT_ST7735_FRMCTR1[ 2u ] );

		writeCommandFirst( CMD_FRMCTR2 );
		writeData8First( TFT_ST7735_FRMCTR2[ 0u ] );
		writeData8( TFT_ST7735_FRMCTR2[ 1u ] );
		writeData8( TFT_ST7735_FRMCTR2[ 2u ] );

		writeCommandFirst( CMD_FRMCTR3 );
		writeData8First( TFT_ST7735_FRMCTR3[ 0u ] );
		writeData8( TFT_ST7735_FRMCTR3[ 1u ] );
		writeData8( TFT_ST7735_FRMCTR3[ 2u ] );

		writeCommandFirst( CMD_DINVCTR );
		writeData8First( TFT_ST7735_DINVCTR );

		// Power Control 1
		writeCommandFirst( CMD_PWCTR1 );
		writeData8First( TFT_ST7735_PWCTR1[ 0u ] );
		writeData8( TFT_ST7735_PWCTR1[ 1u ] );
		writeData8( TFT_ST7735_PWCTR1[ 2u ] );

		// Power Control 2
		writeCommandFirst( CMD_PWCTR2 );
		writeData8First( TFT_ST7735_PWCTR2[ 0u ] );

		writeCommandFirst( CMD_PWCTR3 );
		writeData8First( TFT_ST7735_PWCTR3[ 0u ] );
		writeData8( TFT_ST7735_PWCTR3[ 1u ] );

		writeCommandFirst( CMD_PWCTR4 );
		writeData8First( TFT_ST7735_PWCTR4[ 0u ] );
		writeData8( TFT_ST7735_PWCTR4[ 1u ] );

		writeCommandFirst( CMD_PWCTR5 );
		writeData8First( TFT_ST7735_PWCTR5[ 0u ] );
		writeData8( TFT_ST7735_PWCTR5[ 1u ] );

		//VCOM control 1 -------------------------
		writeCommandFirst( CMD_VCOMCTR1 );
		writeData8First( TFT_ST7735_VCOMCTR1[ 0u ] );
		writeData8( TFT_ST7735_VCOMCTR1[ 1u ] );

		writeCommandFirst( CMD_DINVOF );

		// How many bits per pixel are used?
		writeCommandFirst( CMD_PIXFMT );
		writeData8First( TFT_ST7735_PIXFMT );

		// Default gamma curve?
		writeCommandFirst( CMD_GAMMASET );
		writeData8First( TFT_ST7735_GAMMACURV );

		// Positive Gamma Correction Setting
		writeCommandFirst( CMD_PGAMMAC );
		writeData8First( TFT_POSITIV_GAMMASET[ 0u ] );
		for( uint8 i = 1u; i < 15u; ++i )
		{
			writeData8( TFT_POSITIV_GAMMASET[ i ] );
		}

		// Negative Gamma Correction Setting
		writeCommandFirst( CMD_NGAMMAC );
		writeData8First( TFT_NEGATIV_GAMMASET[ 0u ] );
		for( uint8 i = 1u; i < 15u; ++i )
		{
			writeData8( TFT_NEGATIV_GAMMASET[ i ] );
		}

		// Exit idle mode
		writeCommandFirst( CMD_IDLEOF );

		//Set Column Address
		writeCommand( CMD_CLMADRS );
		writeData16First( 0x0000u );
		writeData16( s_displayHeight );

		// Set Page Address
		writeCommandFirst( CMD_PGEADRS );
		writeData16First( 0x0000u );
		writeData16( s_displayWidth );

		// Normal Display ON
		writeCommandFirst( CMD_NORML );
		writeCommandLast( CMD_DISPON );
		delay( 1u );
		endTransaction();
		delay( 1u );

		// Set Rotation
		uint8 madControlData = 0b11000000;
		madControlData &= ~0xf8u; // clear bit 3..7,  F0 -> clear bit 4...7
		bitSet( madControlData, 6 );
		bitSet( madControlData, 5 );

		startTransaction();
		writeCommandFirst( CMD_MADCTL );
		enableDataStream();
		writeData8Last( madControlData );
		endTransaction();
		delay( 30u );

		clearScreen();

		return true;
	}

	void ST7735::clearScreen()
	{
		fillScreen( 0x0000u );
	}

	void ST7735::fillScreen( Color color )
	{
		startTransaction();

		setAddressRectangle( 0u, 0u, s_displayWidth, s_displayHeight );
		enableDataStream();

		for( uint16 i = 0u; i < s_displayPixelCount; ++i )
		{
			writeData16( color );
		}

		disableCs();
		endTransaction();
	}

	void ST7735::drawPixel( uint8 x, uint8 y, Color color)
	{
		startTransaction();

		setAddressRectangle( x, y, x + 1u, y + 1u );
		writeData16First( color );

		disableCs();
		endTransaction();
	}

	void ST7735::drawRectangle( uint8 x, uint8 y, uint8 width, uint8 height, Color color )
	{
		startTransaction();

		setAddressRectangle( x, y, (x + width) - 1u, (y + height) - 1u );
		enableDataStream();

		uint16 pixelCount = (uint16)width * (uint16)height;
		do
		{
			writeData16( color );
		}
		while( --pixelCount > 0u );

		disableCs();
		endTransaction();
	}

	void ST7735::drawImage( uint8 x, uint8 y, uint8 width, uint8 height, const Color* pPixels )
	{
		startTransaction();

		setAddressRectangle( x, y, (x + width) - 1u, (y + height) - 1u );
		enableDataStream();

		uint16 pixelCount = (uint16)width * (uint16)height;
		do
		{
			writeData16( *pPixels++ );
		}
		while( --pixelCount > 0u );

		disableCs();
		endTransaction();
	}

	void ST7735::drawImageProgramMemory( uint8 x, uint8 y, uint8 width, uint8 height, const Color* pPixels )
	{
		startTransaction();

		setAddressRectangle( x, y, (x + width) - 1u, (y + height) - 1u );
		enableDataStream();

		uint16 pixelCount = (uint16)width * (uint16)height;
		do
		{
			writeData16( pgm_read_word( pPixels ) );
			pPixels++;
		}
		while( --pixelCount > 0u );

		disableCs();
		endTransaction();
	}
}
