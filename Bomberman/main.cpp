#include <iostream> // Include the input/output stream library
#include "Game.h" // Include the header file for the Game class

int main() // Main function
{
	// Init classes
	Game game; // Create an instance of the Game class

	// Game loop
	while (game.Running())
	{
		game.Update(); // Update the game state
		game.Render(); // Render the game graphics
	}
	return 0; // Exit the program with a status code of 0
}