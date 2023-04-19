#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class TextureLibrary
{
public:
	// Constructors/ Destructors
	static void InitTextures();

	static std::array<sf::Texture, 9>* explosionTextures;
	static std::array<sf::Texture, 3>* bombTextures;
	static std::array<sf::Texture, 3>* terrainTextures;
	static std::array<sf::Texture, 4>* player1Textures;
	static std::array<sf::Texture, 4>* player2Textures;
};