#pragma once
#include "TextureLibrary.h"

std::array<sf::Texture, 9> TextureLibrary::explosionTextures;
std::array<sf::Texture, 3> TextureLibrary::bombTextures;
std::array<sf::Texture, 3> TextureLibrary::terrainTextures;
std::array<sf::Texture, 4> TextureLibrary::player1Textures;
std::array<sf::Texture, 4> TextureLibrary::player2Textures;

void TextureLibrary::InitTextures()
{
	terrainTextures[0].loadFromFile("Assets\\Textures\\Terrain\\brick.png");
	terrainTextures[1].loadFromFile("Assets\\Textures\\Terrain\\crate.png");
	terrainTextures[2].loadFromFile("Assets\\Textures\\Terrain\\grass.png");

	bombTextures[0].loadFromFile("Assets\\Textures\\Bomb\\Bomb-0.png");
	bombTextures[1].loadFromFile("Assets\\Textures\\Bomb\\Bomb-1.png");
	bombTextures[2].loadFromFile("Assets\\Textures\\Bomb\\Bomb-2.png");

	explosionTextures[0].loadFromFile("Assets\\Textures\\Bomb\\Explosion-0.png");
	explosionTextures[1].loadFromFile("Assets\\Textures\\Bomb\\Explosion-1.png");
	explosionTextures[2].loadFromFile("Assets\\Textures\\Bomb\\Explosion-2.png");
	explosionTextures[3].loadFromFile("Assets\\Textures\\Bomb\\Explosion-3.png");
	explosionTextures[4].loadFromFile("Assets\\Textures\\Bomb\\Explosion-4.png");
	explosionTextures[5].loadFromFile("Assets\\Textures\\Bomb\\Explosion-5.png");
	explosionTextures[6].loadFromFile("Assets\\Textures\\Bomb\\Explosion-6.png");
	explosionTextures[7].loadFromFile("Assets\\Textures\\Bomb\\Explosion-7.png");
	explosionTextures[8].loadFromFile("Assets\\Textures\\Bomb\\Explosion-8.png");
}