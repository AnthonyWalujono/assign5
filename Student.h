#ifndef CPSC_350_STUDENT_H
#define CPSC_350_STUDENT_H
#include <string>
#include "Person.h"
using namespace std;
class Student : public Person {
public:

	Student(int id) : Person(id), hasAdvisor(false) {}
	
	void setMajor(std::string m) { major = m; }
	void setGPA(double g) { gpa = g; }
	void setAdvisor(int a) { advisorID = a; hasAdvisor = true; }
	void removeAdvisor() { hasAdvisor = false; }
	
	std::string getMajor() const { return major; }
	double getGPA() const { return gpa; }
	bool hasAnAdvisor() const { return hasAdvisor; }
	int getAdvisorId() const { return advisorID; }

private:

	std::string major;
	double gpa;
	int advisorID;
	bool hasAdvisor;
};

std::ostream& operator<<(std::ostream& os, const Student& S);
void readStudent(std::istream&, Student& S);
void writeStudent(std::ostream&, const Student& S);

#endif
