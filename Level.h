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


	void load(std::string fileName);  // �������� ������
	void levelDrawing();              // ��������� ������
	bool CanMove(size_t x, size_t y); // ��������� ����������� ������
	bool IsExit(size_t x, size_t y);  // �������� �� ������ ������� � ������� ������

	size_t getWidth() const;
	size_t getHeight() const;
	size_t getLevelNumber() const;

	void setAreaMask(size_t height, size_t width);
	void setLevelNumber(size_t number);

	void setPerson(Person *person);
	SHORT getStartCoordX() const;
	SHORT getStartCoordY() const;

private:			  

	size_t levelNumber_; // ����� ������
	size_t width_;       // ������
	size_t height_;      // ������

	std::vector<std::vector<bool>> areaMask_; // ����� ��������� (����������� � ���, 
	                                          // ������ ������ ��� ���)	
	std::vector<std::vector<char>> area_;     // ������� ������������

	char floorSymbol_;            // ���
	char wallSymbol_;             // �����
	char exitSymbol_;             // ����� � ������

	COORD exitCoord_;             // ���������� ������ 
	COORD startMainPersonCoord_;  // ��������� ���������� �������� ���������
	ConsoleEngine consoleEngine_;

	MainPerson *mainPerson_;

	void initializeEngine();
	// �������� ������ � ����� � ���������� ��� ������� ��������
	void addSymbolAndAttributeToBuffer(size_t symbolIndex, char symbol, WORD atribute);
};
