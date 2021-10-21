#pragma once
#include "MainPerson.h"
#include "Level.h"
#include <string>
#include <vector>

class Game
{
public:
	Game();
	~Game();

	void Initialize();                    // базовая инициализация 
	void Run();                           // основной игровой цикл, все операции с игрой
private:
	std::vector<std::string> levelsNames_;// название уровня (из файла)
	MainPerson *mainPerson_;              // указатель на персонажа
	Level *level_;                        // указатель на текущий левел
	size_t levelsCount_;                  // количество уровней
};
