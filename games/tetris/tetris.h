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

		void*		m_pSprite3;

		Assets		m_assets;
        Input		m_input;
		Graphics	m_graphics;
		Renderer	m_renderer;

		void*		m_pSprite1;
		void*		m_pSprite2;
    };
}
