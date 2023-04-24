#include "Player.h"

Player::Player()
{
	bombArray = new BombArray();
	direction = None;
	lastDirection = Down;
}

Player::~Player() {}

void Player::PlayerInputBomb(sf::Keyboard::Key bombInput)
{

	// Reads throw key(s) is pressed or not
#pragma region BombThrowKey

// Reads if Space/Enter is being held or not
	if (sf::Keyboard::isKeyPressed(bombInput) && !playerIsTrowing)
	{
		playerIsTrowing = true;
	}
	else if (!sf::Keyboard::isKeyPressed(bombInput) && playerIsTrowing)
	{
		playerIsTrowing = false;
	}
#pragma endregion
}

void Player::UpdateDirection()
{

	if (sf::Keyboard::isKeyPressed(playerInput.up))
	{
		direction = Up;
	}
	if (sf::Keyboard::isKeyPressed(playerInput.down))
	{
		direction = Down;
	}
	if (sf::Keyboard::isKeyPressed(playerInput.left))
	{
		direction = Left;
	}
	if (sf::Keyboard::isKeyPressed(playerInput.right))
	{
		direction = Right;
	}
	if (!sf::Keyboard::isKeyPressed(playerInput.up) && !sf::Keyboard::isKeyPressed(playerInput.down) && !sf::Keyboard::isKeyPressed(playerInput.left) && !sf::Keyboard::isKeyPressed(playerInput.right))
	{
		direction = None;
	}
}

void Player::PlayerCollision(int** grid , sf::RenderTarget& target)
{
	indicator.setScale(3.2f, 3.2f);

	rectangleIndicator.setSize(sf::Vector2f(39.9, 39.9));

	switch (lastDirection)
	{
	case Up:
		rectangleIndicator.setPosition(position.x - 20.0f, position.y - 70.0f);
		indicator.setPosition(position.x - 25.0f, position.y - 75.0f);
		break;
	case Down:
		rectangleIndicator.setPosition(position.x - 20.0f, position.y + 30.0f);
		indicator.setPosition(position.x - 25.0f, position.y + 25.0f);
		break;
	case Left:
		rectangleIndicator.setPosition(position.x - 70.0f, position.y - 15.0f);
		indicator.setPosition(position.x - 75.0f, position.y - 25.0f);
		break;
	case Right:
		rectangleIndicator.setPosition(position.x + 30.0f, position.y - 15.0f);
		indicator.setPosition(position.x + 25.0f, position.y - 25.0f);
		break;
	}

	rectangleLeftRight.setPosition(position.x - 20 + movementValue.x, position.y - 15);
	rectangleLeftRight.setSize(sf::Vector2f(40, 40));

	rectangleUpDown.setPosition(position.x - 20, position.y - 15 + movementValue.y);
	rectangleUpDown.setSize(sf::Vector2f(40, 40));


#ifdef _DEBUG
	rectangleLeftRight.setOutlineColor(sf::Color::Green);
	rectangleLeftRight.setOutlineThickness(1);
	rectangleLeftRight.setFillColor(sf::Color::Transparent);

	rectangleUpDown.setOutlineColor(sf::Color::Red);
	rectangleUpDown.setOutlineThickness(1);
	rectangleUpDown.setFillColor(sf::Color::Transparent);

	rectangleIndicator.setOutlineColor(sf::Color::Red);
	rectangleIndicator.setOutlineThickness(1);
	rectangleIndicator.setFillColor(sf::Color::Transparent);
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
				if (rectangleLeftRight.getGlobalBounds().intersects(collisionBox.getGlobalBounds()))
				{
					movementValue.x = 0;
				}

				if (rectangleUpDown.getGlobalBounds().intersects(collisionBox.getGlobalBounds()))
				{
					movementValue.y = 0;
				}
				if (!rectangleIndicator.getGlobalBounds().intersects(collisionBox.getGlobalBounds()))
				{
					indicator.setTexture(TextureLibrary::indicatorTextures->at(0));
					target.draw(indicator);
				}
				else
				{
					indicator.setTexture(TextureLibrary::indicatorTextures->at(1));
					target.draw(indicator);	
				}
			}
			x += 50;
		}
		y += 50;
	}
	position.x += movementValue.x;
	position.y += movementValue.y;
	playerSprite.move(movementValue.x, movementValue.y);
}

void Player::PlayerMovement(sf::Sprite& player)
{
	/*
	@return void

	*/

	// Move player
	if (!playerIsTrowing)
	{
		switch (direction)
		{
		case Up:
			movementValue.x = 0;
			movementValue.y = -3;
			lastDirection = Up;
			break;

		case Down:
			movementValue.x = 0;
			movementValue.y = 3;
			lastDirection = Down;
			break;
		case Left:
			movementValue.x = -3;
			movementValue.y = 0;
			lastDirection = Left;
			break;

		case Right:
			movementValue.x = 3;
			movementValue.y = 0;
			lastDirection = Right;
			break;

		case None:
			movementValue.x = 0;
			movementValue.y = 0;
			break;
		}
	}
	else
	{
		switch (direction)
		{
		case Up:
			movementValue.x = 0;
			movementValue.y = 0;
			break;

		case Down:
			movementValue.x = 0;
			movementValue.y = 0;
			break;
		case Left:
			movementValue.x = 0;
			movementValue.y = 0;
			break;

		case Right:
			movementValue.x = 0;
			movementValue.y = 0;
			break;

		case None:
			movementValue.x = 0;
			movementValue.y = 0;
			break;
		}
	}
}

void Player::SetSpriteTextures(std::array<sf::Texture, 4> textures)
{
	upTexture = textures[0];
	downTexture = textures[1];
	leftTexture = textures[2];
	rightTexture = textures[3];
}

void Player::SpawnPlayer(sf::Vector2f spawnPosition)
{
	playerSprite.setScale(3.2f, 3.2f);
	if (hasSpawned == false)
	{
		this->position = spawnPosition;

		hasSpawned = true;
	}
}

void Player::BombThrowing()
{
	/*
		@return void

	*/

	// Throw player

	if (playerIsTrowing)
	{
		AddBomb();
		switch (direction)
		{
		case Up:
			// throw direction =  up
			std::cout << direction;
			break;
		case Left:
			// throw direction =  left
			std::cout << direction;
			break;
		case Down:
			// throw direction =  down
			std::cout << direction;
			break;
		case Right:
			// throw direction =  right
			std::cout << direction;
			break;
		}
	}
}

void Player::SetDirectionVisual(Direction direction)
{
	switch (lastDirection)
	{
	case Up:
		playerSprite.setTexture(upTexture);
		break;
	case Down:
		playerSprite.setTexture(downTexture);
		break;
	case Left:
		playerSprite.setTexture(leftTexture);
		break;
	case Right:
		playerSprite.setTexture(rightTexture);
		break;
	}
}

void Player::Update()
{
	UpdateDirection();
	PlayerMovement(playerSprite);
	BombThrowing();
}

void Player::AddBomb()
{
	bombArray->InitBomb(position.x, position.y);
}

void Player::Render(sf::RenderTarget& target)
{
	playerSprite.setPosition(position.x - 25.0f, position.y - 25.0f);
	PlayerCollision(Game::game->GetTerrain()->GetGrid() , target);
	SetDirectionVisual(direction);
	bombArray->DrawOneBomb(target, position.x, position.y, Game::game->GetTerrain()->GetGrid());
	target.draw(playerSprite);

#ifdef _DEBUG
	target.draw(rectangleLeftRight);
	target.draw(rectangleUpDown);
	target.draw(rectangleIndicator);
#endif
}