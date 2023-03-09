#include "Player.h"

Player::Player() {}

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

		if (!playerUp)
		{
			keyPlayer = 1;
			playerUp = true;
		}
	}
	else if (!sf::Keyboard::isKeyPressed(playerInput.up) && playerUp)
	{
		playerUp = false;
		playerLeft = false;
		playerRight = false;
		playerDown = false;
	}

	if (sf::Keyboard::isKeyPressed(playerInput.left))
	{
		direction = Left;

		if (!playerLeft)
		{
			keyPlayer = 2;
			playerLeft = true;
		}
	}
	else if (!sf::Keyboard::isKeyPressed(playerInput.left) && playerLeft)
	{
		playerLeft = false;
		playerUp = false;
		playerRight = false;
		playerDown = false;
	}

	if (sf::Keyboard::isKeyPressed(playerInput.down))
	{
		direction = Down;

		if (!playerDown)
		{
			keyPlayer = 3;
			playerDown = true;
		}
	}
	else if (!sf::Keyboard::isKeyPressed(playerInput.down) && playerDown)
	{
		playerDown = false;
		playerLeft = false;
		playerRight = false;
		playerUp = false;
	}

	if (sf::Keyboard::isKeyPressed(playerInput.right))
	{
		direction = Right;

		if (!playerRight)
		{
			keyPlayer = 4;
			playerRight = true;
		}
	}
	else if (!sf::Keyboard::isKeyPressed(playerInput.right) && playerRight)
	{
		playerRight = false;
		playerLeft = false;
		playerUp = false;
		playerDown = false;
	}
	if (!sf::Keyboard::isKeyPressed(playerInput.up) && !sf::Keyboard::isKeyPressed(playerInput.left) && !sf::Keyboard::isKeyPressed(playerInput.down) && !sf::Keyboard::isKeyPressed(playerInput.right))
	{
		keyPlayer = 5;
	}
}

void Player::PlayerMovement(sf::Sprite& player)
{
	/*
	@return void

	*/

	// Move player
	switch (keyPlayer)
	{
	case 1:
		player.move(0.0f, -3.0f);
		break;
	case 2:
		player.move(-3.0f, 0.0f);
		break;
	case 3:
		player.move(0.0f, 3.0f);
		break;
	case 4:
		player.move(3.0f, 0.0f);
		break;
	case 5:
		player.move(0.0f, 0.0f);
		break;

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
	switch (direction)
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
	BombThrowing();
	UpdateDirection();
	PlayerMovement(playerSprite);
}

void Player::Render(sf::RenderTarget& target)
{
	SetDirectionVisual(direction);
	target.draw(playerSprite);
}