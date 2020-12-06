#include <sstream>
#include "Student.h"

std::ostream& operator<<(std::ostream& os, const Student& S)
{
	os << Person(S);
	os << "Major: " << S.getMajor() << std::endl;
	os << "GPA: " << S.getGPA() << std::endl;
	if (S.hasAnAdvisor()) {
		os << "Advisor ID: " << S.getAdvisorId();
	} else {
		os << "Advisor ID: <none>";
	}
	return os;
}

void readStudent(std::istream& is, Student& S)
{
	std::istringstream iss;
	double gpa;
	int advID;
	std::string word;

	readPerson(is, S);

	getline(is, word);
	S.setMajor(word);

	getline(is, word);
	iss.str(word);
	iss.clear();
	iss.seekg(iss.beg);
	iss >> gpa;
	S.setGPA(gpa);

	getline(is, word);
	if (word == "true") {
		getline(is, word);
		iss.str(word);
		iss.clear();
		iss.seekg(iss.beg);
		iss >> advID;
		S.setAdvisor(advID);
	}
}

void writeStudent(std::ostream& os, const Student& S)
{
	writePerson(os, S);

	os << S.getMajor() << std::endl;
	os << S.getGPA() << std::endl;
	if (S.hasAnAdvisor()) {
		os << "true" << std::endl;
		os << S.getAdvisorId() << std::endl;
	} else {
		os << "false" << std::endl;
	}
}
