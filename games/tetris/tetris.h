#pragma once

#include "tiki_assets.h"
#include "tiki_input.h"
#include "tiki_graphics.h"
#include "tiki_renderer.h"

namespace tiki
{
    class Tetris
    {
    public:

        void  	  initialize();
        void  	  loop();

	private:

		enum
		{
			CellsInWidth	= 10,
			CellsInHeight	= 22
		};

		enum BlockType
		{
			BlockType_I,
			BlockType_O,
			BlockType_T,
			BlockType_S,
			BlockType_Z,
			BlockType_J,
			BlockType_L,

			BlockType_Count
		};

		Assets		m_assets;
        Input		m_input;
		Graphics	m_graphics;
		Renderer	m_renderer;

		void*		m_pWall1;
		void*		m_pWall2;
		void*		m_pWall3;

		void*		m_pBlock1;
		void*		m_pBlock2;
		void*		m_pBlock3;
		void*		m_pBlock4;
    };
}
