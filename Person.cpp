#include "Level.h"
#include "Person.h"


COORD Person::getPersonCoord() const
{
	return personCoord_;
}

void Person::setPersonCoord(COORD coord)
{
	personCoord_ = coord;
}

void Person::setPersonSymbol(char symbol)
{
	symbol_ = symbol;
}
