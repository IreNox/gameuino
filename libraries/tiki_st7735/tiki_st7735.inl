#pragma once

#include <SPI.h>

namespace tiki
{
	// ST7735 commands
	static const uint8 CMD_NOP     	= 0x00; // Non operation
	static const uint8 CMD_SWRESET 	= 0x01; // Soft Reset
	static const uint8 CMD_SLPIN   	= 0x10; // Sleep ON
	static const uint8 CMD_SLPOUT  	= 0x11; // Sleep OFF
	static const uint8 CMD_PTLON   	= 0x12; // Partial Mode ON
	static const uint8 CMD_NORML   	= 0x13; // Normal Display ON								_CMD_NORON
	static const uint8 CMD_DINVOF  	= 0x20; // Display Inversion OFF							_CMD_INVOFF
	static const uint8 CMD_DINVON   = 0x21; // Display Inversion ON								_CMD_INVON
	static const uint8 CMD_GAMMASET = 0x26; // Gamma Set (0x01[1],0x02[2],0x04[3],0x08[4])
	static const uint8 CMD_DISPOFF 	= 0x28; // Display OFF
	static const uint8 CMD_DISPON  	= 0x29; // Display ON
	static const uint8 CMD_IDLEON  	= 0x39; // Idle Mode ON										_CMD_IDLEON
	static const uint8 CMD_IDLEOF  	= 0x38; // Idle Mode OFF									_CMD_IDLEOFF
	static const uint8 CMD_CLMADRS	= 0x2A; // Column Address Set								_CMD_CASET
	static const uint8 CMD_PGEADRS	= 0x2B; // Page Address Set									_CMD_PASET

	static const uint8 CMD_RAMWR   	= 0x2C; // Memory Write
	static const uint8 CMD_RAMRD   	= 0x2E; // Memory Read

	static const uint8 CMD_PARTAREA	= 0x30; // Partial Area										_CMD_PTLAR
	static const uint8 CMD_VSCLLDEF	= 0x33; // Vertical Scroll Definition						_CMD_VSCRLLD
	static const uint8 CMD_TEFXLON	= 0x35; // Tearing Effect Line ON							_CMD_TEFXON
	static const uint8 CMD_TEFXLOF	= 0x34; // Tearing Effect Line OFF							_CMD_TEFXOFF
	static const uint8 CMD_MADCTL  	= 0x36; // Memory Access Control
	static const uint8 CMD_VSSTADRS	= 0x37; // Vertical Scrolling Start address					_CMD_VSCLLSA
	static const uint8 CMD_PIXFMT  	= 0x3A; // Interface Pixel Format

	static const uint8 CMD_FRMCTR1 	= 0xB1; // Frame Rate Control (In normal mode/Full colors)
	static const uint8 CMD_FRMCTR2 	= 0xB2; // Frame Rate Control(In Idle mode/8-colors)
	static const uint8 CMD_FRMCTR3 	= 0xB3; // Frame Rate Control(In Partial mode/full colors)
	static const uint8 CMD_DINVCTR	= 0xB4; // Display Inversion Control						_CMD_INVCTR
	static const uint8 CMD_DFUNCTR 	= 0xB6; // Display Fuction set 5

	static const uint8 CMD_PWCTR1  	= 0xC0; // Power_Control1
	static const uint8 CMD_PWCTR2  	= 0xC1; // Power_Control2
	static const uint8 CMD_PWCTR3  	= 0xC2; // Power_Control3
	static const uint8 CMD_PWCTR4  	= 0xC3; // Power_Control4
	static const uint8 CMD_PWCTR5  	= 0xC4; // Power_Control5
	static const uint8 CMD_PWCTR6  	= 0xFC; // Power_Control6
	static const uint8 CMD_VCOMCTR1	= 0xC5; // VCOM_Control 1									_CMD_VMCTR1
	static const uint8 CMD_VCOMCTR2	= 0xC7; // VCOM_Control 2									_CMD_VMCTR2
	static const uint8 CMD_PGAMMAC	= 0xE0; // Positive Gamma Correction Setting				_CMD_POSGAMUT
	static const uint8 CMD_NGAMMAC	= 0xE1; // Negative Gamma Correction Setting				_CMD_NEGGAMUT

