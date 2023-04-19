#pragma once
#include "TextureLibrary.h"

std::array<sf::Texture, 9>* TextureLibrary::explosionTextures = nullptr;
std::array<sf::Texture, 3>* TextureLibrary::bombTextures = nullptr;
std::array<sf::Texture, 3>* TextureLibrary::terrainTextures = nullptr;
std::array<sf::Texture, 4>* TextureLibrary::player1Textures = nullptr;
std::array<sf::Texture, 4>* TextureLibrary::player2Textures = nullptr;

void TextureLibrary::InitTextures()
{
	explosionTextures = new std::array<sf::Texture, 9>();
	bombTextures = new std::array<sf::Texture, 3>();
	terrainTextures = new std::array<sf::Texture, 3>();
	player1Textures = new std::array<sf::Texture, 4>();
	player2Textures = new std::array<sf::Texture, 4>();

	terrainTextures->at(0).loadFromFile("Assets\\Textures\\Terrain\\brick.png");
	terrainTextures->at(1).loadFromFile("Assets\\Textures\\Terrain\\crate.png");
	terrainTextures->at(2).loadFromFile("Assets\\Textures\\Terrain\\grass.png");

	bombTextures->at(0).loadFromFile("Assets\\Textures\\Bomb\\Bomb-0.png");
	bombTextures->at(1).loadFromFile("Assets\\Textures\\Bomb\\Bomb-1.png");
	bombTextures->at(2).loadFromFile("Assets\\Textures\\Bomb\\Bomb-2.png");

	explosionTextures->at(0).loadFromFile("Assets\\Textures\\Bomb\\Explosion-0.png");
	explosionTextures->at(1).loadFromFile("Assets\\Textures\\Bomb\\Explosion-1.png");
	explosionTextures->at(2).loadFromFile("Assets\\Textures\\Bomb\\Explosion-2.png");
	explosionTextures->at(3).loadFromFile("Assets\\Textures\\Bomb\\Explosion-3.png");
	explosionTextures->at(4).loadFromFile("Assets\\Textures\\Bomb\\Explosion-4.png");
	explosionTextures->at(5).loadFromFile("Assets\\Textures\\Bomb\\Explosion-5.png");
	explosionTextures->at(6).loadFromFile("Assets\\Textures\\Bomb\\Explosion-6.png");
	explosionTextures->at(7).loadFromFile("Assets\\Textures\\Bomb\\Explosion-7.png");
	explosionTextures->at(8).loadFromFile("Assets\\Textures\\Bomb\\Explosion-8.png");

	player1Textures->at(0).loadFromFile("Assets\\Textures\\Player1\\P1_up.png");
	player1Textures->at(1).loadFromFile("Assets\\Textures\\Player1\\P1_down.png");
	player1Textures->at(2).loadFromFile("Assets\\Textures\\Player1\\P1_left.png");
	player1Textures->at(3).loadFromFile("Assets\\Textures\\Player1\\P1_right.png");

	player2Textures->at(0).loadFromFile("Assets\\Textures\\Player2\\P2_up.png");
	player2Textures->at(1).loadFromFile("Assets\\Textures\\Player2\\P2_down.png");
	player2Textures->at(2).loadFromFile("Assets\\Textures\\Player2\\P2_left.png");
	player2Textures->at(3).loadFromFile("Assets\\Textures\\Player2\\P2_right.png");
}