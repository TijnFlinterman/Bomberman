#pragma once
#include <iostream> // Include the input/output stream library
#include <array> // Include the array header from the standard library
#include <SFML/Graphics.hpp> // Include the SFML Graphics library
#include "Game.h" // Include the header file for the Game class
#include "BombArray.h" // Include the header file for the BombArray class
#include "PlayerInput.h" // Include the header file for the PlayerInput class
#include "BombCollisionStruct.h" // Include the header file for the BombCollisionStruct class

class BombArray; // Forward Declaration of the BombArray

class Player
{
private:
	enum Direction // Enumeration that represent the four cardinal directions with additional constant "None"
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

	void SpawnPlayer(sf::Vector2f spawnPosition);
	void SetPlayerInput(PlayerInput input) { playerInput = input; }
	void SetSpriteTextures(std::array<sf::Texture, 4> textures);
	void SetDirectionVisual();

	BombCollisionStruct GetBombCollisionStruct();
	void HitByExplosion(int leftTip, int RightTip, int bottomTip, int topTip, int centerStartX, int centerEndX, int centerStartY, int centerEndY);

private:
	// Private functions
	void UpdateDirection();
	void PlayerMovement(sf::Sprite& player);
	Direction GetPlayerDirection();



	void PlayerCollision(int** grid , sf::RenderTarget& target);
	void BombThrowing();
	void AddBomb(int x, int y);

	int SetDirectionToInt();

public:
	// Public variables
	bool PlayerDead = false;

	sf::Sprite playerSprite;
	sf::Sprite indicator;

private:
	// Private variables
	bool keyPressed = false;
	bool hasSpawned;
	bool canRangeThrow;
	int bombDirection;

	// Pointer objects
	PlayerInput playerInput;
	BombArray* bombArray;
	struct BombCollider;

	sf::Texture	upTexture;
	sf::Texture	downTexture;
	sf::Texture	leftTexture;
	sf::Texture	rightTexture;

	sf::Vector2f position;
	sf::Vector2f movementValue;

	sf::RectangleShape	rectangleLeftRight;
	sf::RectangleShape	rectangleUpDown;
	sf::RectangleShape	rectangleIndicator;

	sf::RectangleShape collisionBox;
};