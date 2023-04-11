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

	Terrain* terrain;
	Game* game;
	std::array<Player, 2> players;

	sf::Clock sfmlTimer;
	float deltaTime;
	float elapsedTime;
	float timeScale;
	float realDeltaTime;

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
};