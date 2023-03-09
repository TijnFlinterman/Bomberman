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
		Up, Down, Left, Right, Still
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

	bool playerLeft = false;
	bool playerRight = false;
	bool playerUp = false;
	bool playerDown = false;

	int keyPlayer = 3;

	Direction direction = Down;

	sf::Sprite playerSprite;

	sf::Texture	upTexture;
	sf::Texture	downTexture;
	sf::Texture	leftTexture;
	sf::Texture	rightTexture;

	sf::Vector2f position;

	sf::RectangleShape	rectangleLeftRight;
	sf::RectangleShape	rectangleUpDown;
};