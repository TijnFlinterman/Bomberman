#include "BombArray.h"

BombArray::BombArray()
{
	totalBombs = 1;
}
BombArray::~BombArray() {}

void BombArray::InitBomb(int x, int y)
{
	if (bombArray.size() < totalBombs)
	{
		Bomb* newBomb = new Bomb(x, y);
		bombArray.push_back(newBomb);
	}
}

void BombArray::DrawOneBomb(sf::RenderTarget& target, sf::Texture bombTexture, sf::Texture explosionTexture, int xPlayer, int yPlayer, int** grid)
{
	for (int i = 0; i < bombArray.size(); i++)
	{
		switch (bombArray.at(i)->GetState())
		{
		case Bomb::State::normal:
			bombArray.at(i)->DrawBomb(bombTexture, explosionTexture, xPlayer, yPlayer, grid);
			bombArray.at(i)->AnimateBomb();
			break;
		case Bomb::State::explode:
			bombArray.at(i)->DrawExplosion(target, explosionTexture, grid);
			bombArray.at(i)->AnimateExplosion();
			break;
		case Bomb::State::disappear:
			bombArray.erase(bombArray.begin() + i);
			break;
		}
	}
}

sf::Texture BombArray::GetBombTexture()
{
	bombTexture.loadFromFile("Assets/Textures/Bomb/Bomb.png");
	return bombTexture;
}

sf::Texture BombArray::GetExplosionTexture()
{
	explosionTexture.loadFromFile("Assets/Textures/Bomb/Explosion.png");
	return explosionTexture;
}