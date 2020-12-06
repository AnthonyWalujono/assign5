#include <limits>
#include <sstream>
#include <fstream>
#include "DatabaseMenu.h"
using namespace std;

void DatabaseMenu::run()
{
	buildMasterDb();

	int choice;
	do
	{
		choice = getChoice();

		if (choice == 1)		{ displayAllStudents(); }
		else if (choice == 2)	{ displayAllFaculty(); }
		else if (choice == 3)	{ findAndDisplayStudent(); }
		else if (choice == 4)	{ findAndDisplayFaculty(); }
		else if (choice == 5)	{ printAdvisorForStudent(); }
		else if (choice == 6)	{ printAdviseesForFaculty(); }
		else if (choice == 7)	{ addStudent(); }
		else if (choice == 8)	{ deleteStudent(); }
		else if (choice == 9)	{ addFaculty(); }
		else if (choice == 10)	{ deleteFaculty(); }
		else if (choice == 11)	{ changeAdvisor(); }
		else if (choice == 12)	{ deleteAdvisee(); }
		else if (choice == 13)	{ rollBack(); }
		else { cout << "\nClosing database." << endl; }

		waitForEnterKey();

	} while (choice != 14);

	writeTableFiles();
}

void DatabaseMenu::buildMasterDb()
{
	students.clear();
	faculty.clear();

	ifstream fin1, fin2;
	size_t count;

	fin1.open(studentDBFilename);
	fin2.open(facultyDBFilename);

	if (fin1.is_open() && fin2.is_open()) {

		// Read in the student info
		fin1 >> count;
		fin1.ignore();	//  consume newline character

		for (size_t i = 0; i < count; ++i) {
			Student student(0);
			readStudent(fin1, student);
			students.insertNode(student);
		}

		cout << "Successfully loaded information for " << count << " students." << endl;

		// Read in the faculty info
		fin2 >> count;
		fin2.ignore();	//  consume newline character

		for (size_t i = 0; i < count; ++i) {
			Faculty faculty_member(0);
			readFaculty(fin2, faculty_member);
			faculty.insertNode(faculty_member);
		}

		cout << "Successfully loaded information for " << count << " faculty members." << endl;
	}
	else {
		if (!fin1.is_open()) {
			cout << "Unable to open student database file \"" << studentDBFilename << "\"." << endl;
		}
		if (!fin2.is_open()) {
			cout << "Unable to open faculty database file \"" << facultyDBFilename << "\"." << endl;
		}
		cout << "Starting with empty student and faculty databases." << endl;
	}
}

void DatabaseMenu::writeTableFiles() const
{
	ofstream fout;
	fout.open(studentDBFilename);

	// First write out the number of students
	fout << students.getSize() << endl;

	// Write out each student's info
	students.writePreorder(fout, writeStudent);

	fout.close();
	fout.open(facultyDBFilename);

	// First write out the number of faculty
	fout << faculty.getSize() << endl;

	// Write out each faculty's info
	faculty.writePreorder(fout, writeFaculty);

	fout.close();
}

int DatabaseMenu::getChoice() const
{
	return getInt(
		"\nSelect one of the options below: \n"
		"1: Print all students and their information (sorted by ascending id #)\n"
		"2. Print all faculty and their information (sorted by ascending id #)\n"
		"3. Find and display student information given the student's id\n"
		"4. Find and display faculty information given the faculty id\n"
		"5. Given a student's id, print the name and info of their faculty advisor\n"
		"6. Given a faculty id, print ALL the names and info of his/her advisees.\n"
		"7. Add a new student\n"
		"8. Delete a student given the id\n"
		"9. Add a new faculty member\n"
		"10. Delete a faculty member given the id.\n"
		"11. Change a student's advisor given the student id and the new faculty id.\n"
		"12. Remove an advisee from a faculty member given the ids\n"
		"13. Rollback\n"
		"14. Exit\n\n"
		"Entry: ",
		"\nInvalid selection. Please type a number between 1 and 14.\n",
		1, 14);
}

