#include "Player.h"

Player::Player()
{
	bombArray = new BombArray();
	LateStart();

#ifdef _DEBUG
	rectangleLeftRight.setSize(sf::Vector2f(40, 40));
	rectangleUpDown.setSize(sf::Vector2f(40, 40));
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

void Player::LateStart()
{
	rectangleIndicator.setPosition(position.x - 20.0f, position.y + 30.0f);
	indicator.setPosition(position.x - 25.0f, position.y + 25.0f);
	direction = Down;
	dir = 4;
}

void Player::Update()
{
	BombThrowing();
	UpdateDirection();
	PlayerMovement(playerSprite);
	PlayerTakeDamage();
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


#ifdef _DEBUG
	rectangleLeftRight.setPosition(position.x - 20.0f + movementValue.x, position.y - 15.0f);
	rectangleUpDown.setPosition(position.x - 20.0f, position.y - 15.0f + movementValue.y);
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

void Player::HitByExplosion(int leftTip, int RightTip, int bottomTip, int topTip, int centerStartX, int centerEndX, int centerStartY, int centerEndY)
{
	if (position.x >= leftTip && position.x <= RightTip && position.y >= centerStartY && position.y <= centerEndY)
	{
		// Die
		PlayerDead = true;
	}
	if (position.y >= topTip && position.y <= bottomTip && position.x >= centerStartX && position.x <= centerEndX)
	{
		// Die
		PlayerDead = true;
	}
}

void Player::PlayerTakeDamage()
{
	int leftTip, RightTip, bottomTip, topTip, centerStartX, centerEndX, centerStartY, centerEndY;

	int arraySize = bombArray->GetBombArray().size();
	for (int i = 0; i < arraySize; i++)
	{
		leftTip = bombArray->GetBombArray().at(i)->GetX() - 130;
		RightTip = bombArray->GetBombArray().at(i)->GetX() + 130;
		topTip = bombArray->GetBombArray().at(i)->GetY() - 130;
		bottomTip = bombArray->GetBombArray().at(i)->GetY() + 130;
		centerStartX = bombArray->GetBombArray().at(i)->GetX() - 27;
		centerEndX = bombArray->GetBombArray().at(i)->GetX() + 27;
		centerStartY = bombArray->GetBombArray().at(i)->GetY() - 27;
		centerEndY = bombArray->GetBombArray().at(i)->GetY() + 27;

		if (bombArray->GetBombArray().at(i)->GetState() == Bomb::explode)
		{
			HitByExplosion(leftTip, RightTip, bottomTip, topTip, centerStartX, centerEndX, centerStartY, centerEndY);
		}
	}
}

void Player::PlayerMovement(sf::Sprite& player)
{
	/*
	@return void

	*/

	// Move player
	if (!keyPressed)
	{
		switch (direction)
		{
		case Up:
			movementValue.x = 0.0f;
			movementValue.y = -3.0f;
			lastDirection = direction;
			break;

		case Down:
			movementValue.x = 0.0f;
			movementValue.y = 3.0f;
			lastDirection = direction;
			break;
		case Left:
			movementValue.x = -3.0f;
			movementValue.y = 0.0f;
			lastDirection = direction;
			break;

		case Right:
			movementValue.x = 3.0f;
			movementValue.y = 0.0f;
			lastDirection = direction;
			break;

		case None:
			movementValue.x = 0.0f;
			movementValue.y = 0.0f;
			break;
		}
	}
	else
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

Player::Direction Player::GetPlayerDirection()
{
	return lastDirection;
}

int Player::SetDirectionToInt()
{
	GetPlayerDirection();
	if (lastDirection == Up)
	{
		dir = 0;
	}
	if (lastDirection == Left)
	{
		dir = 1;
	}
	if (lastDirection == Down)
	{
		dir = 2;
	}
	if (lastDirection == Right)
	{
		dir = 3;
	}
	if (lastDirection == None)
	{
		dir = 4;
	}
	return dir;
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

void Player::AddBomb(int x, int y)
{
	bombArray->InitBomb((int)position.x + x, (int)position.y + y);
}