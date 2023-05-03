#pragma once
#include <vector>
#include "Bomb.h"
#include "TextureLibrary.h"

class Bomb;

class BombArray
{
public:
	// Constructors/ Destructors
	BombArray();
	virtual ~BombArray();

	// Public functions
	void DrawOneBomb(sf::RenderTarget& target, int xPlayer, int yPlayer, int** grid);
	void InitBomb(int x, int y);
	std::vector<Bomb*>GetBombArray();
	void RenderBombs(sf::RenderTarget& target);

private:
	// Private variables
	int totalBombs;
public:
	std::vector<Bomb*>bombArray;
};