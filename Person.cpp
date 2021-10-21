#include "Level.h"
#include "Person.h"


COORD Person::getCoord() const
{
	return personCoord_;
}

void Person::setCoord(COORD coord)
{
	personCoord_ = coord;
}

void Person::setPersonSymbol(char symbol)
{
	symbol_ = symbol;
}
