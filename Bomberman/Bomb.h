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

	struct ExplosionTextures
	{
		sf::Texture explosionTexture0;
		sf::Texture explosionTexture1;
		sf::Texture explosionTexture2;
		sf::Texture explosionTexture3;
		sf::Texture explosionTexture4;
		sf::Texture explosionTexture5;
		sf::Texture explosionTexture6;
		sf::Texture explosionTexture7;
		sf::Texture explosionTexture8;
	};


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

	int height;
	int width;

	int movementX;
	int movementY;

	int timeToExplode;

	State state;

	// Explosion variables
	int indexEX;
	int indexEY;

	int explosionHeight;
	int explosionWidth;
};