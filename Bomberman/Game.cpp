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
		input.bombThrow = sf::Keyboard::Key::Space;

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
		input.bombThrow = sf::Keyboard::Key::Enter;

		players[1] = new Player();
		players[1]->SetPlayerInput(input);
	}
}

void Game::PlayerTextures()
{
	{
		std::array<sf::Texture, 4> textures;
		textures[0] = TextureLibrary::player1Textures->at(0);
		textures[1] = TextureLibrary::player1Textures->at(1);
		textures[2] = TextureLibrary::player1Textures->at(2);
		textures[3] = TextureLibrary::player1Textures->at(3);

		players[0]->SetSpriteTextures(textures);
	}

	{
		std::array<sf::Texture, 4> textures;
		textures[0] = TextureLibrary::player2Textures->at(0);
		textures[1] = TextureLibrary::player2Textures->at(1);
		textures[2] = TextureLibrary::player2Textures->at(2);
		textures[3] = TextureLibrary::player2Textures->at(3);

		players[1]->SetSpriteTextures(textures);
	}
}

sf::Text Game::DrawResultText(std::string string)
{
	if (!font.loadFromFile("Assets\\Fonts\\Quinquefive-ALoRM.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}


	sf::Text text(string, font, 50);
	text.setPosition(rows*50/2, columns * 50 / 2);
	text.setFillColor(sf::Color::White);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	return text;
}

// Constructors/ Destructors
Game::Game()
{
	TextureLibrary::InitTextures();

	terrain = new Terrain();
	game = this;

	InitWindow();
	InitPlayers();
	PlayerTextures();

	players[0]->SpawnPlayer(sf::Vector2f(75.0f, 74.0f));
	players[1]->SpawnPlayer(sf::Vector2f(675.0f, 674.0f));

	players[0]->SetDirectionVisual();
	players[1]->SetDirectionVisual();

	players[0]->LateStart();
	players[1]->LateStart();
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
	if (!players[0]->PlayerDead && !players[1]->PlayerDead)
	{
		players[0]->Update();
		players[1]->Update();
	}
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

	if (!players[0]->PlayerDead)
	{
		players[0]->RenderPlayer(window);
	}
	else
	{
		window.draw(DrawResultText("RED WINS"));
	}
	if (!players[1]->PlayerDead)
	{
		players[1]->RenderPlayer(window);
	}
	else
	{
		window.draw(DrawResultText("BLUE WINS"));
	}

	window.display();
}