#pragma once
#include <wincontypes.h>  // ��� COORD

class Level;


class Person
{
public:

	virtual void move(int command) = 0; // ������������ ������� ���������
	
	COORD getPersonCoord() const;
	void setPersonCoord(COORD coord);
	void setPersonSymbol(char symbol);

protected:
	
	COORD personCoord_; // ���������� ���������
	char symbol_;       // ������ ��� ���������

	Level *level_;  // ������ �� �������, ����� �������������� ����������� �� ������
};
