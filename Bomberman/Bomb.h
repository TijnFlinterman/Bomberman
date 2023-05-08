#pragma once
#include <SFML/Graphics.hpp> // Include the SFML Graphics library
#include "TextureLibrary.h" // Include the header file for the TextureLibrary class
#include <iostream> // Include the input/output stream library
#include <array> // Include the array header from the standard library
#include <thread> // Include the thread header from the standard library
#include "Game.h" // Include the header file for the Game class
#include "Terrain.h" // Include the header file for the Terrain class

class Bomb
{
public:
	enum State  // Enumeration that represent the bomb "States"
	{
		bomb1, bomb2, bomb3, explode, disappear
	};

public:
	// Constructors/ Destructors
	Bomb(int x, int y); // When Bomb is initialized is given the player int x and int y value by the player
	virtual ~Bomb();

public:
	// Public functions
	void Render(sf::RenderTarget& target, int direction);
	State GetState();
	void DrawBomb1(sf::RenderTarget& target, float xPlayer, float yPlayer, int** grid);
	void DrawBomb2(sf::RenderTarget& target, float xPlayer, float yPlayer, int** grid);
	void DrawBomb3(sf::RenderTarget& target, float xPlayer, float yPlayer, int** grid);
	void DrawExplosion(sf::RenderTarget& target, int** grid, std::array<sf::Texture, 9>* explosionTextures);
	void AnimateExplosion();
	void BombCollision(int** grid, sf::RenderTarget& target, int direction);
	int GetX();
	int GetY();

private:
	// Private functions
	bool ValidateLocation(float xPlayer, float yPlayer, int** grid);
	void AnimateBombAfter1Second1();
	void AnimateBombAfter1Second2();
	void AnimateBombAfter1Second3();
	void AnimateExplosionAfter1Second();
	void MoveBomb();


private:
	// Private variables
	int x; // Bomb x position
	int y; // Bomb y position

	int bombDirection; // Bomb direction that is a translation of the player "Direction" variable | 0 = Up | 1 = Left | 2 = Down | 3 = Right | 4 = None
	sf::Vector2i movementValue; // Vector 2 that takes 2 integers as a movement value to modify to be added to the bomb position to move
	bool hasChangedDir = false; // Limits that bomb only read the player position off spawn once
	bool canBeThrown = true; // Boolean that if true bomb will not be able to move

	sf::Sprite bombSprite; // Bomb sprite visual

	sf::RectangleShape	bombCollisionBox; // Bomb collisionbox

	State state; 
	std::thread myThread; // Thread that can branch off to manage time without interupting the main game tick.

	sf::RectangleShape collisionBox; // Terrain collisionbox
};