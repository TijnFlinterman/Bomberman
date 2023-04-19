#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "PlayerInput.h"
#include "game.h"
#include "BombArray.h"
#include <array>

class Player
{
public:
	enum Direction
	{
		Up, Down, Left, Right, None
	};

public:
	// Constructors/ Destructors
	Player();
	virtual ~Player();

	// Public functions
	void Update();
	void Render(sf::RenderTarget& target);

	void SetPlayerInput(PlayerInput input) { playerInput = input; }
	void SetSpriteTextures(std::array<sf::Texture, 4> textures);

	// Private functions
	void SpawnPlayer(sf::Vector2f position);
	void BombThrowing();

	void SetDirectionVisual(Direction direction);
	void UpdateDirection();
	void PlayerMovement(sf::Sprite& player);
	void PlayerInputBomb(sf::Keyboard::Key bombInput);

	void PlayerCollision(int** grid);
	void AddBomb();

	// Public variables
	int playerPoints;

private:
	// Private variables
	bool hasSpawned;
	bool playerIsTrowing;

	PlayerInput playerInput;

	BombArray* bombArray;

	Direction direction = Down;
	Direction lastDirection;

	sf::Sprite playerSprite;

	sf::Texture	upTexture;
	sf::Texture	downTexture;
	sf::Texture	leftTexture;
	sf::Texture	rightTexture;

	sf::Vector2f position;
	sf::Vector2f movementValue;

	sf::RectangleShape	rectangleLeftRight;
	sf::RectangleShape	rectangleUpDown;

	sf::RectangleShape collisionBox;
};