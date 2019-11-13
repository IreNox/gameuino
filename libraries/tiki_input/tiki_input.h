#pragma once

#include <tiki_core.h>

namespace tiki
{
	enum InputButtonMask
	{
		InputButtonMask_B			= 1u <<  0u,
		InputButtonMask_Y			= 1u <<  1u,
		InputButtonMask_Select		= 1u <<  2u,
		InputButtonMask_Start		= 1u <<  3u,
		InputButtonMask_DPad_Up		= 1u <<  4u,
		InputButtonMask_DPad_Down	= 1u <<  5u,
		InputButtonMask_DPad_Left	= 1u <<  6u,
		InputButtonMask_DPad_Right	= 1u <<  7u,
		InputButtonMask_A			= 1u <<  8u,
		InputButtonMask_X			= 1u <<  9u,
		InputButtonMask_L			= 1u << 10u,
		InputButtonMask_R			= 1u << 11u,
	};

	struct InputState
	{
		uint16	buttonMask;
	};

	class Input
	{
	public:

							Input();

		void				initialize();
		void				update();

		const InputState&	getCurrentState() const { return m_currentState; }
		const InputState&	getPreviousState() const { return m_previousState; }

	private:

		InputState	m_currentState;
		InputState	m_previousState;
	};
}