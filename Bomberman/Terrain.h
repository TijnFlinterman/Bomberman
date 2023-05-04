#pragma once
#include <SFML/Graphics.hpp> // Include the SFML Graphics library
#include "TextureLibrary.h" // Include the header file for the TextureLibrary class
#include <iostream> // Include the input/output stream library

#define rows 15 // Define "rows" to integer of 15 to use in easier to read code
#define columns 15 // Define "columns" to integer of 15 to use in easier to read code

class Terrain
{
public:
	// Constructors/ Destructors
	Terrain();
	virtual ~Terrain();

public:
	// Public functions
	void Render(sf::RenderTarget& target);
	int** GetGrid();

private:
	// Private functions
	void GenerateGrid();

private:
	//private variables
	int** grid;
	sf::Sprite solidSprite;
	sf::Sprite breakableSprite;
	sf::Sprite grassSprite;
};