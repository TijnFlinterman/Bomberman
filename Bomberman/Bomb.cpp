#include "Bomb.h"

Bomb::Bomb(int x, int y)
{
	this->x = x;
	this->y = y;

	state = normal;
	timeToExplode = 0;
}
Bomb::~Bomb() {}

bool Bomb::ValidateLocation(int xPlayer, int yPlayer, int** grid)
{
	if (grid[yPlayer / 50][xPlayer / 50] == 0 || grid[yPlayer / 50][xPlayer / 50] == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Bomb::DrawBomb(sf::RenderTarget& target, int xPlayer, int yPlayer, int** grid)
{
	if (ValidateLocation(xPlayer, yPlayer, grid) == true)
	{
		timeToExplode = 0;

		sf::Sprite bombSprite;
		if (timeToExplode == 0)
		{
			bombSprite.setTexture(TextureLibrary::bombTextures->at(0));
			timeToExplode++;
		}
		if (timeToExplode == 1)
		{
			bombSprite.setTexture(TextureLibrary::bombTextures->at(1));
			timeToExplode++;
		}
		if (timeToExplode == 2)
		{
			bombSprite.setTexture(TextureLibrary::bombTextures->at(2));
			timeToExplode++;
		}

		bombSprite.setPosition((float)x - 25, (float)y - 25);
		bombSprite.setScale(3.2f, 3.2f);
		target.draw(bombSprite);
	}
	state = normal;
	if (timeToExplode == 3)
	{
		state = explode;
	}
}

void Bomb::AnimateExplosion()
{
	if (explosionLinger >= 0 && explosionLinger < 3)
	{
		explosionLinger++;
	}
	else
	{
		state = State::disappear;
	}
}

void Bomb::DrawExplosion(sf::RenderTarget& target, int** grid, std::array<sf::Texture, 9>* explosionTextures)
{
	// CENTER
	sf::Sprite sprite;
	sprite.setTexture(TextureLibrary::explosionTextures->at(0));
	sprite.setPosition((float)x - 25.0f, (float)y - 25.0f);
	sprite.setScale(2.5f, 2.5f);
	target.draw(sprite);

	if (grid[y / 50][(x - 50) / 50] != 1) {
		// LEFT SHAFT
		sf::Sprite sprite;
		sprite.setTexture(TextureLibrary::explosionTextures->at(4));
		sprite.setPosition((float)x - 75.0f, (float)y - 25.0f);
		sprite.setScale(2.5f, 2.5f);
		target.draw(sprite);

		if (grid[y / 50][(x - 50) / 50] == 2) 
		{
			grid[y / 50][(x - 50) / 50] = 0; 
		}
	}


	if (grid[y / 50][(x + 50) / 50] != 1) {
		// RIGHT SHAFT
		sf::Sprite sprite;
		sprite.setTexture(TextureLibrary::explosionTextures->at(2));
		sprite.setPosition((float)x + 25.0f, (float)y - 25.0f);
		sprite.setScale(2.5f, 2.5f);
		target.draw(sprite);

		if (grid[y / 50][(x + 50) / 50] == 2) { grid[y / 50][(x + 50) / 50] = 0; }

	}
	if (grid[y / 50][(x + 50) / 50] != 1) {
		sf::Sprite sprite;
		sprite.setTexture(TextureLibrary::explosionTextures->at(3));
		sprite.setPosition((float)x + 75.0f, (float)y - 25.0f);
		sprite.setScale(2.5f, 2.5f);
		target.draw(sprite);

		if (grid[y / 50][(x + 100) / 50] == 2 && grid[y / 50][(x + 50) / 50] != 1)
		{
			grid[y / 50][(x + 100) / 50] = 0;
		}
	}

	if (grid[y / 50][(x - 50) / 50] != 1) {
		// LEFT TIP
		sf::Sprite sprite;
		sprite.setTexture(TextureLibrary::explosionTextures->at(1));
		sprite.setPosition((float)x - 125.0f, (float)y - 25.0f);
		sprite.setScale(2.5f, 2.5f);
		target.draw(sprite);

		if (grid[y / 50][(x - 100) / 50] == 2 && grid[y / 50][(x - 50) / 50] != 1)
		{
			grid[y / 50][(x - 100) / 50] = 0;
		}
	}

	if (grid[(y - 50) / 50][x / 50] != 1)
	{
		// BOTTOM SHAFT
		sf::Sprite sprite;
		sprite.setTexture(TextureLibrary::explosionTextures->at(7));
		sprite.setPosition((float)x - 25.0f, (float)y - 75.0f);
		sprite.setScale(2.5f, 2.5f);
		target.draw(sprite);
	}
	if (grid[(y - 50) / 50][x / 50] == 2)
	{
		grid[(y - 50) / 50][x / 50] = 0;
	}

	if (grid[(y + 50) / 50][x / 50] != 1)
	{
		// TOP SHAFT
		sf::Sprite sprite;
		sprite.setTexture(TextureLibrary::explosionTextures->at(6));
		sprite.setPosition((float)x - 25.0f, (float)y + 25.0f);
		sprite.setScale(2.5f, 2.5f);
		target.draw(sprite);
	}

	if (grid[(y + 50) / 50][x / 50] == 2)
	{
		grid[(y + 50) / 50][x / 50] = 0;
	}

	if (grid[(y - 50) / 50][x / 50] != 1)
	{
		// TOP TIP
		sf::Sprite sprite;
		sprite.setTexture(TextureLibrary::explosionTextures->at(5));
		sprite.setPosition((float)x - 25.0f, (float)y - 125.0f);
		sprite.setScale(2.5f, 2.5f);
		target.draw(sprite);

		if (grid[(y - 100) / 50][x / 50] == 2 && grid[(y - 50) / 50][x / 50] != 1)
		{
			grid[(y - 100) / 50][x / 50] = 0;
		}
	}


	if (grid[(y + 50) / 50][x / 50] != 1)
	{
		// BOTTOM TIP
		sf::Sprite sprite;
		sprite.setTexture(TextureLibrary::explosionTextures->at(8));
		sprite.setPosition((float)x - 25.0f, (float)y + 75.0f);
		sprite.setScale(2.5f, 2.5f);
		target.draw(sprite);

		if (grid[(y + 100) / 50][x / 50] == 2 && grid[(y + 50) / 50][x / 50] != 1)
		{
			grid[(y + 100) / 50][x / 50] = 0;
		}
	}
}

Bomb::State Bomb::GetState()
{
	return state;
}