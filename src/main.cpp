#include <iostream>

#include "glbinding.h"

#include "Game/Game.h"
#include "Game/Track.h"



int main()
{
	//glbinding::Binding::initialize(false);
	//Game game;
	//game.Start();

	Track track(1000);
	std::cout << "Track generated, segmentCount: " << track.SegmentCount() << std::endl;

	system("PAUSE");

	return 0;
}
