#pragma once
#include <vector>
#include "Bomb.h"
#include "TextureLibrary.h"

class BombArray
{
public:
	// Constructors/ Destructors
	BombArray();
	virtual ~BombArray();

	// Public functions
	void DrawOneBomb(sf::RenderTarget& target, int xPlayer, int yPlayer, int** grid);
	void InitBomb(int x, int y);

private:
	// Private variables
	int totalBombs;
	std::vector<Bomb*>bombArray;
};