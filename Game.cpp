#include "Game.h"
#include <fstream>
#include <iostream>
#include <conio.h>

Game::Game()
{
	level_ = nullptr;
	mainPerson_ = nullptr;	      
}

Game::~Game()
{
	if(level_)
		delete level_;

	if(mainPerson_)
		delete mainPerson_;
}

void Game::Initialize()
{
	std::ifstream file;	

	std::string buf = "";
	
	file.open("Levels.txt");
	if (!file.is_open())
	{
		std::string error{ "Error load file Levels.txt" };
		MessageBox(NULL, error.c_str(), TEXT("Error"), MB_OK);
		exit(EXIT_FAILURE);
	}
	/*
	��������� ������ ������ �������������� �� �����������
	�� ������� LevelsCount: ����� ���� ���������� �������:	
	*/
	file >> buf >> levelsCount_;
	file.get();    // ������ ������ ����� ������

	// ����� �������� �������� ������� (��� �� �������� ������ � ��������)
	for (size_t i = 0; i < levelsCount_; i++)
	{
		buf.clear();
		std::getline(file, buf);
		levelsNames_.push_back(buf);
	}

	file.close();
	
	// "������" �������
	level_ = new Level();          
	level_->setLevelNumber(1);     // �������� ������ � 1 ������
	level_->load(levelsNames_[0]); // ��������� ������ �������

	char personSymbol = 0;
	size_t lookRadius = 0;

	file.open("Person.txt");
	if (!file.is_open())
	{
		std::string error{ "Error load file Person.txt" };
		MessageBox(NULL, error.c_str(), TEXT("Error"), MB_OK);
		exit(EXIT_FAILURE);
	}
	file >> buf >> personSymbol >> buf >> lookRadius;
	file.close();

	// ������ �������� ���������
	mainPerson_ = new MainPerson();
	mainPerson_->setLevel(level_);
	mainPerson_->setLookRadius(lookRadius);
	mainPerson_->setPersonSymbol(personSymbol);
	mainPerson_->setPersonCoord(COORD{ level_->getStartCoordX(), level_ ->getStartCoordY()});
	// "����������" ��� �� �������
	level_->setPerson(mainPerson_);
}

void Game::Run()
{
	size_t command = 0;
	while (command != 'q')  // q ����� �������� �� �������� ������!!!!!!!!!!!!
	{
		mainPerson_->lookAround();
		level_->levelDrawing();
		command = _getch();
		mainPerson_->move(command);

		// ���� �������� ��������� ������ (�������� �� ����� �������)
		if (level_->IsExit(mainPerson_->getPersonCoord().X, mainPerson_->getPersonCoord().Y))
		{
			// �������� ����� ������
			size_t number = level_->getLevelNumber();
			// ���� �� ������ ������ ���-�� �������
			if (levelsCount_ > number)
			{
				// ������ ���������
				level_->load(levelsNames_[number]);
				// � �������������� ����� ������ � ������
				level_->setLevelNumber(++number);
				mainPerson_->setPersonCoord(COORD{ level_->getStartCoordX(), level_->getStartCoordY()});
			}
			else   // ����� - ��������� ����
			{				
				std::cout << std::endl << "You Win!" << std::endl;
				system("pause");
				break;
			}
		}
	}
}
