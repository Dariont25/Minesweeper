#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <map>
#include <string>
#include <random>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

class Random
{
	static mt19937 random;
public:
	static int Int(int min, int max);
	static float Float(float min, float max);
};
class TextureFolder //stores the textures
{
	static unordered_map<string, sf::Texture> textures;
	static void ReadTexture(string key);
	
public:
	static sf::Texture& GetTexture(string key);
	static void Clear();

private:
	//hi mom
};

struct Tile
{
	vector <Tile*> surroundingTiles;
	bool isFlag = false;
	bool isBomb = false;
	bool isHidden = true;
	int surroundingMineCount = 0;
	int x_Position;
	int y_Position;
	sf::Sprite flag;
	sf::Sprite bomb;
	sf::Sprite hidden;
	sf::Sprite revealed;
	sf::Sprite number;
	Tile(int xPosition = 0, int yPosition = 0);
	bool CheckBomb();
	void UpdateBomb();
	bool CheckFlag();
	void UpdateFlag();
};
struct GameBoard
{

	sf::RectangleShape background;
	bool win = false;
	bool lose = false;
	bool isGaming = false;
	bool debugMode = false;
	int flagCounter = 0;
	int tilesRevealed = 0;
	int mineCounter = 0;
	int columns = 0;
	int rows = 0;
	int height = 0;
	int width = 0;
	int numOfBombs = 0;
	/*Tile** tiles;*/
	vector<vector<Tile>> tiles;	
	GameBoard();	
	void CreateTiles();
	void CreateMines();
	void CreateNumber();
	void CreateNumberImages();
	void DebugMode();
	void NewGame(int width, int height);
	void Test(vector <char>& vector);
	int CreateTestMines(vector <char>& vector);
	void Reveal(int xPosition, int yPosition);
	void RecursiveReveal(Tile* tile);
	string LoadTestBoard(string board);
};
	
