#include "Level.h"
#include "MainPerson.h"


void MainPerson::lookAround()
{
	size_t height = level_->getHeight();
	size_t width = level_->getWidth();

	for (size_t i = 0; i < height; ++i)
	{
		for (size_t j = 0; j < width + 1; ++j)
		{
			if ((personCoord_.X - i) * (personCoord_.X - i) + (personCoord_.Y - j) * (personCoord_.Y - j) <= (lookRadius_ * lookRadius_))
				level_->setAreaMask(i, j);
		}
	}
}

void MainPerson::move(int command)
{
	switch (command)
	{
		// ������������� w � �
	case 119:
	case 230:
		if (level_->CanMove(personCoord_.X - 1, personCoord_.Y))
			--personCoord_.X;
		break;

		// ������������� a � �
	case 97:
	case 228:
		if (level_->CanMove(personCoord_.X, personCoord_.Y - 1))
			--personCoord_.Y;
		break;

		// ������������� s � �
	case 115:
	case 235:
		if (level_->CanMove(personCoord_.X + 1, personCoord_.Y))
			++personCoord_.X;
		break;

		// ������������� d � �
	case 100:
	case 162:
		if (level_->CanMove(personCoord_.X, personCoord_.Y + 1))
			++personCoord_.Y;
		break;
	default:
		break;
	}
}

void MainPerson::setPersonSymbol(char val)
{
	symbol_ = val;
}

char MainPerson::getPersonSymbol() const
{
	return symbol_;
}

void MainPerson::setLookRadius(size_t radius)
{
	lookRadius_ = radius;
}

void MainPerson::setLevel(Level * level)
{
	level_ = level;
}
