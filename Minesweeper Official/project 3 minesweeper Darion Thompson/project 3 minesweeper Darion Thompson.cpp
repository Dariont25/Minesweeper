#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "BoardSetup.h"
using namespace std;

int main()
{
    
    GameBoard* Board = new GameBoard;
    
     
        
        
        int width = 0;
        int height = 0;
        int numBombs = 0;
        int rows = 0;
        int columns = 0;
    
    // 1. Read the config file to determine the size of the board and the the amount of mines
  
   
        ifstream defaultBoard("boards/config.cfg");
        if (defaultBoard.is_open())
        {
           
            string columnString;
            string rowsString;
            string numBombsString;
            getline(defaultBoard, columnString);
            columns = stoi(columnString);
            width = columns * 32;

            getline(defaultBoard, rowsString);
            rows = stoi(rowsString);
            height = (rows * 32) + 88;
            
            getline(defaultBoard, numBombsString);
            numBombs = stoi(numBombsString);

            cout << "Minesweeper is running!" << endl;
            

            Board->mineCounter = numBombs;
            Board->numOfBombs = numBombs;
            Board->rows = rows;
            Board->columns = columns;
            Board->width = width;
            Board->height = height;

            
            defaultBoard.close();
        }
        else if (!defaultBoard.is_open())
        {
            cout << "Cannot open the file" << endl;
        }
        int position_x = 0, position_y = 0;
        for (int i = 0; i < rows; i++) 
        {
            vector<Tile> a;
            for (int j = 0; j < columns; j++)
            {
                a.push_back(Tile(position_x, position_y));
                position_x += 32;
            }
            Board->tiles.push_back(a);
            position_x = 0;
            position_y += 32;
        }
       
       
        Board->NewGame(width, height);
    
  // 2. Load all the images and set positions
    
    sf::Sprite bomb(TextureFolder::GetTexture("mine"));
    sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper!"); //updates the window size
    sf::Image mineImage;
    mineImage.loadFromFile("images/mine.png");
    window.setIcon(32, 32, mineImage.getPixelsPtr());

    sf::Sprite flagBomb(TextureFolder::GetTexture("flag"));
    sf::Sprite happy(TextureFolder::GetTexture("face_happy"));
    //happy.setPosition((368), 512);
    happy.setPosition(((columns * 32) / 2) - 64, rows * 32);

    sf::Sprite lose(TextureFolder::GetTexture("face_lose"));
    lose.setPosition(((columns * 32) / 2) - 64, rows * 32);

    sf::Sprite win(TextureFolder::GetTexture("face_win"));
    win.setPosition(((columns * 32) / 2) - 64, rows * 32);

    sf::Sprite debug(TextureFolder::GetTexture("debug"));
    debug.setPosition(((columns * 32) / 2) + 64, rows * 32);

    sf::Sprite test1(TextureFolder::GetTexture("test_1"));
    test1.setPosition(((columns * 32) / 2) + 128, rows * 32);

    sf::Sprite test2(TextureFolder::GetTexture("test_2"));
    test2.setPosition(((columns * 32) / 2) + 192, rows * 32);

    sf::Sprite test3(TextureFolder::GetTexture("test_3"));
    test3.setPosition(((columns * 32) / 2) + 256, rows * 32);

    vector <sf::Sprite> digits;
    int offset = 0;
    for (size_t i = 0; i < 11; i++)
    {
        sf::Sprite digit(TextureFolder::GetTexture("digits"));
        digit.setTextureRect(sf::IntRect(offset, 0, 21, 32));
        digits.push_back(digit);
        offset += 21;
    }
    vector <sf::Sprite> digits2 = digits;
    vector <sf::Sprite> digits3 = digits;
    vector <sf::Sprite> digits4 = digits;




    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.clear();
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Right && Board->isGaming)
                {                   
                    for (int i = 0; i < rows; i++)
                    {
                        for (int j = 0; j < columns; j++)
                        {
                            
                            if (Board->tiles[i][j].isHidden && Board->tiles[i][j].hidden.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                            {
                                if (Board->tiles[i][j].isFlag)
                                {
                                    Board->flagCounter--;
                                }
                                else if (!Board->tiles[i][j].isFlag)
                                {
                                    Board->flagCounter++;
                                }
                                Board->tiles[i][j].UpdateFlag();
                                break;
                            }                            
                        }
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Left )
                {
                    if (test1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        
                        ifstream testMapOne("boards/testboard1.brd");
                        vector<char> info1;
                        if (testMapOne.is_open())
                        {
                            Board->flagCounter = 0;
                            string temp;
                            while (getline(testMapOne, temp))
                            {
                                istringstream mapInfo(temp);
                                string update;
                                getline(mapInfo, update);
                                for (size_t i = 0; i < update.size(); i++)
                                {
                                    char data = update.at(i);
                                    info1.push_back(data);
                                }
                            }
                            testMapOne.close();
                        }
                        else if (!testMapOne.is_open())
                        {
                            cout << "failed to open test map 1" << endl;
                        }
                        Board->Test(info1);

                    }
                    if (test2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        
                        ifstream testMapTwo("boards/testboard2.brd");
                        vector<char> info2;
                        if (testMapTwo.is_open())
                        {
                            Board->flagCounter = 0;
                            string temp;
                            while (getline(testMapTwo, temp))
                            {
                                istringstream mapInfo(temp);
                                string update;
                                getline(mapInfo, update);
                                for (size_t i = 0; i < update.size(); i++)
                                {
                                    char data = update.at(i);
                                    info2.push_back(data);
                                }
                            }
                            testMapTwo.close();
                        }
                        else if (!testMapTwo.is_open())
                        {
                            cout << "failed to open test map 2" << endl;
                        }
                        Board->Test(info2);
                    }
                    if (test3.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        
                        ifstream testMapThree("boards/testboard3.brd");
                        vector<char> info3;
                        if (testMapThree.is_open())
                        {
                            Board->flagCounter = 0;
                            string temp;
                            while (getline(testMapThree, temp))
                            {
                                istringstream mapInfo(temp);
                                string update;
                                getline(mapInfo, update);
                                for (size_t i = 0; i < update.size(); i++)
                                {
                                    char data = update.at(i);
                                    info3.push_back(data);
                                }
                            }
                            testMapThree.close();
                        }
                        else if (!testMapThree.is_open())
                        {
                            cout << "failed to open test map 1" << endl;
                        }                       
                        Board->Test(info3);
                    }
                    if (happy.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        Board->NewGame(width, height);
                    }
                    if (debug.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        Board->DebugMode();
                        break;
                    }
                    else if (Board->isGaming)
                    {
                        for (size_t i = 0; i < rows; i++)
                        {
                            for (size_t j= 0; j < columns; j++)
                            {
                                if (Board->tiles[i][j].CheckFlag() == false && Board->tiles[i][j].revealed.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                                {
                                    Board->Reveal(i, j);
                                    if (Board->tiles[i][j].CheckBomb())
                                    {
                                        Board->lose = true;
                                        Board->isGaming = false;
                                    }
                                    else if (Board->tilesRevealed == (rows * columns) - Board->mineCounter)
                                    {
                                        Board->win = true;
                                        Board->isGaming = false;
                                    }
                                    break;
                                }
                            }
                        }
                    }
                    
                    
                    
                }

            }

        }

        window.clear();
        window.draw(Board->background);      
        window.draw(debug);
        window.draw(test1);
        window.draw(test2);
        window.draw(test3);
        
        //Flag count stuff
        if (Board->mineCounter - Board->flagCounter < 0) 
        {
            digits4[10].setPosition(0, rows * 32);
            window.draw(digits4[10]);
            for (int i = 0; i < 10; i++) 
            {
                if ((Board->mineCounter - Board->flagCounter) / 100 == i || (Board->mineCounter - Board->flagCounter) / -100 == i) 
                {
                    digits[i].setPosition(21, rows * 32);
                    window.draw(digits[i]);
                }
            }
            for (int i = 0; i < 10; i++) 
            {
                int tempCounter = Board->mineCounter - Board->flagCounter;
                if (tempCounter <= -100 || tempCounter >= 100) 
                {
                    tempCounter /= -10;
                    if (tempCounter % 10 == i || tempCounter % -10 == i) 
                    {
                        digits2[i].setPosition(42, rows * 32);
                        window.draw(digits2[i]);
                    }
                }
                else if (tempCounter / 10 == i || tempCounter / -10 == i) 
                {
                    digits2[i].setPosition(42, rows * 32);
                    window.draw(digits2[i]);
                }
            }
            for (int i = 0; i < 10; i++) 
            {
                if ((Board->mineCounter - Board->flagCounter) % 10 == i || ((Board->mineCounter - Board->flagCounter) * -1) % 10 == i) 
                {
                    digits3[i].setPosition(63, rows * 32);
                    window.draw(digits3[i]);
                }
            }
        }
        else
        {            
            for (int i = 0; i < 10; i++) 
            {
                if ((Board->mineCounter - Board->flagCounter) / 100 == i || (Board->mineCounter - Board->flagCounter) / -100 == i) 
                {
                    digits[i].setPosition(0, rows * 32);
                    window.draw(digits[i]);
                }
            }
            for (int i = 0; i < 10; i++) 
            {
                int tempCounter = Board->mineCounter - Board->flagCounter;
                if (tempCounter <= -100 || tempCounter >= 100) 
                {
                    tempCounter /= 10;
                    if (tempCounter % 10 == i || tempCounter % -10 == i)
                    {
                        digits2[i].setPosition(21, rows * 32);
                        window.draw(digits2[i]);
                    }
                }
                else if (tempCounter / 10 == i || tempCounter / -10 == i) 
                {
                    digits2[i].setPosition(21, rows * 32);
                    window.draw(digits2[i]);
                }
            }
            for (int i = 0; i < 10; i++) {
                if ((Board->mineCounter - Board->flagCounter) % 10 == i || ((Board->mineCounter - Board->flagCounter) * -1) % 10 == i) 
                {
                    digits3[i].setPosition(42, rows * 32);
                    window.draw(digits3[i]);
                }
            }
        }

        if (Board->isGaming)
        {
            window.draw(happy);
            for (size_t i = 0; i < rows; i++)
            {
                for (size_t j = 0; j < columns; j++)
                {
                    window.draw(Board->tiles[i][j].revealed);
                    if (!Board->tiles[i][j].CheckBomb())
                    {
                        window.draw(Board->tiles[i][j].number);
                    }
                    if (Board->debugMode)
                    {
                        if (Board->tiles[i][j].isHidden)
                        {
                            window.draw(Board->tiles[i][j].hidden);
                        }
                        if (Board->tiles[i][j].CheckFlag())
                        {
                            window.draw(Board->tiles[i][j].flag);
                        }
                        if (Board->tiles[i][j].CheckBomb())
                        {
                            window.draw(Board->tiles[i][j].bomb);
                        }
                     
                    }
                    else 
                    {
                        if (Board->tiles[i][j].CheckBomb())
                        {
                            window.draw(Board->tiles[i][j].bomb);
                        }
                        if (Board->tiles[i][j].isHidden)
                        {
                            window.draw(Board->tiles[i][j].hidden);
                        }
                        if (Board->tiles[i][j].CheckFlag())
                        {
                            window.draw(Board->tiles[i][j].flag);
                        }
                    }
                    
                    
                }
            }
        }
        else if (Board->lose)
        {
            window.draw(lose);
            for (size_t i = 0; i < rows; i++)
            {
                for (size_t j = 0; j < columns; j++)
                {
                    window.draw(Board->tiles[i][j].revealed);
                    if (!Board->tiles[i][j].CheckBomb())
                    {
                        window.draw(Board->tiles[i][j].number);
                    }
                    if (Board->tiles[i][j].isHidden && !Board->tiles[i][j].CheckBomb())
                    {
                        window.draw(Board->tiles[i][j].hidden);
                    }
                    if (Board->tiles[i][j].CheckFlag())
                    {
                        window.draw(Board->tiles[i][j].flag);
                    }
                    if (Board->tiles[i][j].CheckBomb())
                    {
                        window.draw(Board->tiles[i][j].bomb);
                    }
                }
            }
        }
        else if(Board->win)
        {
            window.draw(win);
            for (size_t i = 0; i < rows; i++)
            {
                for (size_t j = 0; j < columns; j++)
                {
                    window.draw(Board->tiles[i][j].revealed);
                    if (!Board->tiles[i][j].CheckBomb())
                    {
                        window.draw(Board->tiles[i][j].number);
                    }
                    if (Board->tiles[i][j].isHidden && !Board->tiles[i][j].CheckBomb())
                    {
                        window.draw(Board->tiles[i][j].hidden);
                    }
                    if (Board->tiles[i][j].CheckBomb())
                    {
                        Board->tiles[i][j].isFlag = true;
                        Board->flagCounter = Board->mineCounter;
                        window.draw(Board->tiles[i][j].hidden);
                        window.draw(Board->tiles[i][j].flag);
                    }
                    if (Board->debugMode)
                    {
                        if (Board->tiles[i][j].CheckBomb())
                        {
                            window.draw(Board->tiles[i][j].bomb);
                        }
                    }
                }
            }
        }
        

        
        window.display();
        
    }
    TextureFolder::Clear();
    delete Board;

    return 0;
}
