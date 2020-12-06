#ifndef CPSC_350_DATABASE_CMD_H
#define CPSC_350_DATABASE_CMD_H
#include "BST.h"
#include "Student.h"
#include "Faculty.h"

class DatabaseCommand
{
public:

	virtual ~DatabaseCommand() {}
	virtual void rollback(BST<Student> & students, BST<Faculty> & faculty) = 0;

};

class AddStudentCommand : public DatabaseCommand
{
public:

	AddStudentCommand(Student student) : student(student) {}
	void rollback(BST<Student>& students, BST<Faculty>& faculty);

private:

	Student student;
};

class AddFacultyCommand : public DatabaseCommand
{
public:

	AddFacultyCommand(Faculty faculty_person) : faculty_person(faculty_person) {}
	void rollback(BST<Student>& students, BST<Faculty>& faculty);

private:

	Faculty faculty_person;
};




#endif
