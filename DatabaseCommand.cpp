#include "DatabaseCommand.h"

void AddStudentCommand::rollback(BST<Student>& students, BST<Faculty>& faculty)
{
	students.deleteNode(student);
}

void AddFacultyCommand::rollback(BST<Student>& students, BST<Faculty>& faculty)
{
	faculty.deleteNode(faculty_person);
}
