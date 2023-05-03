#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include "Player.h"
#include "Terrain.h"
#include <array>

/*
	Class that acts as the game engine.
	Wrapper class.
*/
class Bomb;
class Player;

class Game
{
private:
	// Private functions
	void InitWindow();
	void InitPlayers();
	void PlayerTextures();
	sf::Text DrawResultText(std::string text);

	Terrain* terrain;
	std::array<Player*, 2> players;

public:
	// Constructors/ Destructors
	Game();
	virtual ~Game();

	//Accessors
	bool Running() const;

	// Public Functions
	void PollEvents();
	void Update();
	void Render();

private:
	// Window
	sf::RenderWindow window;
	sf::VideoMode videoMode;
	sf::Event event;

	sf::Font font;
	sf::Text text;

public:
	// Public Variables
	static Game* game;

	Terrain* GetTerrain()
	{
		return terrain;
	}
};