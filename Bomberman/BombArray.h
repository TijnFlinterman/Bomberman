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
	void DrawOneBomb(sf::RenderTarget& target, sf::Texture bombTexture1, sf::Texture bombTexture2, sf::Texture bombTexture3, sf::Texture explosionTexture, int xPlayer, int yPlayer, int** grid);
	void InitBomb(int x, int y);

	sf::Texture GetBombTexture1();
	sf::Texture GetBombTexture2();
	sf::Texture GetBombTexture3();
	sf::Texture GetExplosionTexture();


private:
	// Private variables
	int totalBombs;
	std::vector<Bomb*>bombArray;
	sf::Texture	bombTexture1;
	sf::Texture	bombTexture2;
	sf::Texture	bombTexture3;
	sf::Texture	explosionTexture;
};