#pragma once

#include <tiki_core.h>

namespace tiki
{
	enum InputButtonMask
	{
		InputButtonMask_1		= 1u << 0u,
		InputButtonMask_2		= 1u << 1u,
		InputButtonMask_3		= 1u << 2u,
		InputButtonMask_4		= 1u << 3u,
		InputButtonMask_Stick	= 1u << 4u,
	};

	struct InputState
	{
		sint16	stickX;
		sint16	stickY;
		uint8	buttonMask;
	};

	class Input
	{
	public:

				Input();

		void	initialize();
		void	update();
		
		const InputState&	getCurrentState() const { return m_currentState; }
		const InputState&	getPreviousState() const { return m_previousState; }

	private:

		InputState	m_currentState;
		InputState	m_previousState;
	};
}