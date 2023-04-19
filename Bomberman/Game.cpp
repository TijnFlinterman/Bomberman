#include "Game.h"

Game* Game::game = nullptr;

// Private functions
void Game::InitWindow()
{
	videoMode.height = 1080;
	videoMode.width = 1920;
	window.create(sf::VideoMode(videoMode), "BouncyBombs", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);
}

void Game::InitPlayers()
{
	{
		// Player 1.
		PlayerInput input;
		input.up = sf::Keyboard::Key::W;
		input.left = sf::Keyboard::Key::A;
		input.down = sf::Keyboard::Key::S;
		input.right = sf::Keyboard::Key::D;

		players[0] = new Player();
		players[0]->SetPlayerInput(input);
	}

	{
		// Player 2.
		PlayerInput input;
		input.up = sf::Keyboard::Key::Up;
		input.left = sf::Keyboard::Key::Left;
		input.down = sf::Keyboard::Key::Down;
		input.right = sf::Keyboard::Key::Right;

		players[1] = new Player();
		players[1]->SetPlayerInput(input);
	}
}

void Game::PlayerTextures()
{
	{
		std::array<std::string, 4> textures;
		textures[0] = "Assets/Textures/Player1/P1_up.png";
		textures[1] = "Assets/Textures/Player1/P1_down.png";
		textures[2] = "Assets/Textures/Player1/P1_left.png";
		textures[3] = "Assets/Textures/Player1/P1_right.png";

		players[0]->SetSpriteTextures(textures);
	}

	{
		std::array<std::string, 4> textures;
		textures[0] = "Assets/Textures/Player2/P2_up.png";
		textures[1] = "Assets/Textures/Player2/P2_down.png";
		textures[2] = "Assets/Textures/Player2/P2_left.png";
		textures[3] = "Assets/Textures/Player2/P2_right.png";

		players[1]->SetSpriteTextures(textures);
	}
}

// Constructors/ Destructors
Game::Game()
{
	TextureLibrary::InitTextures();

	terrain = new Terrain();
	game = this;
	sfmlTimer = sf::Clock();
	elapsedTime = 0;
	deltaTime = 0;
	timeScale = 1;


	InitWindow();
	InitPlayers();
	PlayerTextures();

	players[0]->SpawnPlayer(sf::Vector2f(50.0f, 49.0f));
	players[1]->SpawnPlayer(sf::Vector2f(650.0f, 649.0f));
}

Game::~Game()
{
}

//Accessors
bool Game::Running() const
{
	return window.isOpen();
}

// Fuctions
void Game::PollEvents()
{
	// Event polling
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			break;
		}
	}
}

void Game::Update()
{
	PollEvents();

	players[0]->PlayerInputBomb(sf::Keyboard::Key::Space);
	players[1]->PlayerInputBomb(sf::Keyboard::Key::Enter);

	players[0]->Update();
	players[1]->Update();
}

void Game::Render()
{
	/*
	@return void
	- clear old frame
	- render terrain
	- render players
	- display frame in window

	Renders the game objects
	*/

	window.clear();

	// Draw level
	terrain->Render(window);

	// Draw players
	players[0]->Render(window);
	players[1]->Render(window);

	window.display();
}