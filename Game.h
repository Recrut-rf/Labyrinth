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

	void Initialize();                    // ������� ������������� 
	void Run();                           // �������� ������� ����, ��� �������� � �����
private:
	std::vector<std::string> levelsNames_;// �������� ������ (�� �����)
	MainPerson *mainPerson_;              // ��������� �� ���������
	Level *level_;                        // ��������� �� ������� �����
	size_t levelsCount_;                  // ���������� �������
};
