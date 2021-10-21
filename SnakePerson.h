#pragma once
#include "Person.h"

class SnakePerson : public Person
{
public:

	// ”наследовано через Person
	virtual void move(int command) override;

};

