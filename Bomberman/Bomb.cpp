#include "Bomb.h"

Bomb::Bomb(int x, int y)
{
	this->x = x;
	this->y = y;
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

void Bomb::DrawBomb1(sf::RenderTarget& target, int xPlayer, int yPlayer, int** grid)
{
	state = bomb1;
	if (ValidateLocation(xPlayer, yPlayer, grid) == true)
	{
		bombSprite.setPosition((float)x - 25, (float)y - 25);
		bombSprite.setScale(3.2f, 3.2f);
		bombSprite.setTexture(TextureLibrary::bombTextures->at(0));
		target.draw(bombSprite);
		myThread = std::thread(&Bomb::AnimateBombAfter1Second1, this);
		myThread.detach();
	}
}

void Bomb::DrawBomb2(sf::RenderTarget& target, int xPlayer, int yPlayer, int** grid)
{
	if (ValidateLocation(xPlayer, yPlayer, grid) == true)
	{
		bombSprite.setPosition((float)x - 25, (float)y - 25);
		bombSprite.setScale(3.2f, 3.2f);
		bombSprite.setTexture(TextureLibrary::bombTextures->at(1));
		target.draw(bombSprite);
		myThread = std::thread(&Bomb::AnimateBombAfter1Second2, this);
		myThread.detach();
	}
}

void Bomb::DrawBomb3(sf::RenderTarget& target, int xPlayer, int yPlayer, int** grid)
{
	if (ValidateLocation(xPlayer, yPlayer, grid) == true)
	{
		bombSprite.setPosition((float)x - 25, (float)y - 25);
		bombSprite.setScale(3.2f, 3.2f);
		bombSprite.setTexture(TextureLibrary::bombTextures->at(2));
		target.draw(bombSprite);
		myThread = std::thread(&Bomb::AnimateBombAfter1Second3, this);
		myThread.detach();
	}
}

void Bomb::AnimateExplosion()
{
	myThread = std::thread(&Bomb::AnimateExplosionAfter1Second, this);
	myThread.detach();
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

void Bomb::Render(sf::RenderTarget& target)
{
	//BombCollision(Game::game->GetTerrain()->GetGrid(), target);
}

//void Bomb::BombCollision(int** grid, sf::RenderTarget& target)
//{
//	rectangleLeftRight.setPosition(x - 20 + x, y - 15);
//	rectangleLeftRight.setSize(sf::Vector2f(39, 39));
//
//	rectangleUpDown.setPosition(x - 20, y - 15 + y);
//	rectangleUpDown.setSize(sf::Vector2f(39, 39));
//
//
//#ifdef _DEBUG
//	rectangleLeftRight.setOutlineColor(sf::Color::Green);
//	rectangleLeftRight.setOutlineThickness(1);
//	rectangleLeftRight.setFillColor(sf::Color::Transparent);
//
//	rectangleUpDown.setOutlineColor(sf::Color::Red);
//	rectangleUpDown.setOutlineThickness(1);
//	rectangleUpDown.setFillColor(sf::Color::Transparent);
//#endif
//
//	float x, y = 0;
//	for (int a = 0; a < rows; a++)
//	{
//		x = 0;
//		for (int b = 0; b < columns; b++)
//		{
//			collisionBox.setPosition(x, y);
//			collisionBox.setSize(sf::Vector2f(50, 50));
//			if (grid[a][b] == 1 || grid[a][b] == 2)
//			{
//				if (rectangleLeftRight.getGlobalBounds().intersects(collisionBox.getGlobalBounds()) && movementValue.x > 0)
//				{
//					movementValue.x = -2;
//				}
//				if (rectangleLeftRight.getGlobalBounds().intersects(collisionBox.getGlobalBounds()) && movementValue.x < 0)
//				{
//					movementValue.x = 2;
//				}
//
//				if (rectangleUpDown.getGlobalBounds().intersects(collisionBox.getGlobalBounds()) && movementValue.y > 0)
//				{
//					movementValue.y = -2;
//				}
//				if (rectangleUpDown.getGlobalBounds().intersects(collisionBox.getGlobalBounds()) && movementValue.y < 0)
//				{
//					movementValue.y = 2;
//				}
//			}
//			x += 50;
//		}
//		y += 50;
//	}
//	x += movementValue.x;
//	y += movementValue.y;
//	//bombSprite.move(movementValue.x, movementValue.y);
//}

int Bomb::GetX()
{
	return x;
}
int Bomb::GetY()
{
	return y;
}

void Bomb::AnimateExplosionAfter1Second()
{
	sf::sleep(sf::seconds(1));
	state = State::disappear;
}

void Bomb::AnimateBombAfter1Second1()
{
	sf::sleep(sf::seconds(1));
	state = bomb2;
}

void Bomb::AnimateBombAfter1Second2()
{
	sf::sleep(sf::seconds(1));
	state = bomb3;
}

void Bomb::AnimateBombAfter1Second3()
{
	sf::sleep(sf::seconds(1));
	state = explode;
}