	static const uint8 TFT_ST7735_FRMCTR1[ 3u ]		= { 0x00, 0x06, 0x03 };	// Frame Rate Control_1 (In normal mode/Full colors) 0x00, 0x06, 0x03 - 0x01, 0x2C, 0x2D
	static const uint8 TFT_ST7735_FRMCTR2[ 3u ]		= { 0x01, 0x2C, 0x2D };	// Frame Rate Control_2 (Idle mode/8 Bits)
	static const uint8 TFT_ST7735_FRMCTR3[ 3u ]		= { 0x01, 0x2C, 0x2D };	// Frame Rate Control_3
	static const uint8 TFT_ST7735_DINVCTR			= 0x00;					// (0x00 or 0x07)

	// Power settings
	static const uint8 TFT_ST7735_PWCTR1[ 3u ]		= { 0xA2, 0x02, 0x84 };	// Set the GVDD and voltage
	static const uint8 TFT_ST7735_PWCTR2[ 1u ]		= { 0xC5 };
	static const uint8 TFT_ST7735_PWCTR3[ 2u ]		= { 0x0A, 0x00 };		// Set the amount of current in Operation amplifier in normal mode/full colors.
	static const uint8 TFT_ST7735_PWCTR4[ 2u ]		= { 0x8A, 0x2A };		// Set the amount of current in Operational amplifier in Idle mode/8-colors
	static const uint8 TFT_ST7735_PWCTR5[ 2u ]		= { 0x8A, 0x2A };		// Set the amount of current in Operational amplifier in Partial mode/full-colors
	static const uint8 TFT_ST7735_VCOMCTR1[ 2u ]	= { 0x3C, 0x38 };		// Set VCOMH Voltage

	static const uint8 TFT_ST7735_PIXFMT			= 0x05;					// Defines how many bits per pixel are used in the interface
	static const uint8 TFT_ST7735_GAMMACURV			= 0x01;					// Selects the gamma curve used by the display device (0x01[1],0x02[2],0x04[3],0x08[4]) [alt 0x04] default gamma curve

	static const uint8 TFT_POSITIV_GAMMASET[ 15u ]	= { 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00 };
	static const uint8 TFT_NEGATIV_GAMMASET[ 15u ]	= { 0x00, 0x0E, 0x14, 0x07, 0x11, 0x07, 0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F };

	// SPI Settings
#if TIKI_ENABLED( TIKI_AVR )
	static const uint32 TFT_ST7735_SPI_SPEED 		= 8000000;
#elif TIKI_ENABLED( TIKI_ARM_DUE )
	static const uint32 TFT_ST7735_SPI_SPEED 		= 24000000;
#else
#	error "Platform not supported"
#endif
	static const SPISettings TFT_ST7735_SPI			= SPISettings( TFT_ST7735_SPI_SPEED, MSBFIRST, SPI_MODE0 );

	void TIKI_FORCE_INLINE ST7735::spiWrite8( uint8 data )
	{
#if TIKI_ENABLED( TIKI_AVR )
		SPDR = data;					// load your outgoing data into the SPI shift reg's data register
		while( !(SPSR & _BV(SPIF)) );	// wait for the data to be transmitted on MOSI
#elif TIKI_ENABLED( TIKI_ARM_DUE )
		SPI.transfer( data );
#endif
	}

	TIKI_FORCE_INLINE void ST7735::spiWrite16( uint16 data )
	{
#if TIKI_ENABLED( TIKI_AVR )
		spiWrite8( data >> 8);
		spiWrite8( data );
#elif TIKI_ENABLED( TIKI_ARM_DUE )
		SPI.transfer16( data );
#endif
	}

