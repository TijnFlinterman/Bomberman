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

class Game
{
private:
	// Private functions
	void InitWindow();
	void InitPlayers();
	void PlayerTextures();

	//Player1* player1;
	std::array<Player, 2> players;
	Terrain terrain;

public:
	// Constructors/ Destructors
	Game();

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
};