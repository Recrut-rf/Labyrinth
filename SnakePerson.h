#pragma once
#include "Person.h"

class SnakePerson : public Person
{
public:

	// ������������ ����� Person
	virtual void move(int command) override;

};

