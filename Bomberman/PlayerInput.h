#pragma once
#include <SFML/Graphics.hpp>  // Include the SFML Graphics library

struct PlayerInput
{
public:
	// Public variables
	sf::Keyboard::Key up, down, right, left , bombThrow;
};