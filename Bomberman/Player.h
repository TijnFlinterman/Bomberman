#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "PlayerInput.h"
#include "Game.h"
#include "BombArray.h"
#include <array>

class BombArray;

class Player
{
private:
	enum Direction
	{
		Up, Down, Left, Right, None
	};
	Direction direction = Down;
	Direction lastDirection = Down;

public:
	// Constructors/ Destructors
	Player();
	virtual ~Player();

	// Public functions
	void LateStart();
	void Update();
	void Render(sf::RenderTarget& target);
	void RenderPlayer(sf::RenderTarget& target);

	void SetPlayerInput(PlayerInput input) { playerInput = input; }
	void SetSpriteTextures(std::array<sf::Texture, 4> textures);

	// Private functions
	void SpawnPlayer(sf::Vector2i spawnPosition);
	void SetDirectionVisual();

	void PlayerCollision(int** grid , sf::RenderTarget& target);
	void AddBomb(int x, int y);
	void HitByExplosion(int leftTip, int RightTip, int bottomTip, int topTip, int centerStartX, int centerEndX, int centerStartY, int centerEndY);
	void PlayerTakeDamage();

private:
	void BombThrowing();
	void UpdateDirection();
	void PlayerMovement(sf::Sprite& player);
	int SetDirectionToInt();

	Direction GetPlayerDirection();

public:
	// Public variables
	bool PlayerDead = false;

	sf::Sprite playerSprite;
	sf::Sprite indicator;

private:
	// Private variables
	bool keyPressed = false;
	bool hasSpawned;
	bool SpaceDown;
	bool canRangeThrow;
	int directionToInt;

	PlayerInput playerInput;

	BombArray* bombArray;

	sf::Texture	upTexture;
	sf::Texture	downTexture;
	sf::Texture	leftTexture;
	sf::Texture	rightTexture;

	sf::Vector2i position;
	sf::Vector2i movementValue;

	sf::RectangleShape	rectangleLeftRight;
	sf::RectangleShape	rectangleUpDown;
	sf::RectangleShape	rectangleIndicator;

	sf::RectangleShape collisionBox;
};