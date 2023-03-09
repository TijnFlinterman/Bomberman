#include <iostream>
#include "Game.h"

int main()
{
	// Init srand
	std::srand(static_cast<unsigned>(time(NULL)));

	// Init classes
	Game game;

	// Game start method

	// Game loop
	while (game.Running())
	{
		// Update
		game.Update();
		// Renderer
		game.Render();
	}
	// End of application
	return 0;
}