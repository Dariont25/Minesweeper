#include "BoardSetup.h"
#include <iostream>
#include <ctime>
#include <random>
#include <vector>
using namespace std;

std::mt19937 Random::random(time(0));
int Random::Int(int min, int max) 
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(random);
}
float Random::Float(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(random);
}
unordered_map<string, sf::Texture> TextureFolder::textures;

void TextureFolder::ReadTexture(string file) //adds the correct paths for the images and stores them
{
	string fileLoaded = "images/";
	fileLoaded += file;
	fileLoaded += ".png";

	textures[file].loadFromFile(fileLoaded);
}


sf::Texture& TextureFolder::GetTexture(string texture)
{
	if (textures.find(texture) == textures.end()) //checks to see if the texture is in the map
	{
		ReadTexture(texture);
	}
	return textures[texture]; 
}
void TextureFolder::Clear() //clears the textures
{
	textures.clear();
}
Tile::Tile(int x, int y)
{
	Tile::x_Position = x;
	Tile::y_Position = y;

	sf::Sprite revealedTile(TextureFolder::GetTexture("tile_revealed"));
	revealedTile.setPosition(x, y);
	this->revealed = revealedTile;

	sf::Sprite hiddenTile(TextureFolder::GetTexture("tile_hidden"));
	hiddenTile.setPosition(x, y);
	this->hidden = hiddenTile;

	sf::Sprite bombTile(TextureFolder::GetTexture("mine"));
	bombTile.setPosition(x, y);
	this->bomb = bombTile;

	sf::Sprite flagTile(TextureFolder::GetTexture("flag"));
	flagTile.setPosition(x, y);
	this->flag = flagTile;
}

bool Tile::CheckBomb()
{
	return isBomb;
}
bool Tile::CheckFlag()
{
	return isFlag;
}

void Tile::UpdateBomb()
{
	if (isBomb == true)
	{
		Tile::isBomb = false;
	}
	if (isBomb == false)
	{
		Tile::isBomb = true;
	}
}

void Tile::UpdateFlag()
{
	if (isFlag == true)
	{
		isFlag = false;
	}
	else if (isFlag == false)
	{
		isFlag = true;
	}
}

GameBoard::GameBoard()
{
	background.setSize(sf::Vector2f(width, height));
	background.setFillColor(sf::Color::White);
	CreateTiles();
	CreateMines();
	CreateNumber();
	CreateNumberImages();
	isGaming = true;
}

void GameBoard::CreateTiles()
{
}

void GameBoard::CreateMines()
{
	int bombCount = 0;
	while (bombCount < mineCounter)
	{
		int index_x = Random::Int(0, (rows - 1));
		int index_y = Random::Int(0, (columns - 1));

		if (this->tiles[index_x][index_y].CheckBomb() == false)
		{
			this->tiles[index_x][index_y].UpdateBomb();
			bombCount++;
		}
	}
}

