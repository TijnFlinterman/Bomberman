#pragma once
#include <SFML/Graphics.hpp>
#include "TextureLibrary.h"
#include <iostream>
#include <array>

class Bomb
{
public:
	enum State
	{
		normal, explode, disappear
	};

private:
	bool ValidateLocation(int x, int y, int** grid);

public:
	// Constructors/ Destructors
	Bomb(int x, int y);
	virtual ~Bomb();

	State GetState();

	void DrawBomb(sf::RenderTarget& target, int xPlayer, int yPlayer, int** grid);
	void DrawExplosion(sf::RenderTarget& target, int** grid, std::array<sf::Texture, 9>* explosionTextures);
	void AnimateExplosion();

private:
	// Bomb variables
	int x;
	int y;

	int timeToExplode;
	int explosionLinger;

	State state;
};