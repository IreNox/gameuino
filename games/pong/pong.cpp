#include "pong.h"

namespace tiki
{
	void Pong::initialize()
	{
		Serial.begin( 9600 );

		m_input.initialize();

		m_graphics.initialize();
		m_graphics.fillScreen( 0x0000u );

		m_humanPlayer.moveY			= 0;
		m_humanPlayer.rect.pos.x	= Player1PosX;
		m_humanPlayer.rect.pos.y	= 42u;
		m_humanPlayer.rect.size.x	= 4;
		m_humanPlayer.rect.size.y	= 16u;
		m_humanPlayer.score			= 0u;

		m_aiPlayer.moveY			= 0;
		m_aiPlayer.rect.pos.x		= Player2PosX;
		m_aiPlayer.rect.pos.y		= 42u;
		m_aiPlayer.rect.size.x		= 4;
		m_aiPlayer.rect.size.y		= 16u;
		m_aiPlayer.score			= 0u;

		m_ballRect.pos.x			= 0u;
		m_ballRect.pos.y			= 0u;
		m_ballRect.size.x			= 4u;
		m_ballRect.size.y			= 4u;
		m_ballSpeedX				= 0;
		m_ballSpeedY				= 0;
		m_ballDirectionX			= -1;
		m_ballDirectionY			= 1;
		
		drawGame();
		drawPlayer( m_humanPlayer.rect.pos.x, m_humanPlayer.rect.pos.y, m_humanPlayer.rect.pos.y );
		drawPlayer( m_aiPlayer.rect.pos.x, m_aiPlayer.rect.pos.y, m_aiPlayer.rect.pos.y );
	}

	void Pong::loop()
	{
		const int frameStartTime = millis();

		m_input.update();

		updateHumanPlayer();
		updateAiPlayer();
		updateBall();
		
		const int frameEndTime = millis();
		const int elapsedTime = frameEndTime - frameStartTime;
		Serial.println( elapsedTime );
		if( elapsedTime < 16 )
		{
			delay( 16 - elapsedTime );
		}
		else
		{
			Serial.println( "Frame time exeeded!" );
		}
	}

	void Pong::updateHumanPlayer()
	{
		const sint32 stickState = m_input.getCurrentState().stickY;
		updatePlayer( m_humanPlayer, stickState );
	}

	void Pong::updateAiPlayer()
	{
		const sint32 ballCenterY = (m_ballRect.pos.y + 2);
		const sint32 playerCenterY = (m_aiPlayer.rect.pos.y + 8);
		const sint32 stickState = (playerCenterY - ballCenterY) * 64;
		updatePlayer( m_aiPlayer, stickState );
	}

	void Pong::updatePlayer( PlayerState& player, sint32 inputState )
	{
		inputState = min( inputState, 512 );
		inputState = max( inputState, -512 );

		player.speedY = inputState;
		player.moveY -= (inputState * 250);
		
		if( abs( player.moveY ) < (512 * 60) )
		{
			return;
		}

		const sint32 playerDelta = player.moveY / (512 * 60);
		player.moveY -= playerDelta *  (512 * 60);

		const uint8 oldPos = player.rect.pos.y;
		sint16 newPos = player.rect.pos.y;
		newPos += playerDelta;
		player.rect.pos.y = newPos;

		checkPlayerPos( player );
		if( player.rect.pos.y != oldPos )
		{
			drawPlayer( player.rect.pos.x, player.rect.pos.y, oldPos );
		}
	}

	void Pong::updateBall()
	{
		const Rectangle oldRect = m_ballRect;

		if( m_ballSpeedX == 0u )
		{
			m_ballRect.pos.x	= 78u;
			m_ballRect.pos.y	= random( 8, 92 );
			m_ballSpeedX 		= 2;
			m_ballSpeedY		= 2;
			m_ballDirectionY	= random( 100 ) < 50 ? -1 : 1;
		}

		m_ballRect.pos.x += m_ballSpeedX * m_ballDirectionX;
		m_ballRect.pos.y += m_ballSpeedY * m_ballDirectionY;
		checkBallPos();

		if( m_ballRect.pos.x != oldRect.pos.x || m_ballRect.pos.y != oldRect.pos.y )
		{
			drawBall( m_ballRect.pos.x, m_ballRect.pos.y, oldRect.pos.x, oldRect.pos.y );
		}

		Rectangle pointRect = { 78u, 6u, 4u, 4u };
		for( ; pointRect.pos.y < 100;  pointRect.pos.y += 8u )
		{
			if( !pointRect.intersect( oldRect ) )
			{
				continue;
			}

			m_graphics.drawRectangle( pointRect, GraphicsColorWhite );
		}
	}

