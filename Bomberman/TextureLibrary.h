#pragma once
#include <SFML/Graphics.hpp> // Include the SFML Graphics library
#include <array> // Include the array header from the standard library

class TextureLibrary
{
public:
	// Public functions
	static void InitTextures();

	static std::array<sf::Texture, 9>* explosionTextures; // Declares a static pointer variable with 9 object
	static std::array<sf::Texture, 3>* bombTextures; // Declares a static pointer variable with 3 object
	static std::array<sf::Texture, 3>* terrainTextures;  // Declares a static pointer variable with 3 object
	static std::array<sf::Texture, 4>* player1Textures;  // Declares a static pointer variable with 4 object
	static std::array<sf::Texture, 4>* player2Textures;  // Declares a static pointer variable with 4 object
	static std::array<sf::Texture, 2>* indicatorTextures;  // Declares a static pointer variable with 2 object
};