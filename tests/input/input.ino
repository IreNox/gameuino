#include "tiki_input.h"
#include "tiki_graphics.h"

tiki::Input input;
tiki::Graphics graphics;

void setup()
{
    input.initialize();

    graphics.initialize();
    graphics.fillScreen( 0x0000u );

    ST7735& tft = graphics.getTft();
    tft.drawString(0, 0, "StickX:", 0xffffu );
    tft.drawString(0, 8, "StickY:", 0xffffu );
    tft.drawString(0, 16, "Button:", 0xffffu );
}

void loop()
{
    input.update();

    ST7735& tft = graphics.getTft();
    const tiki::InputState& inputState = input.getCurrentState();
    
    char buffer[ 128u ];
    
    sprintf( buffer, "%+d", inputState.stickX );
    tft.fillRect( 48, 0, 24, 7, 0x0000u );
    tft.drawString( 48, 0, buffer, 0xffffu );

    sprintf( buffer, "%+d", inputState.stickY );
    tft.fillRect( 48, 8, 24, 7, 0x0000u );
    tft.drawString( 48, 8, buffer, 0xffffu );

    sprintf( buffer, "%02x", inputState.buttonMask );
    tft.fillRect( 48, 16, 12, 7, 0x0000u );
    tft.drawString( 48, 16, buffer, 0xffffu );
}
