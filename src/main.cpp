#include <iostream>

#include "glbinding.h"

#include "Game/Game.h"

#include "Resources/Font/FntParser.h"



int main()
{
	//glbinding::Binding::initialize(false);
	//Game::I().Start();

	FntParser::Value value("height=25");
	std::cout
		<< value.name << std::endl
		<< value.stringValue << std::endl
		<< value.intValue << std::endl;
		

	system("PAUSE");

	return 0;
}
