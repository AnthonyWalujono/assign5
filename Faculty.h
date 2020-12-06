#ifndef CPSC_350_FACULTY_H //include guards
#define CPSC_350_FACULTY_H
#include <string>
#include "Person.h"
#include "DoublyLinkedList.h"
class Faculty : public Person {
public:
	Faculty(int id) : Person(id) {}
	
	void setDepartment(std::string d) { department = d; }
	void addAdvisee(int studID) { advisees.insertBack(studID); }
	void removeAdvisee(int studID) { advisees.deleteElem(studID); }

	std::string getDepartment() const { return department; }
	const DoublyLinkedList<int>& getAdvisees() const { return advisees; }

private:

	std::string department;
	DoublyLinkedList<int> advisees;
};

std::ostream& operator<<(std::ostream& os, const Faculty& F);
void readFaculty(std::istream&, Faculty& F);
void writeFaculty(std::ostream&, const Faculty& F);

#endif
