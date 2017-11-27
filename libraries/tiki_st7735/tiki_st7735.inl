#pragma once

namespace tiki
{
	void TIKI_FORCE_INLINE ST7735::spiWrite8( uint8 data )
	{
#if TIKI_ENABLED( TIKI_AVR )
		SPDR = data;				//load your outgoing data into the SPI shift reg's data register
		while( !(SPSR & _BV(SPIF)) );	//wait for the data to be transmitted on MOSI
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
		*m_pRsPort &= ~m_dcPinMask;	// low
#elif TIKI_ENABLED( TIKI_ARM_DUE )
		m_pRsPort->PIO_CODR |= m_dcPinMask; // low
#endif
	}

	TIKI_FORCE_INLINE void ST7735::enableDataStream()
	{
#if TIKI_ENABLED( TIKI_AVR )
		*m_pRsPort |= m_dcPinMask; // high
#elif TIKI_ENABLED( TIKI_ARM_DUE )
		m_pRsPort->PIO_SODR |= m_dcPinMask; // high
#endif
	}

	TIKI_FORCE_INLINE void ST7735::startTransaction()
	{
#if defined( SPI_HAS_TRANSACTION )
		SPI.beginTransaction( _ST7735SPI );
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

	}

	TIKI_FORCE_INLINE void ST7735::writeCommand( uint8 command )
	{

	}

	TIKI_FORCE_INLINE void ST7735::writeCommandLast( uint8 command )
	{

	}

	TIKI_FORCE_INLINE void ST7735::writeData8First( uint8 data )
	{

	}

	TIKI_FORCE_INLINE void ST7735::writeData16First( uint16 data )
	{

	}

	TIKI_FORCE_INLINE void ST7735::writeData8( uint8 data )
	{

	}

	TIKI_FORCE_INLINE void ST7735::writeData16( uint16 data )
	{

	}

	TIKI_FORCE_INLINE void ST7735::writeData8Last( uint8 data )
	{

	}

	TIKI_FORCE_INLINE void ST7735::writeData16Last( uint16 data )
	{

	}
}
