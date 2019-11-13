#include "tiki_input.h"

namespace tiki
{
	static const uint8 s_inputDataClockPin		= 2u;
	static const uint8 s_inputDataLatchPin		= 3u;
	static const uint8 s_inputDataSerialPin		= 4u;

//#if TIKI_ENABLED( TIKI_AVR )
//	static const uint8 s_inputStickX			= PIN_A10;
//	static const uint8 s_inputStickY			= PIN_A11;
//#elif TIKI_ENABLED( TIKI_ARM_DUE )
//	static const uint8 s_inputStickX			= 64u;
//	static const uint8 s_inputStickY			= 65u;
//#else
//#	error "Platform not supported"
//#endif
//	static const uint8 s_inputStickButton		= 52u;
//	static const uint8 s_inputStickTolerance	= 24u;

	Input::Input()
	{
		m_currentState.buttonMask = 0u;
		m_previousState = m_currentState;
	}

	void Input::initialize()
	{
		pinMode( s_inputDataClockPin, OUTPUT );
		digitalWrite( s_inputDataClockPin, HIGH );

		pinMode( s_inputDataLatchPin, OUTPUT );
		digitalWrite( s_inputDataLatchPin, LOW );

		//pinMode( s_inputDataSerialPin, OUTPUT );
		//digitalWrite( s_inputDataSerialPin, HIGH );
		pinMode( s_inputDataSerialPin, INPUT );
	}

	void Input::update()
	{
		m_previousState = m_currentState;
		m_currentState.buttonMask = 0u;

	    // Latch for 12us
		digitalWrite( s_inputDataLatchPin, HIGH );
		delayMicroseconds( 12u );
		//digitalWrite( s_inputDataLatchPin, LOW );
		//delayMicroseconds( 12u );

		for( uint8 i = 0u; i < 16u; ++i )
		{
			if( i <= 11u )
			{
				m_currentState.buttonMask |= digitalRead( s_inputDataSerialPin ) ? 0 : (1u << i);
			}

			delayMicroseconds( 12u );
			digitalWrite( s_inputDataClockPin, HIGH );
			delayMicroseconds( 12u );
			digitalWrite( s_inputDataClockPin, LOW );
		}
	}
}
