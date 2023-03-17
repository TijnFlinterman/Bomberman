#include "Player.h"

Player::Player()
{
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

void Player::PlayerMovement(sf::Sprite& player)
{
	/*
	@return void

	*/

	// Move player
	switch (direction)
	{
	case Up:
		xMovementSpeed = 0.0f;
		yMovementSpeed = -3.0f;
		lastDirection = Up;

		player.move(xMovementSpeed, yMovementSpeed);
		break;
	case Down:
		xMovementSpeed = 0.0f;
		yMovementSpeed = 3.0f;
		lastDirection = Down;

		player.move(xMovementSpeed, yMovementSpeed);
		break;
	case Left:
		xMovementSpeed = -3.0f;
		yMovementSpeed = 0.0f;
		lastDirection = Left;

		player.move(xMovementSpeed, yMovementSpeed);
		break;
	case Right:
		xMovementSpeed = 3.0f;
		yMovementSpeed = 0.0f;
		lastDirection = Right;

		player.move(xMovementSpeed, yMovementSpeed);
		break;
	case None:
		xMovementSpeed = 0.0f;
		yMovementSpeed = 0.0f;

		player.move(xMovementSpeed, yMovementSpeed);
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

void Player::PlayerCollision()
{

	rectangleLeftRight.setPosition(playerSprite.getPosition().x + 5 + xMovementSpeed, playerSprite.getPosition().y + 10);
	rectangleLeftRight.setSize(sf::Vector2f(40, 40));
	rectangleLeftRight.setOutlineColor(sf::Color::Green);
	rectangleLeftRight.setOutlineThickness(1);
	rectangleLeftRight.setFillColor(sf::Color::Transparent);

	rectangleUpDown.setPosition(playerSprite.getPosition().x + 5, playerSprite.getPosition().y + 10 + yMovementSpeed);
	rectangleUpDown.setSize(sf::Vector2f(40, 40));
	rectangleUpDown.setOutlineColor(sf::Color::Red);
	rectangleUpDown.setOutlineThickness(1);
	rectangleUpDown.setFillColor(sf::Color::Transparent);
}

void Player::Update()
{
	BombThrowing();
	UpdateDirection();
	PlayerMovement(playerSprite);
}

void Player::Render(sf::RenderTarget& target)
{
	PlayerCollision();
	SetDirectionVisual(direction);

	target.draw(playerSprite);
	target.draw(rectangleLeftRight);
	target.draw(rectangleUpDown);
}