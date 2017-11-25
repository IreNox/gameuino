#include "pong.h"

tiki::Pong game;

void setup()
{
	game.initialize();
}

void loop()
{
  game.loop();
}
