#include "BombArray.h"  // Include the header file for the BombArray class

// Constructors/ Destructors
BombArray::BombArray()
{
	totalBombs = 1;
}
BombArray::~BombArray() {}

// Public functions
void BombArray::DrawOneBomb(sf::RenderTarget& target, float xPlayer, float yPlayer, int** grid)
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
void BombArray::InitBomb(int x, int y)
{
	if (bombArray.size() < totalBombs)
	{
		Bomb* newBomb = new Bomb(x, y);
		bombArray.push_back(newBomb);
	}
}
std::vector<Bomb*> BombArray::GetBombArray()
{
	return bombArray;
}
void BombArray::RenderBombs(sf::RenderTarget& target, int direction)
{
	for (int i = 0; i < bombArray.size(); i++)
	{
		bombArray.at(i)->Render(target, direction);
	}
}