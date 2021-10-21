#pragma once

#include "Person.h"

class Level;
class Person;


class MainPerson : public Person
{
public:
	void lookAround();      // обновл¤ем маску видимости в левеле

	// ”наследовано через Person
	virtual void move(int command) override;

	void setPersonSymbol(char val);
	char getPersonSymbol() const;
	void setLookRadius(size_t radius);

	void setLevel(Level *level);

private:
	size_t lookRadius_;  // радиус видимости	
};