	TIKI_FORCE_INLINE void ST7735::enableCommandStream()
	{
#if TIKI_ENABLED( TIKI_AVR )
		*m_pDcPort &= ~m_dcPinMask;	// low
#elif TIKI_ENABLED( TIKI_ARM_DUE )
		m_pDcPort->PIO_CODR |= m_dcPinMask; // low
#endif
	}

	TIKI_FORCE_INLINE void ST7735::enableDataStream()
	{
#if TIKI_ENABLED( TIKI_AVR )
		*m_pDcPort |= m_dcPinMask; // high
#elif TIKI_ENABLED( TIKI_ARM_DUE )
		m_pDcPort->PIO_SODR |= m_dcPinMask; // high
#endif
	}

	TIKI_FORCE_INLINE void ST7735::startTransaction()
	{
#if defined( SPI_HAS_TRANSACTION )
		SPI.beginTransaction( TFT_ST7735_SPI );
#endif

#if TIKI_ENABLED( TIKI_AVR )
		*m_pCsPort &= ~m_csPinMask; // low
#elif TIKI_ENABLED( TIKI_ARM_DUE )
		m_pCsPort->PIO_CODR |= m_csPinMask; // low
#endif
	}

	TIKI_FORCE_INLINE void ST7735::endTransaction()
	{
#if defined(SPI_HAS_TRANSACTION)
		SPI.endTransaction();
#endif
	}

	TIKI_FORCE_INLINE void ST7735::disableCs()
	{
#if TIKI_ENABLED( TIKI_AVR )
		*m_pCsPort |= m_csPinMask; // high
#elif TIKI_ENABLED( TIKI_ARM_DUE )
		m_pCsPort->PIO_SODR |= m_csPinMask; // high
#endif
	}

	TIKI_FORCE_INLINE void ST7735::writeCommandFirst( uint8 command )
	{
		enableCommandStream();
		spiWrite8( command );
	}

	TIKI_FORCE_INLINE void ST7735::writeCommand( uint8 command )
	{
		spiWrite8( command );
	}

	TIKI_FORCE_INLINE void ST7735::writeCommandLast( uint8 command )
	{
		spiWrite8( command );
		disableCs();
	}

	TIKI_FORCE_INLINE void ST7735::writeData8First( uint8 data )
	{
		enableDataStream();
		spiWrite8( data );
	}

	TIKI_FORCE_INLINE void ST7735::writeData16First( uint16 data )
	{
		enableDataStream();
		spiWrite16( data );
	}

	TIKI_FORCE_INLINE void ST7735::writeData8( uint8 data )
	{
		spiWrite8( data );
	}

	TIKI_FORCE_INLINE void ST7735::writeData16( uint16 data )
	{
		spiWrite16( data );
	}

	TIKI_FORCE_INLINE void ST7735::writeDataArray8( const uint8* pData, uint8 length )
	{
		do
		{
			spiWrite8( *pData++ );
		}
		while( length-- > 0u );
	}

	TIKI_FORCE_INLINE void ST7735::writeDataArray16( const uint16* pData, uint16 length )
	{
		do
		{
			spiWrite16( *pData++ );
		}
		while( length-- > 0u );
	}

	TIKI_FORCE_INLINE void ST7735::writeData8Last( uint8 data )
	{
		spiWrite8( data );
		disableCs();
	}

	TIKI_FORCE_INLINE void ST7735::writeData16Last( uint16 data )
	{
		spiWrite16( data );
		disableCs();
	}

	TIKI_FORCE_INLINE void ST7735::setAddressRectangle( uint8 x0, uint8 y0, uint8 x1, uint8 y1 )
	{
		writeCommandFirst( CMD_CLMADRS ); // Column
		writeData16First( x0 );
		writeData16( x1 );

		writeCommandFirst( CMD_PGEADRS ); // Page
		writeData16First( y0 );
		writeData16( y1 );

		writeCommandFirst( CMD_RAMWR ); // Into ILI Ram
	}
}
