#include "Bomb.h"

Bomb::Bomb(int x, int y)
{
	this->x = x;
	this->y = y;

	state = normal;
	width = 66 / 3;
	height = 24;

	timeToExplode = 0;

	explosionHeight = 160 / 8;
	explosionWidth = 80 / 4;
}
Bomb::~Bomb() {}

bool Bomb::ValidateLocation(int x, int y, int** grid)
{
	if (grid[y / 50][x / 50] == 0 || grid[y / 50][x / 50] == 2)
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
	if (ValidateLocation(x, y, grid) == true)
	{
		timeToExplode = 0;

		sf::Sprite bombSprite;
		if (timeToExplode == 0)
		{
			bombSprite.setTexture(TextureLibrary::bombTextures[0]);
			timeToExplode++;
		}
		if (timeToExplode == 1)
		{
			bombSprite.setTexture(TextureLibrary::bombTextures[1]);
			timeToExplode++;
		}
		if (timeToExplode == 2)
		{
			bombSprite.setTexture(TextureLibrary::bombTextures[2]);
			timeToExplode++;
		}

		bombSprite.setPosition((float)x, (float)y);
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
	if (indexEX >= 0 && indexEX < 2)
	{
		indexEX++;
	}
	else
	{
		state = State::disappear;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Bomb::DrawExplosion(sf::RenderTarget& target, int** grid, std::array<sf::Texture, 9>& explosionTextures)
{
	////////////////////////
	sf::Sprite sprite;
	sprite.setTexture(TextureLibrary::explosionTextures[0]);
	target.draw(sprite);
	////////////////////////
	if (grid[y / 50][(x - 50) / 50] != 1) {
		////////////////////////
		sf::Sprite sprite;
		sprite.setTexture(TextureLibrary::explosionTextures[4]);
		sprite.setPosition((float)x - 50.0f, (float)y);
		sprite.setScale(2.5f, 2.5f);
		target.draw(sprite);
		////////////////////////

		if (grid[y / 50][(x - 50) / 50] == 3)
		{
			grid[y / 50][(x - 50) / 50] = 2;
		}
	}

	if (grid[y / 50][(x + 50) / 50] != 1) {
		sf::Sprite sprite;
		sprite.setTexture(TextureLibrary::explosionTextures[2]);
		sprite.setPosition((float)x + 50.0f, (float)y);
		sprite.setScale(2.5f, 2.5f);
		target.draw(sprite);

		if (grid[y / 50][(x + 50) / 50] == 3)
		{
			grid[y / 50][(x + 50) / 50] = 2;
		}
	}

	if (grid[y / 50][(x + 50) / 50] != 1) {
		sf::RectangleShape tipRight;
		tipRight.setPosition((float)x + 100.0f, (float)y);
		tipRight.setSize(sf::Vector2f(50.0f, 50.0f));

		sf::Sprite sprite;
		sprite.setTexture(TextureLibrary::explosionTextures[4]);
		target.draw(sprite);
		target.draw(tipRight);


		if (grid[y / 50][(x + 100) / 50] == 3 && grid[y / 50][(x + 50) / 50] != 1)
		{

			grid[y / 50][(x + 100) / 50] = 2;
		}
	}

	if (grid[y / 50][(x - 50) / 50] != 1) {
		sf::RectangleShape tipLeft;
		tipLeft.setPosition((float)x - 100.0f, (float)y);
		tipLeft.setSize(sf::Vector2f(50.0f, 50.0f));

		sf::Sprite sprite;
		sprite.setTexture(TextureLibrary::explosionTextures[1]);
		target.draw(sprite);
		target.draw(tipLeft);

		if (grid[y / 50][(y - 100) / 50] == 3 && grid[y / 50][(x - 50) / 50] != 1)
		{
			grid[y / 50][(x - 100) / 50] = 2;
		}
	}

	sf::RectangleShape verticalTop;
	verticalTop.setPosition((float)x, (float)y - 50.0f);
	verticalTop.setSize(sf::Vector2f(50.0f, 50.0f));

	sf::RectangleShape Verticalbottom;
	Verticalbottom.setPosition((float)x, (float)y + 50.0f);
	Verticalbottom.setSize(sf::Vector2f(50.0f, 50.0f));

	if (grid[(y - 50) / 50][x / 50] != 1)
	{
		//g->DrawImage(explosionCenter, verticalTop, portionUseVertical);
	}
	if (grid[(y - 50) / 50][x / 50] == 3)
	{
		grid[(y - 50) / 50][x / 50] = 2;
	}
	if (grid[(y + 50) / 50][x / 50] != 1)
	{
		//g->DrawImage(explosionCenter, Verticalbottom, portionUseVertical);
	}
	if (grid[(+50) / 50][x / 50] == 3)
	{
		grid[(+50) / 50][x / 50] = 2;
	}


	if (grid[(y - 50) / 50][x / 50] != 1) {
		sf::RectangleShape portionUseTopTip;
		portionUseTopTip.setPosition((float)indexEX * (float)explosionWidth, (float)indexEY + 5.0f * (float)explosionHeight); //indiceY = 5
		portionUseTopTip.setSize(sf::Vector2f((float)explosionWidth, (float)explosionHeight));
		sf::RectangleShape topTip;
		topTip.setPosition((float)x, (float)y - 100.0f);
		topTip.setSize(sf::Vector2f(50.0f, 50.0f));
		//g->DrawImage(explosionCenter, topTip, portionUseTopTip);

		if (grid[(y - 100) / 50][x / 50] == 3 && grid[(y - 50) / 50][x / 50] != 1)
		{
			grid[(y - 100) / 50][x / 50] = 2;
		}
	}


	if (grid[(y + 50) / 50][x / 50] != 1) {
		sf::RectangleShape PuntaInferior;
		PuntaInferior.setPosition((float)x, (float)y + 100.0f);
		PuntaInferior.setSize(sf::Vector2f(50.0f, 50.0f));
		//g->DrawImage(explosionCenter, PuntaInferior, porcionUsarPuntaInferior);
		if (grid[(y + 100) / 50][x / 50] == 3 && grid[(y + 50) / 50][x / 50] != 1) {
			grid[(y + 100) / 50][x / 50] = 2;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Bomb::State Bomb::GetState()
{
	return state;
}