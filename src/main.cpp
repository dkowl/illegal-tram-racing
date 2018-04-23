#include <iostream>

#include "glbinding.h"

#include "Game/Game.h"

#include "Resources/Font/FntParser.h"



int main()
{
	//glbinding::Binding::initialize(false);
	//Game::I().Start();

	FntParser fntParser("C:\\Users\\Dominik\\Desktop\\NWW\\NWT\\res\\Fonts\\expressway.fnt");
	fntParser.Display();

	system("PAUSE");

	return 0;
}
