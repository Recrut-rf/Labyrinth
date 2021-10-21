#include "MainPerson.h"
#include "Level.h"
#include <fstream>
#include <WinUser.h>
#include <stdlib.h>
#include <algorithm>

Level::Level() : levelNumber_{},
                 width_{},
	             height_{},
	             areaMask_{},
	             area_{},
	             floorSymbol_{},
	             wallSymbol_{},
				 exitSymbol_{},
	             exitCoord_{}, 
	             startMainPersonCoord_{},
				 mainPerson_{}
{        }

void Level::load(std::string fileName)
{
	consoleEngine_.flushBuffer();

	std::ifstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		std::string error{ "Error load file " + fileName };
		MessageBox(NULL, error.c_str(), TEXT("Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	std::string buf{};
	file >> buf >> floorSymbol_
		 >> buf >> wallSymbol_
		 >> buf >> exitSymbol_
		 >> buf >> startMainPersonCoord_.X
		 >> buf >> startMainPersonCoord_.Y
	     >> buf >> exitCoord_.X
		 >> buf >> exitCoord_.Y;		 
	
	// при каждой новой загрузке уровня 
	// игровое пространство нужно чистить - потому как у каждого уровня оно свое
	if (area_.size() != 0)
	{
		for (size_t i{}; i < area_.size(); ++i)
			area_[i].clear();

		area_.clear();
	}

	// при каждой новой загрузке уровн¤ 
	// маску нужно чистить - потому как для каждого уровня она своя
	if (areaMask_.size() != 0)
	{
		for (size_t i{}; i < areaMask_.size(); ++i)
			areaMask_[i].clear();

		areaMask_.clear();
	}

	file >> buf >> height_
		 >> buf >> width_;		

	file.get();   // читаем символ новой строки

	// через new скорее всего эффективнее
	// но не очень охота возитьс¤ поэтому
	// буду делать через вектор
	std::vector<char> temp;
	std::vector<bool> tempBool;

	for (size_t i = 0; i < height_; ++i)
	{
		for (size_t j = 0; j < width_ + 1; ++j)
		{
			temp.push_back(file.get());			
			tempBool.push_back(false);			
		}
		area_.push_back(temp);
		temp.clear();
		areaMask_.push_back(tempBool);
		tempBool.clear();		
	}

	file.close();	
}

void Level::levelDrawing()
{
	initializeEngine();
	   
	/*
	список цветов для атрибутов:
	0 Ч черный
	1 Ч синий
	2 Ч зеленый
	3 Ч голубой
	4 Ч красный
	5 Ч лиловый
	6 Ч желтый
	7 Ч белый
	8 Ч серый
	9 Ч свело-синий
	A Ч светло-зеленый
	B Ч светло-голубой
	— Ч светло-красный
	E Ч светло-желтый
	F Ч ярко-белый
	*/

	WORD floorAttrib = 2 | 4;
	WORD wallAttrib = 2;
	WORD personAttrib = 6;
	WORD attribBlack = 0;

	size_t index = 0;
	for (size_t i = 0; i < height_; ++i)
	{
		for (size_t j = 0; j < width_ + 1; ++j)
		{			
			if (area_[i][j] == '\n')			
				addSymbolAndAttributeToBuffer(index, '\n', 0);
			
			if (areaMask_[i][j] && area_[i][j] != '\n')
			{
				if ((i != mainPerson_->getPersonCoord().X || j != mainPerson_->getPersonCoord().Y) && !IsExit(i, j))
				{					
					if (area_[i][j] == floorSymbol_)					
						addSymbolAndAttributeToBuffer(index, floorSymbol_, floorAttrib);
					
					if (area_[i][j] == wallSymbol_)					
						addSymbolAndAttributeToBuffer(index, wallSymbol_, wallAttrib);					
				}
				else if (IsExit(i, j))					
					addSymbolAndAttributeToBuffer(index, exitSymbol_, 0xF);
				
				else				
					addSymbolAndAttributeToBuffer(index, mainPerson_->getPersonSymbol(), personAttrib);				
			}			
			++index;
		}
	}
	consoleEngine_.setWriteRegion(0, 0, width_ + 1, height_);
	consoleEngine_.writeConsole();
}

bool Level::CanMove(size_t x, size_t y)
{
	return area_[x][y] != wallSymbol_;
}

bool Level::IsExit(size_t x, size_t y)
{
	return x == exitCoord_.X && y == exitCoord_.Y;
}

size_t Level::getWidth() const
{
	return width_;
}

size_t Level::getHeight() const
{
	return height_;
}

size_t Level::getLevelNumber() const
{
	return levelNumber_;
}

void Level::setAreaMask(size_t height, size_t width)
{
	if (areaMask_.size() != 0)
		areaMask_[height][width] = true;
}

void Level::setLevelNumber(size_t number)
{
	levelNumber_ = number;
}

void Level::setPerson(Person *person)
{	
	mainPerson_ = dynamic_cast<MainPerson*>(person);
}

SHORT Level::getStartCoordX() const
{
	return startMainPersonCoord_.X;
}

SHORT  Level::getStartCoordY() const
{
	return startMainPersonCoord_.Y;
}

void Level::initializeEngine()
{
	// в буфер складываются все символы, включая переход
	// на новую строку (\n) поэтому width_ + 1
	consoleEngine_.setBufferSize(width_ + 1, height_);
	consoleEngine_.setCursorPosition(COORD{});
	consoleEngine_.setCursorAttribute(false);
}

void Level::addSymbolAndAttributeToBuffer(size_t symbolIndex, char symbol, WORD atribute)
{
	consoleEngine_.setCharBuffer(symbolIndex, symbol);
	consoleEngine_.setAttribute(atribute, symbolIndex);
}