void GameBoard::CreateNumber() 
{
	// Used + or - 1 to check the x and y axis for bombs
	int counter = 0;
	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < columns; j++) 
		{

			if (i == 0 && j == 0) 
			{

				tiles[i][j].surroundingTiles.push_back(&tiles[i][j + 1]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i + 1][j]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i + 1][j + 1]);

				if (this->tiles[i][j + 1].CheckBomb()) 		
					counter++;				
				if (this->tiles[i + 1][j].CheckBomb()) 		
					counter++;				
				if (this->tiles[i + 1][j + 1].CheckBomb()) 		
					counter++;
				
			}
			else if (i == (rows - 1) && j == 0) 
			{

				tiles[i][j].surroundingTiles.push_back(&tiles[i - 1][j]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i - 1][j + 1]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i][j + 1]);

				if (this->tiles[i - 1][j].CheckBomb()) 		
					counter++;				
				if (this->tiles[i - 1][j + 1].CheckBomb()) 		
					counter++;				
				if (this->tiles[i][j + 1].CheckBomb()) 		
					counter++;
				
			}
			else if (i == 0 && j == (columns - 1)) 
			{
				tiles[i][j].surroundingTiles.push_back(&tiles[i][j - 1]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i + 1][j - 1]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i + 1][j]);

				if (this->tiles[i][j - 1].CheckBomb()) 		
					counter++;				
				if (this->tiles[i + 1][j - 1].CheckBomb()) 		
					counter++;				
				if (this->tiles[i + 1][j].CheckBomb()) 		
					counter++;
				

			}
			else if (i == (rows - 1)  && j == (columns - 1)) 
			{
				tiles[i][j].surroundingTiles.push_back(&tiles[i - 1][j - 1]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i - 1][j]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i][j - 1]);

				if (this->tiles[i - 1][j - 1].CheckBomb()) 		
					counter++;				
				if (this->tiles[i - 1][j].CheckBomb())		
					counter++;				
				if (this->tiles[i][j - 1].CheckBomb()) 		
					counter++;	
			}
			else if (i == 0 && j != 0 && j != (columns - 1)) 
			{
				tiles[i][j].surroundingTiles.push_back(&tiles[i][j - 1]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i][j + 1]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i + 1][j - 1]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i + 1][j]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i + 1][j + 1]);

				if (this->tiles[i][j - 1].CheckBomb()) 		
					counter++;				
				if (this->tiles[i][j + 1].CheckBomb()) 		
					counter++;				
				if (this->tiles[i + 1][j - 1].CheckBomb()) 		
					counter++;				
				if (this->tiles[i + 1][j].CheckBomb()) 		
					counter++;				
				if (this->tiles[i + 1][j + 1].CheckBomb()) 		
					counter++;
				
			}
			else if (i == (rows - 1) && j != 0 && j != (columns - 1)) 
			{

				tiles[i][j].surroundingTiles.push_back(&tiles[i - 1][j - 1]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i - 1][j]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i - 1][j + 1]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i][j - 1]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i][j + 1]);

				if (this->tiles[i - 1][j - 1].CheckBomb()) 		
					counter++;				
				if (this->tiles[i - 1][j].CheckBomb()) 		
					counter++;				
				if (this->tiles[i - 1][j + 1].CheckBomb()) 		
					counter++;				
				if (this->tiles[i][j - 1].CheckBomb()) 		
					counter++;				
				if (this->tiles[i][j + 1].CheckBomb()) 		
					counter++;
				
			}
			else if (j == 0 && i != 0 && i != (rows - 1)) 
			{
				tiles[i][j].surroundingTiles.push_back(&tiles[i - 1][j]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i - 1][j + 1]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i][j + 1]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i + 1][j]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i + 1][j + 1]);

				if (this->tiles[i - 1][j].CheckBomb()) 		
					counter++;				
				if (this->tiles[i - 1][j + 1].CheckBomb()) 		
					counter++;				
				if (this->tiles[i][j + 1].CheckBomb()) 		
					counter++;				
				if (this->tiles[i + 1][j].CheckBomb()) 		 
					counter++;				
				if (this->tiles[i + 1][j + 1].CheckBomb()) 		
					counter++;
				

			}
			else if (j == (columns - 1) && i != 0 && i != (rows - 1))
			{
				tiles[i][j].surroundingTiles.push_back(&tiles[i - 1][j - 1]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i - 1][j]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i][j - 1]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i + 1][j - 1]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i + 1][j]);

				if (this->tiles[i - 1][j - 1].CheckBomb()) 		
					counter++;				
				if (this->tiles[i - 1][j].CheckBomb()) 		
					counter++;				
				if (this->tiles[i][j - 1].CheckBomb()) 		
					counter++;				
				if (this->tiles[i + 1][j - 1].CheckBomb()) 		
					counter++;				
				if (this->tiles[i + 1][j].CheckBomb()) 		 
					counter++;				
			}
			else if (i != 0 || j != 0 || i != (rows - 1) || j != (columns - 1)) 
			{

				tiles[i][j].surroundingTiles.push_back(&tiles[i - 1][j - 1]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i - 1][j]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i - 1][j + 1]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i][j - 1]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i][j + 1]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i + 1][j - 1]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i + 1][j]);
				tiles[i][j].surroundingTiles.push_back(&tiles[i + 1][j + 1]);


				if (this->tiles[i - 1][j - 1].CheckBomb()) 		
					counter++;				
				if (this->tiles[i - 1][j].CheckBomb()) 		
					counter++;
				
				if (this->tiles[i - 1][j + 1].CheckBomb()) 		
					counter++;				
				if (this->tiles[i][j - 1].CheckBomb()) 		
					counter++;				
				if (this->tiles[i][j + 1].CheckBomb()) 		
					counter++;				
				if (this->tiles[i + 1][j - 1].CheckBomb()) 		
					counter++;				
				if (this->tiles[i + 1][j].CheckBomb()) 		
					counter++;				
				if (this->tiles[i + 1][j + 1].CheckBomb()) 		
					counter++;
				
			}

			tiles[i][j].surroundingMineCount = counter;
			counter = 0;
		}
	}
}

