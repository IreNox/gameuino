#pragma once

#include "tiki_core.h"
#include "tiki_input.h"
#include "tiki_graphics.h"
#include "tiki_resource.h"

namespace tiki
{
    class Pong
    {
    public:

        void  	  initialize();
        void  	  loop();

	private:
		
		enum
		{
			Player1PosX	= 3u * 4u,
			Player2PosX	= 36u * 4u,
		};

		struct PlayerState
		{
			sint32		moveY;
			sint16		speedY;
			Rectangle	rect;
			uint8		score;
		};

        Input		m_input;
		Graphics	m_graphics;

		PlayerState	m_humanPlayer;
		PlayerState	m_aiPlayer;
		
		Rectangle	m_ballRect;
		sint8		m_ballSpeedX;
		sint8		m_ballSpeedY;
		sint8		m_ballDirectionX;
		sint8		m_ballDirectionY;
		
		void		updateHumanPlayer();
		void		updateAiPlayer();
		void		updatePlayer( PlayerState& player, sint32 inputState );
		void		updateBall();

		void		checkPlayerPos( PlayerState& player );
		void		checkBallPos();
		void		checkBallPlayerPos( PlayerState& player );
		
		void		drawGame();
		void		drawPlayer( uint8 posX, uint8 posY, uint8 oldPosY );
		void		drawBall( uint8 posX, uint8 posY, uint8 oldPosX, uint8 oldPosY );
		void		drawScore( uint8 posX, uint8 posY, uint8 oldScore, uint8 newScore );
    };
}
