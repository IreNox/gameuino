#include "tiki_assets.h"
#include "tiki_input.h"
#include "tiki_graphics.h"

#include "asset_data.h"

tiki::Assets assets;
tiki::Input input;
tiki::Graphics graphics;

void setup()
{
	assets.initialize( tiki::s_assets, tiki::AssetName_Count );
	
    input.initialize();

    graphics.initialize();
    graphics.fillScreen( tiki::GraphicsColorBlack );

	const void* pFont = assets.loadAsset( tiki::AssetName_Font );
    graphics.drawText(0, 0, pFont, "STICK X:", tiki::GraphicsColorWhite );
    graphics.drawText(0, 8, pFont, "STICK Y:", tiki::GraphicsColorWhite );
    graphics.drawText(0, 16, pFont, "BUTTONS:", tiki::GraphicsColorWhite );
}

void loop()
{
    input.update();

    const tiki::InputState& inputState = input.getCurrentState();
	const void* pFont = assets.loadAsset( tiki::AssetName_Font );
    char buffer[ 128u ];

    //sprintf( buffer, "%+d", inputState.stickX );
    //graphics.drawRectangle( 63, 0, 30, 7, tiki::GraphicsColorBlack );
    //graphics.drawText( 63, 0, pFont, buffer, tiki::GraphicsColorWhite );

    //sprintf( buffer, "%+d", inputState.stickY );
    //graphics.drawRectangle( 63, 8, 30, 7, tiki::GraphicsColorBlack );
    //graphics.drawText( 63, 8, pFont, buffer, tiki::GraphicsColorWhite );

    sprintf( buffer, "%04X", inputState.buttonMask );
    graphics.drawRectangle( 63, 16, 28, 7, tiki::GraphicsColorBlack );
    graphics.drawText( 63, 16, pFont, buffer, tiki::GraphicsColorWhite );

    delay( 100u );
}
