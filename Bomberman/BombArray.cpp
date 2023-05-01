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

void BombArray::DrawOneBomb(sf::RenderTarget& target, int xPlayer, int yPlayer, int** grid)
{
	for (int i = 0; i < bombArray.size(); i++)
	{
		switch (bombArray.at(i)->GetState())
		{
		case Bomb::State::bomb1:
			bombArray.at(i)->DrawBomb1(target, xPlayer, yPlayer, grid);
			break;
		case Bomb::State::bomb2:
			bombArray.at(i)->DrawBomb2(target, xPlayer, yPlayer, grid);
			break;
		case Bomb::State::bomb3:
			bombArray.at(i)->DrawBomb3(target, xPlayer, yPlayer, grid);
			break;
		case Bomb::State::explode:
			bombArray.at(i)->AnimateExplosion();
			bombArray.at(i)->DrawExplosion(target, grid, TextureLibrary::explosionTextures);
			break;
		case Bomb::State::disappear:
			bombArray.erase(bombArray.begin() + i);
			break;
		}
	}
}
std::vector<Bomb*> BombArray::GetBombArray()
{
	return bombArray;
}