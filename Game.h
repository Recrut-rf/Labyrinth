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

	void Run();                           // основной игровой цикл, все операции с игрой
private:
	void Initialize();                    // базовая инициализация 

	std::vector<std::string> levelsNames_;// название уровня (из файла)
	MainPerson *mainPerson_;              // указатель на персонажа
	Level *level_;                        // указатель на текущий левел
	size_t levelsCount_;                  // количество уровней
};
