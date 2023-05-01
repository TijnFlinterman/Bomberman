#pragma once
#include <SFML/Graphics.hpp>
#include "TextureLibrary.h"
#include <iostream>
#include <array>
#include <thread>
#include <windows.h>
#include "terrain.h"
//#include "game.h"


class Bomb
{
public:
	enum State
	{
		bomb1, bomb2, bomb3, explode, disappear
	};

	enum Direction
	{
		Up, Down, Left, Right, None
	};

private:
	bool ValidateLocation(int x, int y, int** grid);
	void AnimateExplosionAfter1Second();
	void AnimateBombAfter1Second1();
	void AnimateBombAfter1Second2();
	void AnimateBombAfter1Second3();

public:
	// Constructors/ Destructors
	Bomb(int x, int y);
	virtual ~Bomb();

	State GetState();

	void Render(sf::RenderTarget& target);

	void DrawBomb1(sf::RenderTarget& target, int xPlayer, int yPlayer, int** grid);
	void DrawBomb2(sf::RenderTarget& target, int xPlayer, int yPlayer, int** grid);
	void DrawBomb3(sf::RenderTarget& target, int xPlayer, int yPlayer, int** grid);
	void DrawExplosion(sf::RenderTarget& target, int** grid, std::array<sf::Texture, 9>* explosionTextures);
	void AnimateExplosion();

	void BombCollision(int** grid, sf::RenderTarget& target);

	int GetX();
	int GetY();

private:
	// Bomb variables
	int x;
	int y;
	sf::Vector2i movementValue;

	sf::Sprite bombSprite;

	Direction direction;

	sf::RectangleShape	rectangleLeftRight;
	sf::RectangleShape	rectangleUpDown;

	State state;
	std::thread myThread;

	sf::RectangleShape collisionBox;
};