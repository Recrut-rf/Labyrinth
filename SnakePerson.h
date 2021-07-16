#pragma once
#include "Person.h"

class SnakePerson : public Person
{
public:

	// Унаследовано через Person
	virtual void move(int command) override;

};

