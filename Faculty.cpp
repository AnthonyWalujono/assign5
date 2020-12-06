#include <sstream>
#include "Faculty.h"

std::ostream& operator<<(std::ostream& os, const Faculty& F)
{
	os << Person(F);
	os << "Department: " << F.getDepartment() << std::endl;
	os << "Advisee IDs: ";
	const DoublyLinkedList<int>& advisees = F.getAdvisees();
	if (advisees.empty()) {
		os << "<none>";
	}
	else {
		auto it = advisees.begin();
		os << *it;
		++it;
		for (auto IT = advisees.end(); it != IT; ++it) {
			os << ", " << *it;
		}
	}
	return os;
}

void readFaculty(std::istream& is, Faculty& F)
{
	std::istringstream iss;
	int numAdvisees;
	int id;
	std::string word;

	readPerson(is, F);

	getline(is, word);
	F.setDepartment(word);

	getline(is, word);
	iss.str(word);
	iss.clear();
	iss.seekg(iss.beg);
	iss >> numAdvisees;

	while (numAdvisees-- > 0) {
		getline(is, word);
		iss.str(word);
		iss.clear();
		iss.seekg(iss.beg);
		iss >> id;
		F.addAdvisee(id);
	}
}

void writeFaculty(std::ostream& os, const Faculty& F)
{
	writePerson(os, Person(F));

	os << F.getDepartment() << std::endl;

	// First write out the number of advisees
	os << F.getAdvisees().getSize() << std::endl;
	for (auto cur = F.getAdvisees().begin(), end = F.getAdvisees().end(); cur != end; ++cur) {
		os << *cur << std::endl;
	}
}
