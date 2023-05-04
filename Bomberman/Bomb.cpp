#include "Bomb.h"  // Include the header file for the Bomb class

// Constructors/ Destructors
Bomb::Bomb(int x, int y)
{
	state = bomb1;
	bombDirection = 4;
	this->x = x;
	this->y = y;

	bombSprite.setPosition((float)x, (float)y);
	bombSprite.setScale(3.2f, 3.2f);
	bombCollisionBox.setSize(sf::Vector2f(39.0f, 39.0f));
	bombCollisionBox.setFillColor(sf::Color::Green);
}
Bomb::~Bomb() {}

// Public functions
void Bomb::Render(sf::RenderTarget& target, int direction)
{
	BombCollision(Game::game->GetTerrain()->GetGrid(), target, direction);
	if (canBeThrown)
	{
		MoveBomb();
	}
}

Bomb::State Bomb::GetState()
{
	return state;
}

bool Bomb::ValidateLocation(float xPlayer, float yPlayer, int** grid)
{
	if (grid[(int)yPlayer / 50][(int)xPlayer / 50] == 0 || grid[(int)yPlayer / 50][(int)xPlayer / 50] == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Bomb::DrawBomb1(sf::RenderTarget& target, float xPlayer, float yPlayer, int** grid)
{
	state = bomb1;
	if (ValidateLocation(xPlayer, yPlayer, grid) == true)
	{
		bombSprite.setTexture(TextureLibrary::bombTextures->at(0));
		target.draw(bombSprite);
		myThread = std::thread(&Bomb::AnimateBombAfter1Second1, this);
		myThread.detach();
	}
}
void Bomb::DrawBomb2(sf::RenderTarget& target, float xPlayer, float yPlayer, int** grid)
{
	if (ValidateLocation(xPlayer, yPlayer, grid) == true)
	{
		bombSprite.setTexture(TextureLibrary::bombTextures->at(1));
		target.draw(bombSprite);
		myThread = std::thread(&Bomb::AnimateBombAfter1Second2, this);
		myThread.detach();
	}
}
void Bomb::DrawBomb3(sf::RenderTarget& target, float xPlayer, float yPlayer, int** grid)
{
	if (ValidateLocation(xPlayer, yPlayer, grid) == true)
	{
		bombSprite.setTexture(TextureLibrary::bombTextures->at(2));
		target.draw(bombSprite);
		myThread = std::thread(&Bomb::AnimateBombAfter1Second3, this);
		myThread.detach();
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

	if (grid[y / 50][(x - 50) / 50] != 1)
	{
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

	if (grid[y / 50][(x + 50) / 50] != 1)
	{
		// RIGHT SHAFT
		sf::Sprite sprite;
		sprite.setTexture(TextureLibrary::explosionTextures->at(2));
		sprite.setPosition((float)x + 25.0f, (float)y - 25.0f);
		sprite.setScale(2.5f, 2.5f);
		target.draw(sprite);

		if (grid[y / 50][(x + 50) / 50] == 2)
		{
			grid[y / 50][(x + 50) / 50] = 0;
		}
	}

	if (grid[y / 50][(x + 50) / 50] != 1)
	{
		// RIGHT TIP
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

	if (grid[y / 50][(x - 50) / 50] != 1)
	{
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
void Bomb::AnimateExplosion()
{
	myThread = std::thread(&Bomb::AnimateExplosionAfter1Second, this);
	myThread.detach();
}
void Bomb::BombCollision(int** grid, sf::RenderTarget& target, int direction)
{
	bombCollisionBox.setPosition((float)x - 20.0f, (float)y - 15.0f);
	bombSprite.setPosition((float)x, (float)y);


	if (hasChangedDir == false)
	{
		bombDirection = direction;
		hasChangedDir = true;
	}


#ifdef _DEBUG
	target.draw(bombCollisionBox);
#endif

	float x, y = 0;
	for (int a = 0; a < rows; a++)
	{
		x = 0;
		for (int b = 0; b < columns; b++)
		{
			collisionBox.setPosition(x, y);
			collisionBox.setSize(sf::Vector2f(50, 50));
			if (grid[a][b] == 1 || grid[a][b] == 2)
			{
				if (bombCollisionBox.getGlobalBounds().intersects(collisionBox.getGlobalBounds()))
				{
					switch (bombDirection)
					{
					case 0:
						bombDirection = 2;
						break;
					case 1:
						bombDirection = 3;
						break;
					case 2:
						bombDirection = 0;
						break;
					case 3:
						bombDirection = 1;
						break;
					case 4:
						bombDirection = 4;
						canBeThrown = false;
						break;
					}
				}
			}
			x += 50;
		}
		y += 50;
	}

}
int Bomb::GetX()
{
	return x;
}
int Bomb::GetY()
{
	return y;
}

// Private functions
void Bomb::AnimateExplosionAfter1Second()
{
	sf::sleep(sf::seconds(1));
	state = State::disappear;
}
void Bomb::AnimateBombAfter1Second1()
{
	sf::sleep(sf::seconds(0.5f));
	state = bomb2;
}
void Bomb::AnimateBombAfter1Second2()
{
	sf::sleep(sf::seconds(0.5f));
	state = bomb3;
}
void Bomb::AnimateBombAfter1Second3()
{
	sf::sleep(sf::seconds(0.5f));
	canBeThrown = false;
	state = explode;
}
void Bomb::MoveBomb()
{
	switch (bombDirection)
	{
	case 0:
		movementValue.x = 0;
		movementValue.y = -4;
		break;

	case 1:
		movementValue.x = -4;
		movementValue.y = 0;
		break;
	case 2:
		movementValue.x = 0;
		movementValue.y = 4;
		break;
	case 3:
		movementValue.x = 4;
		movementValue.y = 0;
		break;

	case 4:
		movementValue.x = 0;
		movementValue.y = 0;
		break;
	}
	x += movementValue.x;
	y += movementValue.y;
	bombCollisionBox.move((float)movementValue.x, (float)movementValue.y);
	bombSprite.setPosition(bombCollisionBox.getPosition());
}