#pragma once
#include <SFML/Graphics.hpp>
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
	void Render(sf::RenderTarget& target);

public:
	// Constructors/ Destructors
	Bomb(int x, int y);
	virtual ~Bomb();

	State GetState();

	void DrawBomb(sf::Texture bombTexture, sf::Texture explosionTexture, int xPlayer, int yPlayer, int** grid);
	void AnimateBomb();
	void DrawExplosion(sf::RenderTarget& target, sf::Texture explosionTexture, int** grid);
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

	int indexX;

	State state;

	// Explosion variables
	int indexEX;
	int indexEY;

	int explosionHeight;
	int explosionWidth;
};