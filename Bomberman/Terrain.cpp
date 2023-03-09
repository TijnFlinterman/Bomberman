#include "Terrain.h"

// Constructors/ Destructors
Terrain::Terrain()
{
	InitVariables();
}

Terrain::~Terrain() {}

void Terrain::InitVariables()
{
	grid = new int* [rows];

	solidTexture.loadFromFile("Assets\\Textures\\brick.png");
	breakableTexture.loadFromFile("Assets\\Textures\\crate.png");
	grassTexture.loadFromFile("Assets\\Textures\\grass.png");
}

void Terrain::Start()
{
	GetGrid();
	GenerateGrid();
}



void Terrain::GenerateGrid()
{
	for (int x = 0; x < rows; x++)
	{
		grid[x] = new int[columns];
	}

	for (int x = 0; x < rows; x++)
	{
		for (int y = 0; y < columns; y++)
		{
			if (x == 0 || y == 0 || x == rows - 1 || y == columns - 1) // edges
			{
				grid[x][y] = 1;
			}
			else
			{
				if (x % 2 == 0 && y % 2 == 0) // fixed interiior  blocks
				{
					grid[x][y] = 1;
				}
				else
				{
					if ((x == 1 && (y == 1 || y == 2)) || (y == 1 && x == 2) || (x == rows - 2 && (y == columns - 3 || y == columns - 2)) || (x == rows - 3 && y == columns - 2)) // walking area
					{
						grid[x][y] = 0;
					}
					else // fills the rest in with breakable blocks
					{
						grid[x][y] = 2;
					}
				}
			}
		}
	}
}

int** Terrain::GetGrid()
{
	return grid;
}

void Terrain::Render(sf::RenderTarget& target)
{
	solid.setTexture(solidTexture);
	breakable.setTexture(breakableTexture);
	grass.setTexture(grassTexture);

	float X, Y = 0.0f;

	for (int a = 0; a < rows; a++)
	{
		X = 0.0f;
		for (int b = 0; b < columns; b++)
		{

			grass.setScale(3.2f, 3.2f);
			grass.setPosition(X, Y);
			target.draw(grass);

			if (grid[a][b] == 1)
			{
				solid.setScale(3.2f, 3.2f);
				solid.setPosition(X, Y);
				target.draw(solid);
			}
			if (grid[a][b] == 2)
			{
				breakable.setScale(3.2f, 3.2f);
				breakable.setPosition(X, Y);
				target.draw(breakable);
			}
			X += 50.0f;
		}
		Y += 50.0f;
	}
}