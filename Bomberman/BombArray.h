#pragma once
#include <array> // Include the array header from the standard library
#include "Bomb.h" // Include the header file for the Bomb class
#include "TextureLibrary.h" // Include the header file for the TextureLibrary class

class Bomb;  // Forward Declaration of the Bomb

class BombArray
{
public:
	// Constructors/ Destructors
	BombArray();
	virtual ~BombArray();

public:
	// Public functions
	void DrawOneBomb(sf::RenderTarget& target, float xPlayer, float yPlayer, int** grid);
	void InitBomb(int x, int y);
	std::vector<Bomb*>GetBombArray();
	void RenderBombs(sf::RenderTarget& target, int direction);

public:
	// Public variables
	std::vector<Bomb*>bombArray;

private:
	// Private variables
	int totalBombs;
};