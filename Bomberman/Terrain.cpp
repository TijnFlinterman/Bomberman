#include "Terrain.h"  // Include the header file for the Terrain class

// Constructors/ Destructors
Terrain::Terrain()
{
	grid = new int* [rows];
	GenerateGrid();
}
Terrain::~Terrain() {}

// Public functions
void Terrain::Render(sf::RenderTarget& target)
{
	solidSprite.setTexture(TextureLibrary::terrainTextures->at(0));
	breakableSprite.setTexture(TextureLibrary::terrainTextures->at(1));
	grassSprite.setTexture(TextureLibrary::terrainTextures->at(2));

	int x, y = 0;

	for (int a = 0; a < rows; a++)
	{
		x = 0;
		for (int b = 0; b < columns; b++)
		{
			if (grid[a][b] == 0 || grid[a][b] == 2)
			{
				grassSprite.setScale(3.2f, 3.2f);
				grassSprite.setPosition((float)x, (float)y);
				target.draw(grassSprite);
			}
			if (grid[a][b] == 1)
			{
				solidSprite.setScale(3.2f, 3.2f);
				solidSprite.setPosition((float)x, (float)y);
				target.draw(solidSprite);
			}
			if (grid[a][b] == 2)
			{
				breakableSprite.setScale(3.2f, 3.2f);
				breakableSprite.setPosition((float)x, (float)y);
				target.draw(breakableSprite);
			}
			x += 50;
		}
		y += 50;
	}
}
int** Terrain::GetGrid()
{
	return grid;
}

// Private functions
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