#pragma once
#include "ConsoleEngine.h"
#include <vector>
#include <string>

class MainPerson;
class Person;

class Level
{
public:
	Level();


	void load(std::string fileName);  // загрузка уровня
	void levelDrawing();              // отрисовка уровня
	bool CanMove(size_t x, size_t y); // проверяет доступность клетки
	bool IsExit(size_t x, size_t y);  // является ли клетка выходом с данного уровня

	USHORT getWidth() const;
	USHORT getHeight() const;
	USHORT getLevelNumber() const;

	void setAreaMask(USHORT height, USHORT width);
	void setLevelNumber(USHORT number);

	void setPerson(Person *person);
	SHORT getStartCoordX() const;
	SHORT getStartCoordY() const;

private:			  

	USHORT levelNumber_; // номер уровня
	USHORT width_;       // ширина
	USHORT height_;      // высота

	std::vector<std::vector<bool>> areaMask_; // маска видимости (информирует о том, 
	                                          // видима клетка или нет)	
	std::vector<std::vector<char>> area_;     // игровое пространство

	char floorSymbol_;            // пол
	char wallSymbol_;             // стены
	char exitSymbol_;             // выход с уровня

	COORD exitCoord_;             // координаты выхода 
	COORD startMainPersonCoord_;  // стартовые координаты главного персонажа
	ConsoleEngine consoleEngine_;

	MainPerson *mainPerson_;

	void initializeEngine();
	// добавить символ в буфер и установить для символа атрибуты
	void addSymbolAndAttributeToBuffer(size_t symbolIndex, char symbol, WORD atribute);
};
