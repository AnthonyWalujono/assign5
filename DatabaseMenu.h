#ifndef CPSC_350_DATABASE_MENU_H
#define CPSC_350_DATABASE_MENU_H

#include <climits>
#include <cfloat>
#include "DatabaseCommand.h"
#include "DoublyLinkedList.h"

class DatabaseMenu
{
public:

	static const int MAX_ROLLBACKS = 5;

	void run();

private:

	const char* const studentDBFilename = "studentTable"; //*
	const char* const facultyDBFilename = "facultyTable"; //*

	BST<Student> students;
	BST<Faculty> faculty;

	DoublyLinkedList<DatabaseCommand*> prevCommands;

	void buildMasterDb();
	void writeTableFiles() const;

	int getChoice() const;

	void displayAllStudents() const;
	void displayAllFaculty() const;
	void findAndDisplayStudent() const;
	void findAndDisplayFaculty() const;
	void printAdvisorForStudent() const;
	void printAdviseesForFaculty() const;

	void addStudent();
	void deleteStudent();
	void addFaculty();
	void deleteFaculty();
	void changeAdvisor();
	void deleteAdvisee();

	void rollBack();

	void pushPrevCommands(DatabaseCommand*);

	void waitForEnterKey() const;
	int getInt(const std::string& prompt, const std::string errMsg, int minValid = INT_MIN, int maxValid = INT_MAX) const;
	double getDouble(const std::string& prompt, const std::string errMsg, double minValid = DBL_MIN, double maxValid = DBL_MAX) const;
};

#endif
