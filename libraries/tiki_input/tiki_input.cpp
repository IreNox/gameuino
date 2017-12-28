#include "tiki_input.h"

namespace tiki
{
	static const uint8 s_inputButton1		= 30u;
	static const uint8 s_inputButton2		= 31u;
	static const uint8 s_inputButton3		= 32u;
	static const uint8 s_inputButton4		= 33u;

#if TIKI_ENABLED( TIKI_AVR )
	static const uint8 s_inputStickX		= PIN_A10;
	static const uint8 s_inputStickY		= PIN_A11;
#elif TIKI_ENABLED( TIKI_ARM_DUE )
	static const uint8 s_inputStickX		= 64u;
	static const uint8 s_inputStickY		= 65u;
#else
#	error "Platform not supported"
#endif
	static const uint8 s_inputStickButton	= 52u;

	static const uint8 s_inputTolerance		= 24u;

	Input::Input()
	{
		m_currentState.stickX		= 0;
		m_currentState.stickY		= 0;
		m_currentState.buttonMask	= 0u;
		m_previousState = m_currentState;
	}

	void Input::initialize()
	{
		pinMode( s_inputButton1, INPUT );
		pinMode( s_inputButton2, INPUT );
		pinMode( s_inputButton3, INPUT );
		pinMode( s_inputButton4, INPUT );

		pinMode( s_inputStickX, INPUT );
		pinMode( s_inputStickY, INPUT );
		pinMode( s_inputStickButton, INPUT );
	}

	void Input::update()
	{
		m_previousState = m_currentState;

		sint16 stickX = (sint16)analogRead( s_inputStickX );
		stickX = 512 - stickX;
		if( abs( stickX ) < s_inputTolerance )
		{
			stickX = 0u;
		}

		sint16 stickY = (sint16)analogRead( s_inputStickY );
		stickY = 512 - stickY;
		if( abs( stickY ) < s_inputTolerance )
		{
			stickY = 0u;
		}

		m_currentState.stickX	= stickX;
		m_currentState.stickY	= stickY;

		m_currentState.buttonMask = 0u;
		m_currentState.buttonMask |= digitalRead( s_inputButton1 ) ? InputButtonMask_1 : 0;
		m_currentState.buttonMask |= digitalRead( s_inputButton2 ) ? InputButtonMask_2 : 0;
		m_currentState.buttonMask |= digitalRead( s_inputButton3 ) ? InputButtonMask_3 : 0;
		m_currentState.buttonMask |= digitalRead( s_inputButton4 ) ? InputButtonMask_4 : 0;
		m_currentState.buttonMask |= digitalRead( s_inputStickButton ) ? InputButtonMask_Stick : 0;
	}
}
