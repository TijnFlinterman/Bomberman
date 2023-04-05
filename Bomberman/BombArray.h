#pragma once
#include <vector>
#include "Bomb.h"

class BombArray
{
public:
	// Constructors/ Destructors
	BombArray();
	virtual ~BombArray();

	// Public functions
	void DrawOneBomb(sf::RenderTarget& target, sf::Texture bombTexture, sf::Texture explosionTexture, int xPlayer, int yPlayer, int** grid);
	void InitBomb(int x, int y);

	sf::Texture GetBombTexture();
	sf::Texture GetExplosionTexture();


private:
	// Private variables
	int totalBombs;
	std::vector<Bomb*>bombArray;
	sf::Texture	bombTexture;
	sf::Texture	explosionTexture;
};