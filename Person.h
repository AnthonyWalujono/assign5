#ifndef CPSC_350_PERSON_H //include guards
#define CPSC_350_PERSON_H
#include <string>
#include <iostream>
class Person {
public:
	Person(int id) : idNum(id) {}
	void setId(int id) { idNum = id; }
	void setName(std::string n) { name = n; }
	void setLevel(std::string l) { level = l; }

	int getId() const { return idNum; }
	std::string getName() const { return name; }
	std::string getLevel() const { return level; }

	bool operator < (const Person& S) const { return idNum < S.idNum; }
	bool operator <= (const Person& S) const { return (*this < S) || !(S < *this); }
	bool operator > (const Person& S) const { return !(*this <= S); }
	bool operator >= (const Person& S) const { return !(*this < S); }
	bool operator == (const Person& S) const { return !(*this < S) && !(S < *this); }
	bool operator != (const Person& S) const { return !(*this == S); }

protected:

	int idNum;
	std::string name;
	std::string level;
};

std::ostream& operator<<(std::ostream& os, const Person& P);
void readPerson(std::istream&, Person& P);
void writePerson(std::ostream&, const Person& P);

#endif //!PERSON_H
