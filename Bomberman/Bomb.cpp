#include "Bomb.h"

Bomb::Bomb(int x, int y)
{
	this->x = x;
	this->y = y;

	state = normal;
	width = 66 / 3;
	height = 24;

	indexX = 0;
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

void Bomb::DrawBomb(sf::RenderTarget& target, sf::Texture bombTexture1, sf::Texture bombTexture2, sf::Texture bombTexture3, int xPlayer, int yPlayer, int** grid)
{
	if (ValidateLocation(x ,y, grid) == true)
	{
		timeToExplode = 0;

		sf::RectangleShape increase;
		increase.setPosition((float)x, (float)y);
		increase.setSize(sf::Vector2f(40, 40));

		sf::Sprite bombSprite; 
		if (timeToExplode ==0)
		{
			bombSprite.setTexture(bombTexture1);
			timeToExplode++;
		}
		if (timeToExplode == 1)
		{
			bombSprite.setTexture(bombTexture2);
			timeToExplode++;
		}
		if (timeToExplode == 2)
		{
			bombSprite.setTexture(bombTexture3);
			timeToExplode++;
		}

		bombSprite.setPosition(increase.getPosition());
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

void Bomb::DrawExplosion(sf::RenderTarget& target, sf::Texture explosionTexture, int** grid)
{

	sf::RectangleShape portionUseLeft;
	portionUseLeft.setPosition((float)indexEX * (float)explosionWidth, (float)indexEY * (float)explosionHeight);
	portionUseLeft.setSize(sf::Vector2f((float)explosionWidth, (float)explosionHeight)); // indexY=0
	sf::RectangleShape center;
	center.setPosition((float)x, (float)y);
	center.setScale(50, 50);
////////////////////////
	sf::Sprite sprite;
	sprite.setTexture(explosionTexture);
	target.draw(sprite);
	target.draw(center);
	target.draw(portionUseLeft);
////////////////////////
	if (grid[y / 50][(x - 50) / 50] != 1) {
		sf::RectangleShape portionUseLeft;
		portionUseLeft.setPosition((float)indexEX * (float)explosionWidth, (float)indexEY + 2.0f * (float)explosionHeight); //indexY = 2
		portionUseLeft.setSize(sf::Vector2f((float)explosionWidth, (float)explosionHeight));
		sf::RectangleShape left;
		left.setPosition((float)x - 50.0f, (float)y);
		left.setSize(sf::Vector2f(50.0f, 50.0f));
		////////////////////////
		sf::Sprite sprite;
		sprite.setTexture(explosionTexture);
		target.draw(sprite);
		target.draw(left);
		target.draw(portionUseLeft);
		////////////////////////

		if (grid[y / 50][(x - 50) / 50] == 3)
		{
			grid[y / 50][(x - 50) / 50] = 2;
		}
	}

	if (grid[y / 50][(x + 50) / 50] != 1) {
		sf::RectangleShape portionUseRight;
		portionUseRight.setPosition((float)indexEX * (float)explosionWidth, (float)indexEY + 4.0f * (float)explosionHeight); //indexY = 4
		portionUseRight.setSize(sf::Vector2f((float)explosionWidth, (float)explosionHeight));
		sf::RectangleShape right;
		right.setPosition((float)x + 50.0f, (float)y);
		right.setSize(sf::Vector2f(50.0f, 50.0f));

		sf::Sprite sprite;
		sprite.setTexture(explosionTexture);
		target.draw(sprite);
		target.draw(right);
		target.draw(portionUseRight);

		if (grid[y / 50][(x + 50) / 50] == 3)
		{
			grid[y / 50][(x + 50) / 50] = 2;
		}

	}
	if (grid[y / 50][(x + 50) / 50] != 1) {
		sf::RectangleShape portionUseRightTip;
		portionUseRightTip.setPosition((float)indexEX * (float)explosionWidth, (float)indexEY + 3.0f * (float)explosionHeight); //indexY = 3
		portionUseRightTip.setSize(sf::Vector2f((float)explosionWidth, (float)explosionHeight));
		sf::RectangleShape tipRight;
		tipRight.setPosition((float)x + 100.0f, (float)y);
		tipRight.setSize(sf::Vector2f(50.0f, 50.0f));

		sf::Sprite sprite;
		sprite.setTexture(explosionTexture);
		target.draw(sprite);
		target.draw(tipRight);
		target.draw(portionUseRightTip);


		if (grid[y / 50][(x + 100) / 50] == 3 && grid[y / 50][(x + 50) / 50] != 1)
		{

			grid[y / 50][(x + 100) / 50] = 2;
		}
	}

	if (grid[y / 50][(x - 50) / 50] != 1) {
		sf::RectangleShape portionUseLeftTip;
		portionUseLeftTip.setPosition((float)indexEX * (float)explosionWidth, (float)indexEY + 1.0f * (float)explosionHeight); //indexY = 1
		portionUseLeftTip.setSize(sf::Vector2f((float)explosionWidth, (float)explosionHeight));
		sf::RectangleShape tipLeft;
		tipLeft.setPosition((float)x - 100.0f, (float)y);
		tipLeft.setSize(sf::Vector2f(50.0f, 50.0f));

		sf::Sprite sprite;
		sprite.setTexture(explosionTexture);
		target.draw(sprite);
		target.draw(tipLeft);
		target.draw(portionUseLeftTip);

		if (grid[y / 50][(y - 100) / 50] == 3 && grid[y / 50][(x - 50) / 50] != 1)
		{
			grid[y / 50][(x - 100) / 50] = 2;
		}
	}

	sf::RectangleShape portionUseVertical;
	portionUseVertical.setPosition((float)indexEX * (float)explosionWidth, (float)indexEY + 6.0f * (float)explosionHeight); //indiceY = 1
	portionUseVertical.setSize(sf::Vector2f((float)explosionWidth, (float)explosionHeight));
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
	if (grid[( + 50) / 50][x / 50] == 3)
	{
		grid[( + 50) / 50][x / 50] = 2;
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
		sf::RectangleShape porcionUsarPuntaInferior;
		porcionUsarPuntaInferior.setPosition((float)indexEX * (float)explosionWidth, (float)indexEY + 7.0f * (float)explosionHeight); //indiceY = 7
		porcionUsarPuntaInferior.setSize(sf::Vector2f((float)explosionWidth, (float)explosionHeight));
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