	void Pong::checkPlayerPos( PlayerState& player )
	{
		if( player.rect.pos.y < 8 )
		{
			player.rect.pos.y = 8u;
			player.moveY = 0;
		}
		else if( player.rect.pos.y > 80u )
		{
			player.rect.pos.y = 80;
			player.moveY = 0;
		}
	}

	void Pong::checkBallPos()
	{
		if( m_ballRect.pos.y < 8u )
		{
			m_ballRect.pos.y = 8u;
			m_ballDirectionY *= -1;
		}
		else if( m_ballRect.pos.y > 92u )
		{
			m_ballRect.pos.y = 92u;
			m_ballDirectionY *= -1;
		}

		if( m_ballRect.pos.x < 4 )
		{
			m_ballRect.pos.x = 4u;

			m_aiPlayer.score++;			
			m_ballSpeedX		= 0u;
			m_ballDirectionX	= -1;

			drawScore( 0, 0, 0, 0 );
		}
		else if( m_ballRect.pos.x > 38u * 4u )
		{
			m_ballRect.pos.x = 38u * 4u;

			m_humanPlayer.score++;
			m_ballSpeedX		= 0u;
			m_ballDirectionX	= 1;

			drawScore( 0, 0, 0, 0 );
		}

		checkBallPlayerPos( m_humanPlayer );
		checkBallPlayerPos( m_aiPlayer );
	}

	void Pong::checkBallPlayerPos( PlayerState& player )
	{
		if( m_ballRect.intersect( player.rect ) )
		{
			m_ballRect.pos.x = (m_ballDirectionX < 0 ? player.rect.pos.x + player.rect.size.x : player.rect.pos.x - m_ballRect.size.x);

			const sint8 ballCenterY		= (m_ballRect.pos.y + 2);
			const sint8 playerCenterY	= (player.rect.pos.y + 8);
			m_ballSpeedY				= (ballCenterY - playerCenterY) / 3;
			m_ballDirectionY			= (m_ballSpeedY / abs( m_ballSpeedY ));

			const sint16 playerDirectionY = (player.speedY / abs( player.speedY ));
			if( playerDirectionY == m_ballDirectionY )
			{
				m_ballSpeedY += player.speedY / 256;
			}

			m_ballSpeedY = max( abs( m_ballSpeedY ), 1 );
			if( m_ballSpeedY > m_ballSpeedX )
			{
				m_ballSpeedX = max( m_ballSpeedY / 2, m_ballSpeedX );
			}

			m_ballDirectionX *= -1;
		}
	}

	void Pong::drawGame()
	{
		m_graphics.drawRectangle( 3u * 4u, 4u, 34u * 4u, 4u, GraphicsColorWhite );
		m_graphics.drawRectangle( 3u * 4u, 96u, 34u * 4u, 4u, GraphicsColorWhite );

		for( uint8 y = 6u; y < 100; y += 8u )
		{
			m_graphics.drawRectangle( 78u, y, 4u, 4u, GraphicsColorWhite );
		}
	}

	void Pong::drawPlayer( uint8 posX, uint8 posY, uint8 oldPosY )
	{
		if( posY != oldPosY )
		{
			const uint8 oldPosBaseY = ( posY > oldPosY ? oldPosY : posY + 16 );
			const uint8 oldHeight = ( posY > oldPosY ? posY - oldPosY : oldPosY - posY );
			m_graphics.drawRectangle( posX, oldPosBaseY, 4, oldHeight, GraphicsColorBlack );
		}

		m_graphics.drawRectangle( posX, posY, 4, 16, GraphicsColorWhite );
	}

	void Pong::drawBall( uint8 posX, uint8 posY, uint8 oldPosX, uint8 oldPosY )
	{
		/*const uint8 oldPosBaseX = ( posX > oldPosX ? oldPosX : posX + 4 );
		const uint8 oldWidth = ( posX > oldPosX ? posY - oldPosX : oldPosX - posX );
		if( oldWidth > 0 )
		{
			m_graphics.drawRectangle( oldPosBaseX, oldPosY, 4, oldWidth, GraphicsColorBlack );
		}

		const uint8 oldPosBaseY = ( posY > oldPosY ? oldPosY : posY + 4 );
		const uint8 oldHeight = ( posY > oldPosY ? posY - oldPosY : oldPosY - posY );
		if( oldHeight > 0 )
		{
			m_graphics.drawRectangle( oldPosX, oldPosBaseY, 4, oldHeight, GraphicsColorBlack );
		}*/

		m_graphics.drawRectangle( oldPosX, oldPosY, 4, 4, GraphicsColorBlack );
		m_graphics.drawRectangle( posX, posY, 4, 4, GraphicsColorWhite );
	}

	void Pong::drawScore( uint8 posX, uint8 posY, uint8 oldScore, uint8 newScore )
	{

	}
}
