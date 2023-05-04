#pragma once
#include <iostream> // Include the input/output stream library
#include <SFML/Graphics.hpp>  // Include the SFML Graphics library
#include <SFML/Window.hpp> // Include the SFML Window library
#include <SFML/System.hpp> // Include the SFML System library
#include "Player.h" // Include the header file for the Player class
#include "Terrain.h" // Include the header file for the Terrain class
#include <array> // Include the array header from the standard library

/*
	Class that acts as the game engine.
	Wrapper class.
*/

class Bomb;  // Forward declaration of the Bomb
class Player;  // Forward declaration of the Player

class Game
{
public:
	// Constructors/ Destructors
	Game();
	virtual ~Game();

public:
	// Public functions
	void PollEvents();
	void Update();
	void Render();

	Terrain* GetTerrain() { return terrain; }

	//Accessors
	bool Running() const;

private:
	// Private functions
	void InitWindow();
	void InitPlayers();
	void PlayerTextures();
	sf::Text DrawResultText(std::string text);

	// Pointer objects
	Terrain* terrain;
	std::array<Player*, 2> players;

public:
	// Public variables
	static Game* game;

private:
	// Private variables
	sf::Font font;
	sf::Text text;
	// Window
	sf::RenderWindow window;
	sf::VideoMode videoMode;
	sf::Event event;
};