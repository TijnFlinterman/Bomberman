#pragma once
#include <SFML/Graphics.hpp>
#include "TextureLibrary.h"
#include <iostream>
#include <array>
#include <thread>
#include <windows.h>
#include "Game.h"
#include "Terrain.h"

class Bomb
{
public:
	enum State
	{
		bomb1, bomb2, bomb3, explode, disappear
	};

private:
	bool ValidateLocation(float xPlayer, float yPlayer, int** grid);
	void AnimateExplosionAfter1Second();
	void AnimateBombAfter1Second1();
	void AnimateBombAfter1Second2();
	void AnimateBombAfter1Second3();
	void MoveBomb();

public:
	// Constructors/ Destructors
	Bomb(int x, int y);
	virtual ~Bomb();

	State GetState();

	void Render(sf::RenderTarget& target, int direction);

	void DrawBomb1(sf::RenderTarget& target, float xPlayer, float yPlayer, int** grid);
	void DrawBomb2(sf::RenderTarget& target, float xPlayer, float yPlayer, int** grid);
	void DrawBomb3(sf::RenderTarget& target, float xPlayer, float yPlayer, int** grid);
	void DrawExplosion(sf::RenderTarget& target, int** grid, std::array<sf::Texture, 9>* explosionTextures);
	void AnimateExplosion();

	void BombCollision(int** grid, sf::RenderTarget& target, int direction);

	int GetX();
	int GetY();

private:
	// Bomb variables
	int x;
	int y;

	int dir;
	sf::Vector2f movementValue;
	bool hasChangedDir = false;
	bool canBeThrown = true;

	sf::Sprite bombSprite;

	sf::RectangleShape	bombCollisionBox;

	State state;
	std::thread myThread;

	sf::RectangleShape collisionBox;
};