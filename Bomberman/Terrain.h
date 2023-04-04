#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <stdlib.h>
#include <iostream>

#define rows 15
#define columns 15

class Terrain
{
public:
	// Constructors/ Destructors
	Terrain();
	virtual ~Terrain();

	// Public functions
	int** GetGrid();

	void GenerateGrid();
	void Start();
	void Render(sf::RenderTarget& target);

private:
	// Private functions
	void InitVariables();

private:
	//private variables
	int** grid;
	sf::Texture	solidTexture;
	sf::Texture	breakableTexture;
	sf::Texture	grassTexture;

public:
	//public variables
	sf::Sprite solid;
	sf::Sprite breakable;
	sf::Sprite grass;
};