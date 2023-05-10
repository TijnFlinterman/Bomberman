#include "Player.h"  // Include the header file for the Player class

// Constructors/ Destructors
Player::Player()
{
	bombArray = new BombArray();
	LateStart();

	rectangleLeftRight.setSize(sf::Vector2f(40, 40));
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
}
Player::~Player() {}

// Public functions
void Player::LateStart()
{
	rectangleIndicator.setPosition(position.x - 20.0f, position.y + 30.0f);
	indicator.setPosition(position.x - 25.0f, position.y + 25.0f);
	direction = Down;
	bombDirection = 4;
}

void Player::Update()
{
	BombThrowing();
	UpdateDirection();
	PlayerMovement(playerSprite);
}

void Player::Render(sf::RenderTarget& target)
{
	SetDirectionVisual();
	playerSprite.setPosition(position.x - 25.0f, position.y - 25.0f);
	bombArray->RenderBombs(target, SetDirectionToInt());
	bombArray->DrawOneBomb(target, position.x, position.y, Game::game->GetTerrain()->GetGrid());

#ifdef _DEBUG
	target.draw(rectangleLeftRight);
	target.draw(rectangleUpDown);
	target.draw(rectangleIndicator);
#endif
}

void Player::RenderPlayer(sf::RenderTarget& target)
{
	PlayerCollision(Game::game->GetTerrain()->GetGrid(), target);
	target.draw(playerSprite);
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

void Player::SetSpriteTextures(std::array<sf::Texture, 4> textures)
{
	upTexture = textures[0];
	downTexture = textures[1];
	leftTexture = textures[2];
	rightTexture = textures[3];
}

void Player::SetDirectionVisual()
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

void Player::HitByExplosion(int leftTip, int RightTip, int bottomTip, int topTip, int centerStartX, int centerEndX, int centerStartY, int centerEndY)
{
	if (position.x >= leftTip && position.x <= RightTip && position.y >= centerStartY && position.y <= centerEndY)
	{
		PlayerDead = true;
	}
	if (position.y >= topTip && position.y <= bottomTip && position.x >= centerStartX && position.x <= centerEndX)
	{
		PlayerDead = true;
	}
}

BombCollisionStruct Player::GetBombCollisionStruct()
{
	int leftTip, RightTip, bottomTip, topTip, centerStartX, centerEndX, centerStartY, centerEndY;
	int arraySize = bombArray->GetBombArray().size();
	const auto& Array = bombArray->GetBombArray();
	for (int i = 0; i < arraySize; i++)
	{
		leftTip = Array[i]->GetX() - 130;
		RightTip = Array[i]->GetX() + 130;
		topTip = Array[i]->GetY() - 130;
		bottomTip = Array[i]->GetY() + 130;
		centerStartX = Array[i]->GetX() - 27;
		centerEndX = Array[i]->GetX() + 27;
		centerStartY = Array[i]->GetY() - 27;
		centerEndY = Array[i]->GetY() + 27;

		if (bombArray->GetBombArray().at(i)->GetState() == Bomb::explode)
		{
			return BombCollisionStruct(leftTip, RightTip, bottomTip, topTip, centerStartX, centerEndX, centerStartY, centerEndY);
		}
	}
	return BombCollisionStruct(-10, -10, -10, -10, -10, -10, -10, -10);
}

// Private functions
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
	// Move player
	if (!keyPressed)
	{
		switch (direction)
		{
		case Up:
			movementValue.x = 0.0f;
			movementValue.y = -3.0f;
			if (canRangeThrow == true)
				lastDirection = direction;
			break;

		case Down:
			movementValue.x = 0.0f;
			movementValue.y = 3.0f;
			if (canRangeThrow == true)
				lastDirection = direction;
			break;
		case Left:
			movementValue.x = -3.0f;
			movementValue.y = 0.0f;
			if (canRangeThrow == true)
				lastDirection = direction;
			break;

		case Right:
			movementValue.x = 3.0f;
			movementValue.y = 0.0f;
			if (canRangeThrow == true)
				lastDirection = direction;
			break;

		case None:
			movementValue.x = 0.0f;
			movementValue.y = 0.0f;
			break;
		}
	}
	if (keyPressed)
	{
		switch (direction)
		{
		case Up:
			movementValue.x = 0.0f;
			movementValue.y = 0.0f;
			lastDirection = direction;
			break;

		case Down:
			movementValue.x = 0.0f;
			movementValue.y = 0.0f;
			lastDirection = direction;
			break;
		case Left:
			movementValue.x = 0.0f;
			movementValue.y = 0.0f;
			lastDirection = direction;
			break;

		case Right:
			movementValue.x = 0.0f;
			movementValue.y = 0.0f;
			lastDirection = direction;
			break;

		case None:
			movementValue.x = 0.0f;
			movementValue.y = 0.0f;
			break;
		}
	}
}

void Player::PlayerCollision(int** grid, sf::RenderTarget& target)
{
	indicator.setScale(3.2f, 3.2f);


	rectangleIndicator.setSize(sf::Vector2f(39.9f, 39.9f));

	switch (direction)
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

	rectangleLeftRight.setPosition(position.x - 20.0f + movementValue.x, position.y - 15.0f);
	rectangleUpDown.setPosition(position.x - 20.0f, position.y - 15.0f + movementValue.y);

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
					lastDirection = None;
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

void Player::BombThrowing()
{
	/*
		@return void

	*/

	// Throw player

	if (sf::Keyboard::isKeyPressed(playerInput.bombThrow))
	{
		if (!keyPressed)
		{
			keyPressed = true;
		}
	}
	else
	{
		if (keyPressed)
		{
			switch (lastDirection)
			{
			case Up:
				AddBomb(0, -50);
				SetDirectionToInt();
				break;
			case Left:
				AddBomb(-50, 0);
				SetDirectionToInt();
				break;
			case Down:
				AddBomb(0, 50);
				SetDirectionToInt();
				break;
			case Right:
				AddBomb(50, 0);
				SetDirectionToInt();
				break;
			case None:
				AddBomb(0, 0);
				SetDirectionToInt();
				break;
			}

			keyPressed = false;
		}
	}
}

void Player::AddBomb(int x, int y)
{
	bombArray->InitBomb((int)position.x + x, (int)position.y + y);
}

Player::Direction Player::GetPlayerDirection()
{
	return lastDirection;
}

int Player::SetDirectionToInt()
{
	GetPlayerDirection();
	if (lastDirection == Up)
	{
		bombDirection = 0;
	}
	if (lastDirection == Left)
	{
		bombDirection = 1;
	}
	if (lastDirection == Down)
	{
		bombDirection = 2;
	}
	if (lastDirection == Right)
	{
		bombDirection = 3;
	}
	if (lastDirection == None)
	{
		bombDirection = 4;
	}
	return bombDirection;
}

int Player::Snap(int value)
{
	int mult = 50;
	if (value < 0)
	{
		mult = -50;
		value = -value;
	}

	return mult * ((value + 25) / 50);
}