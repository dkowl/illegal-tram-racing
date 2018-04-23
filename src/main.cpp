#include <iostream>

#include "glbinding.h"

#include "Game/Game.h"

#include "Resources/Font/FntParser.h"



int main()
{
	//glbinding::Binding::initialize(false);
	//Game::I().Start();

	FntParser::Line line("char id=23   x=2005  y=0     width=25    height=25    xoffset=-12   yoffset=-12   xadvance=64    page=0  chnl=15");
	line.Display();

	system("PAUSE");

	return 0;
}