void DatabaseMenu::displayAllStudents() const
{
	if (students.isEmpty()) {
		cout << "\nNo students in database currently.\n";
	}
	else {
		students.printTree();
	}
}

void DatabaseMenu::displayAllFaculty() const
{
	if (faculty.isEmpty()) {
		cout << "\nNo faculty in database currently.\n";
	}
	else {
		faculty.printTree();
	}
}

void DatabaseMenu::findAndDisplayStudent() const
{
	int id = getInt("\nEnter the id of an existing student: ",
					"\nInvalid entry. Type an integer id number\n");

	Student existingStudent(id);
	if (students.searchNode(existingStudent)) {
		cout << students.getNodeValue(existingStudent) << endl;
	}
	else {
		cout << "\nNo matching student id in the database\n";
	}
}

void DatabaseMenu::findAndDisplayFaculty() const
{
	int id = getInt("\nEnter the id of an existing faculty member: ",
					"\nInvalid entry. Type an integer id number\n");

	Faculty existingFaculty(id);
	if (faculty.searchNode(existingFaculty)) {
		cout << faculty.getNodeValue(existingFaculty) << endl;
	}
	else {
		cout << "\nNo matching faculty id in the database\n";
	}
}

void DatabaseMenu::printAdvisorForStudent() const
{
	int id = getInt("\nEnter the id of an existing student: ",
					"\nInvalid entry. Type an integer id number\n");

	Student existingStudent(id);
	if (students.searchNode(existingStudent)) {
		existingStudent = students.getNodeValue(existingStudent);
		if (existingStudent.hasAnAdvisor()) {
			cout << "\nAdvisor info for student " << id << ":\n";
			cout << faculty.getNodeValue(Faculty(existingStudent.getAdvisorId())) << endl;
		}
		else {
			cout << "\nStudent has no advisor\n";
		}
	}
	else {
		cout << "\nStudent id not found\n";
	}
}

void DatabaseMenu::printAdviseesForFaculty() const
{
	int id = getInt("\nEnter the id of an existing faculty member: ",
					"\nInvalid entry. Type an integer id number\n");

	Faculty existingFaculty(id);
	if (faculty.searchNode(existingFaculty)) {
		existingFaculty = faculty.getNodeValue(existingFaculty);
		const DoublyLinkedList<int>& advisees = existingFaculty.getAdvisees();

		cout << "\nAdvisees of faculty member " << existingFaculty.getId() << ":\n";

		if (advisees.empty()) {
			cout << "\n<none>\n";
		}
		else {
			for (auto cur = advisees.begin(), end = advisees.end(); cur != end; ++cur) {
				cout << students.getNodeValue(Student(*cur)) << endl;
			}
		}
	}
	else {
		cout << "\nNo matching faculty id in the database\n";
	}
}

void DatabaseMenu::addStudent()
{
	int id = getInt("\nEnter the id of the new student: ",
			"\nInvalid entry. Type an integer id number\n");

	Student newStudent(id);
	if (students.searchNode(newStudent)) {
		cout << "\nInvalid entry. There is already a student with that id number."
			<< " You can update that student's info from the main menu.\n";
		return;
	}
	string word;
	double gpa;
	cout << "Enter student's name: ";
	getline(cin, word);
	newStudent.setName(word);
	cout << "Enter student's level: ";
	getline(cin, word);
	newStudent.setLevel(word);
	cout << "Enter student's major: ";
	getline(cin, word);
	newStudent.setMajor(word);
	gpa = getDouble("Enter student's GPA: ",
		"\nInvalid entry. Type a decimal number between 0.0 and 5.0\n\n", 0.0, 5.0);
	newStudent.setGPA(gpa);
	students.insertNode(newStudent);
	pushPrevCommands(new AddStudentCommand(newStudent));
	cout << "\nStudent successfully added to database.\n";
}
void DatabaseMenu::deleteStudent()
{
	int studID = getInt("\nEnter the id of an existing student: ",
						"\nInvalid entry. Type an integer id number\n");

	Student existingStudent(studID);

	if (!students.searchNode(existingStudent)) {
		cout << "\nNo matching student id in the database\n";
		return;
	}

	existingStudent = students.getNodeValue(existingStudent);

	// Inform the student's advisor (if there is one) that student is going away.
	if (existingStudent.hasAnAdvisor()) {
		Faculty advisor(existingStudent.getAdvisorId());
		advisor = faculty.getNodeValue(advisor);
		faculty.deleteNode(advisor);
		advisor.removeAdvisee(studID);
		faculty.insertNode(advisor);
		cout << "\nStudent " << studID << " has been removed from faculty member "
			<< advisor.getId() << "'s list of advisees.";
	}

	students.deleteNode(existingStudent);
	cout << "\nStudent " << studID << " has been removed from database." << endl;

}

