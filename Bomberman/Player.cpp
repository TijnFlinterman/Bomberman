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

void Player::PlayerCollision(int** grid)
{
	rectangleLeftRight.setPosition(playerSprite.getPosition().x + 5 + movementValue.x, playerSprite.getPosition().y + 10);
	rectangleLeftRight.setSize(sf::Vector2f(40, 40));
	rectangleLeftRight.setOutlineColor(sf::Color::Green);
	rectangleLeftRight.setOutlineThickness(1);
	rectangleLeftRight.setFillColor(sf::Color::Transparent);

	rectangleUpDown.setPosition(playerSprite.getPosition().x + 5, playerSprite.getPosition().y + 10 + movementValue.y);
	rectangleUpDown.setSize(sf::Vector2f(40, 40));
	rectangleUpDown.setOutlineColor(sf::Color::Red);
	rectangleUpDown.setOutlineThickness(1);
	rectangleUpDown.setFillColor(sf::Color::Transparent);

	float x, y = 0;
	for (int a = 0; a < 15; a++)
	{
		x = 0;
		for (int b = 0; b < 15; b++)
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

void Player::SetSpriteTextures(std::array<std::string, 4> sprites)
{
	upTexture.loadFromFile(sprites[0]);
	downTexture.loadFromFile(sprites[1]);
	leftTexture.loadFromFile(sprites[2]);
	rightTexture.loadFromFile(sprites[3]);
}

void Player::SpawnPlayer(sf::Vector2f position)
{
	playerSprite.setScale(3.2f, 3.2f);
	if (hasSpawned == false)
	{
		this->position = position;
		playerSprite.setPosition(position);
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
	PlayerCollision(Game::game->GetTerrain()->GetGrid());
}

void Player::AddBomb()
{
	bombArray->InitBomb(position.x + 2 * 3, position.y + 15 * 3 + movementValue.y);
}

void Player::Render(sf::RenderTarget& target)
{
	SetDirectionVisual(direction);

	bombArray->DrawOneBomb(target, bombArray->GetBombTexture1(), bombArray->GetBombTexture2(), bombArray->GetBombTexture3(), bombArray->GetExplosionTexture(), position.x, position.y, Game::game->GetTerrain()->GetGrid());

	target.draw(playerSprite);
	target.draw(rectangleLeftRight);
	target.draw(rectangleUpDown);
}