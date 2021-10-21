#pragma once
#include <wincontypes.h>  // для COORD

class Level;


class Person
{
public:

	virtual void move(int command) = 0; // обрабатываем команды персонажа
	
	COORD getPersonCoord() const;
	void setPersonCoord(COORD coord);
	void setPersonSymbol(char symbol);

protected:
	
	COORD personCoord_; // координаты персонажа
	char symbol_;       // символ для персонажа

	Level *level_;  // ссылка на уровень, чтобы контролировать перемещения по уровню
};