void DatabaseMenu::addFaculty()
{
	int id = getInt("\nEnter the id of the new faculty: ",
					"\nInvalid entry. Type an integer id number\n");

	Faculty newFaculty(id);
	if (faculty.searchNode(newFaculty)) {
		cout << "\nInvalid entry. There is already a faculty with that id number."
			<< " You can update that faculty's info from the main menu.\n";
		return;
	}
	string word;
	cout << "Enter faculty's name: ";
	getline(cin, word);
	newFaculty.setName(word);
	cout << "Enter faculty's level: ";
	getline(cin, word);
	newFaculty.setLevel(word);
	cout << "Enter faculty's department: ";
	getline(cin, word);
	newFaculty.setDepartment(word);
	faculty.insertNode(newFaculty);
	pushPrevCommands(new AddFacultyCommand(newFaculty));
	cout << "\nFaculty successfully added to database.\n";
}
void DatabaseMenu::deleteFaculty()
{
	int facID = getInt("\nEnter the id of an existing faculty member: ",
						"\nInvalid entry. Type an integer id number\n");

	Faculty existingFaculty(facID);
	if (!faculty.searchNode(existingFaculty)) {
		cout << "\nNo matching faculty id in the database\n";
		return;
	}

	existingFaculty = faculty.getNodeValue(existingFaculty);

	// Before removing the faculty member, we have to inform any of his
	// advisees that he is going away.
	auto advisees = existingFaculty.getAdvisees();
	for (auto cur = advisees.begin(), end = advisees.end(); cur != end; ++cur) {
		Student advisee(*cur);
		advisee = students.getNodeValue(advisee);
		students.deleteNode(advisee);
		advisee.removeAdvisor();
		students.insertNode(advisee);
		cout << "\nStudent " << advisee.getId() << " no longer has an advisor.";
	}

	faculty.deleteNode(existingFaculty);
	cout << "\nFaculty member " << facID << " has been removed from database." << endl;

}

void DatabaseMenu::changeAdvisor()
{
	// Look up the student id
	Student existingStudent(getInt("\nEnter the id of an existing student: ",
									"\nInvalid entry. Type an integer id number\n"));
	if (!students.searchNode(existingStudent)) {
		cout << "\nNo matching student id in the database\n";
		return;
	}

	// Look up the faculty id
	int facID = getInt("\nEnter the id of an existing faculty member: ",
						"\nInvalid entry. Type an integer id number\n");
	Faculty existingFaculty(facID);
	if (!faculty.searchNode(existingFaculty)) {
		cout << "\nNo matching faculty id in the database\n";
		return;
	}

	// Check if the student-faculty pair has already been assigned that way
	existingStudent = students.getNodeValue(existingStudent);
	if (existingStudent.hasAnAdvisor() && existingStudent.getAdvisorId() == facID) {
		cout << "\nThe given faculty member is already assigned as that student's advisor.\n";
		return;
	}

	// Remove the student and faculty from the trees, and also removed the student's current
	// advisor if they have one already.
	students.deleteNode(existingStudent);
	existingFaculty = faculty.getNodeValue(existingFaculty);
	faculty.deleteNode(existingFaculty);

	// Change their advisor/advisee info
	if (existingStudent.hasAnAdvisor()) {
		Faculty oldAdvisor = faculty.getNodeValue(Faculty(existingStudent.getAdvisorId()));
		oldAdvisor.removeAdvisee(existingStudent.getId());
		faculty.insertNode(oldAdvisor);
	}
	existingStudent.setAdvisor(facID);
	existingFaculty.addAdvisee(existingStudent.getId());

	// Put the updated student and faculty back into the trees
	students.insertNode(existingStudent);
	faculty.insertNode(existingFaculty);

	cout << "\nFaculty member has been assigned as that student's advisor.\n";


}

