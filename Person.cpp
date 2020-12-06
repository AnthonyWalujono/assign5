#include <sstream>
#include "Person.h"

std::ostream& operator<<(std::ostream& os, const Person& P)
{
	os << "\nID number: " << P.getId() << std::endl;
	os << "Name: " << P.getName() << std::endl;
	os << "Level: " << P.getLevel() << std::endl;
	return os;
}

void readPerson(std::istream& is, Person& P)
{
	std::istringstream iss;
	int id;
	std::string word;

	getline(is, word);
	iss.str(word);
	iss.clear();
	iss.seekg(iss.beg);
	iss >> id;
	P.setId(id);

	getline(is, word);
	P.setName(word);

	getline(is, word);
	P.setLevel(word);
}

void writePerson(std::ostream& os, const Person& P)
{
	os << P.getId() << std::endl;
	os << P.getName() << std::endl;
	os << P.getLevel() << std::endl;
}
