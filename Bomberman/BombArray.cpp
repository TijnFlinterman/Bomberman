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

void BombArray::DrawOneBomb(sf::RenderTarget& target, sf::Texture bombTexture1, sf::Texture bombTexture2, sf::Texture bombTexture3, sf::Texture explosionTexture, int xPlayer, int yPlayer, int** grid)
{
	for (int i = 0; i < bombArray.size(); i++)
	{
		switch (bombArray.at(i)->GetState())
		{
		case Bomb::State::normal:
			bombArray.at(i)->DrawBomb(target, bombTexture1, bombTexture2, bombTexture3, xPlayer, yPlayer, grid);
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

sf::Texture BombArray::GetBombTexture1()
{
	bombTexture1.loadFromFile("Assets/Textures/Bomb/Bomb-1.png");

	return bombTexture1;
}
sf::Texture BombArray::GetBombTexture2()
{
	bombTexture2.loadFromFile("Assets/Textures/Bomb/Bomb-2.png");
	return bombTexture2;
}
sf::Texture BombArray::GetBombTexture3()
{
	bombTexture3.loadFromFile("Assets/Textures/Bomb/Bomb-3.png");
	return bombTexture3;
}

sf::Texture BombArray::GetExplosionTexture()
{
	explosionTexture.loadFromFile("Assets/Textures/Bomb/Explosion.png");
	return explosionTexture;
}