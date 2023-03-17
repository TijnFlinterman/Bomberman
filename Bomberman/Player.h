#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "PlayerInput.h"
#include <array>

class Player
{
public:
	enum Direction
	{
		Up, Down, Left, Right, None
	};

public:
	// Public functions
	void Update();
	void Render(sf::RenderTarget& target);


	void SetPlayerInput(PlayerInput input) { playerInput = input; }
	void SetSpriteTextures(std::array<std::string, 4> sprites);

	// Private functions
	void SpawnPlayer(sf::Vector2f position);
	void BombThrowing();

	void SetDirectionVisual(Direction direction);
	void PlayerMovement(sf::Sprite& player);
	void PlayerInputBomb(sf::Keyboard::Key bombInput);
	void UpdateDirection();

	void PlayerCollision();
public:
	// Constructors/ Destructors
	Player();
	virtual ~Player();

	// Public variables
	int playerPoints;

private:
	// Private variables
	bool hasSpawned;
	bool playerIsTrowing;

	PlayerInput playerInput;

	Direction direction = Down;
	Direction lastDirection;

	sf::Sprite playerSprite;

	sf::Texture	upTexture;
	sf::Texture	downTexture;
	sf::Texture	leftTexture;
	sf::Texture	rightTexture;

	sf::Vector2f position;

	float xMovementSpeed;
	float yMovementSpeed;

	sf::RectangleShape	rectangleLeftRight;
	sf::RectangleShape	rectangleUpDown;
};