void DatabaseMenu::deleteAdvisee()
{
	// Look up the faculty id
	int facID = getInt("\nEnter the id of an existing faculty member: ",
						"\nInvalid entry. Type an integer id number\n");
	Faculty existingFaculty(facID);
	if (!faculty.searchNode(existingFaculty)) {
		cout << "\nNo matching faculty id in the database\n";
		return;
	}

	// Look up the student id
	int studID = getInt("\nEnter the id of an existing student: ",
						"\nInvalid entry. Type an integer id number\n");
	Student existingStudent(studID);
	if (!students.searchNode(existingStudent)) {
		cout << "\nNo matching student id in the database\n";
		return;
	}

	existingStudent = students.getNodeValue(existingStudent);

	if (!existingStudent.hasAnAdvisor() || existingStudent.getAdvisorId() != facID) {
		cout << "\nFaculty member " << facID << " is not the advisor of student " << studID << ".\n";
		return;
	}
	existingFaculty = faculty.getNodeValue(existingFaculty);
	existingFaculty.removeAdvisee(studID);
	faculty.insertNode(existingFaculty);
	cout << "Advisee ID " << studID << " has been deleted"<< endl;

}

void DatabaseMenu::rollBack()
{
	if (prevCommands.empty()) {
		cout << "No previous commands can be rolled back" << endl << endl;
	}
	else {
		prevCommands.getBack()->rollback(students, faculty);
		delete prevCommands.removeBack();
	}
}

void DatabaseMenu::pushPrevCommands(DatabaseCommand* cmd)
{
	if (prevCommands.getSize() == MAX_ROLLBACKS) {
		delete prevCommands.removeFront();
	}
	prevCommands.insertBack(cmd);
}

void DatabaseMenu::waitForEnterKey() const
{
	cout << "\nPress enter to proceed.\n";

	string entry;
	getline(cin, entry);
}

int DatabaseMenu::getInt(const std::string& prompt, const std::string errMsg, int minValid, int maxValid) const
{
	string input;
	int val;

	cout << prompt;
	getline(cin, input);
	istringstream iss(input);

	// Make sure we can convert the user input into an integer in the interval [minValid,maxValid]
	// and there is no additional input.
	while (!(iss >> val) || val < minValid || val > maxValid || (iss >> input && !input.empty())) {
		cout << errMsg << prompt;
		getline(cin, input);
		iss.str(input);
		iss.clear();
		iss.seekg(ios::beg);
	}

	return val;
}

double DatabaseMenu::getDouble(const std::string& prompt, const std::string errMsg, double minValid, double maxValid) const
{
	string input;
	double val;

	cout << prompt;
	getline(cin, input);
	istringstream iss(input);

	// Make sure we can convert the user input into a double in the interval [minValid,maxValid]
	// and there is no additional input.
	while (!(iss >> val) || val < minValid || val > maxValid || (iss >> input && !input.empty())) {
		cout << errMsg << prompt;
		getline(cin, input);
		iss.str(input);
		iss.clear();
		iss.seekg(ios::beg);
	}

	return val;
}