void GameBoard::CreateNumberImages()
{
	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < columns; j++) 
		{
			if (this->tiles[i][j].surroundingMineCount == 0) 
			{
				Tile temp(tiles[i][j].x_Position, tiles[i][j].y_Position);
				temp.isBomb = tiles[i][j].isBomb;
				temp.isHidden = tiles[i][j].isHidden;
				temp.isFlag = tiles[i][j].isFlag;
				temp.surroundingTiles = tiles[i][j].surroundingTiles;
				tiles[i][j] = temp;
			}

			else if (this->tiles[i][j].surroundingMineCount == 1) 
			{
				sf::Sprite one(TextureFolder::GetTexture("number_1"));
				one.setPosition(tiles[i][j].x_Position, tiles[i][j].y_Position);
				this->tiles[i][j].number = one;
			}
			else if (this->tiles[i][j].surroundingMineCount == 2) 
			{
				sf::Sprite two(TextureFolder::GetTexture("number_2"));
				two.setPosition(tiles[i][j].x_Position, tiles[i][j].y_Position);
				this->tiles[i][j].number = two;
			}
			else if (this->tiles[i][j].surroundingMineCount == 3)
			{
				sf::Sprite three(TextureFolder::GetTexture("number_3"));
				three.setPosition(tiles[i][j].x_Position, tiles[i][j].y_Position);
				this->tiles[i][j].number = three;
			}
			else if (this->tiles[i][j].surroundingMineCount == 4)
			{
				sf::Sprite four(TextureFolder::GetTexture("number_4"));
				four.setPosition(tiles[i][j].x_Position, tiles[i][j].y_Position);
				this->tiles[i][j].number = four;
			}
			else if (this->tiles[i][j].surroundingMineCount == 5)
			{
				sf::Sprite five(TextureFolder::GetTexture("number_5"));
				five.setPosition(tiles[i][j].x_Position, tiles[i][j].y_Position);
				this->tiles[i][j].number = five;
			}
			else if (this->tiles[i][j].surroundingMineCount == 6) 
			{
				sf::Sprite six(TextureFolder::GetTexture("number_6"));
				six.setPosition(tiles[i][j].x_Position, tiles[i][j].y_Position);
				this->tiles[i][j].number = six;
			}
			else if (this->tiles[i][j].surroundingMineCount == 7) 
			{
				sf::Sprite seven(TextureFolder::GetTexture("number_7"));
				seven.setPosition(tiles[i][j].x_Position, tiles[i][j].y_Position);
				this->tiles[i][j].number = seven;
			}
			else if (this->tiles[i][j].surroundingMineCount == 8) 
			{
				sf::Sprite eight(TextureFolder::GetTexture("number_8"));
				eight.setPosition(tiles[i][j].x_Position, tiles[i][j].y_Position);
				this->tiles[i][j].number = eight;
			}
		}
	}
}
void GameBoard::DebugMode() 
{
	if (debugMode) 
	{
		debugMode = false;
	}
	else if (!debugMode) 
	{
		debugMode = true;
	}
}
void GameBoard::NewGame(int width, int height) 
{
	background.setSize(sf::Vector2f(width, height));
	background.setFillColor(sf::Color::White);
	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < columns; j++) 
		{
			
			if (this->tiles[i][j].isBomb)
			{
				this->tiles[i][j].isBomb = false;
			}
			if (this->tiles[i][j].CheckFlag()) 
			{
				this->tiles[i][j].UpdateFlag();
			}
			this->tiles[i][j].isHidden = true;
		}
	}

	CreateMines();
	CreateNumber();
	CreateNumberImages();

	this->isGaming = true;
	this->win = false;
	this->lose = false;
	this->debugMode = false;
	tilesRevealed = 0;
	this->flagCounter = 0;
	mineCounter = numOfBombs;
}
void GameBoard::Test(vector <char>& board) 
{
	board.size();
	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < columns; j++) 
		{
			if (this->tiles[i][j].isBomb) 
			{
				this->tiles[i][j].isBomb = false;
			}
			if (this->tiles[i][j].CheckFlag()) 
			{
				this->tiles[i][j].UpdateFlag();
			}
			this->tiles[i][j].isHidden = true;
		}
	}

	this->mineCounter = CreateTestMines(board);
	CreateNumber();
	CreateNumberImages();

	this->isGaming = true;
	this->win = false;
	this->lose = false;
	this->debugMode = false;
	tilesRevealed = 0;
	int flagCounter = 0;
}
int GameBoard::CreateTestMines(vector <char>& board) 
{
	int bombCount = 0;
	int index = 0;
	for (int i = 0; i < 16; i++) 
	{
		for (int j = 0; j < 25; j++) 
		{
			if (board[index] == '1') //throwing exception on bigger boards
			{
				this->tiles[i][j].isBomb = true;
				bombCount++;
			}
			index++;
		}
	}
	return bombCount;
}
void GameBoard::Reveal(int i, int j) 
{
	if (!tiles[i][j].isFlag) 
	{
		if (tiles[i][j].isHidden == true)
		{
			tilesRevealed++;
		}
		this->tiles[i][j].isHidden = false;
		if (tiles[i][j].surroundingMineCount == 0 && !tiles[i][j].isBomb) 
		{
			RecursiveReveal(&tiles[i][j]);
		}
	}
}
void GameBoard::RecursiveReveal(Tile *tile) 
{
	for (int x = 0; x < tile->surroundingTiles.size(); x++) 
	{
		if (!tile->surroundingTiles[x]->isFlag && tile->surroundingTiles[x]->isHidden == true) 
		{		
			if (tile->surroundingTiles[x]->isHidden == true) 
			{
				tilesRevealed++;
				tile->surroundingTiles[x]->isHidden = false;
			}
			if (tile->surroundingTiles[x]->surroundingMineCount == 0) 
			{
				RecursiveReveal(tile->surroundingTiles[x]);
			}
		}
	}
}

string GameBoard::LoadTestBoard(string board)
{
	string boardName = "boards/";
	boardName += board;
	boardName += ".brd";

	return boardName;
}


// GameBoard::GameBoard() //create the gameboard
//{
//	 background.setSize(sf::Vector2f())
//}
//
//


