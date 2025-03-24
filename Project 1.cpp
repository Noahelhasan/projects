/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

struct student {
	string id;
	string name;
	vector<double> grades;

	double averageGrade() const {
		if (grades.empty()) return 0.0;
		double sum = 0;
		for (double grade : grades) sum += grade;
		return sum / grades.size();
	}

	double highestGrade() const {
		if (grades.empty()) return 0.0;
		return *max(grades.begin(), grades.end());
	}

	double lowestGrade() const {
		if (grades.empty()) return 0.0;
		return *min(grades.begin(), grades.end());
	}
};

vector<student> students;
const string FILE_NAME = "students.txt";

void saveToFile() {
	ofstream file(FILE_NAME);
	for (const auto& student : students) {
		file << student.id << " " << student.name << " " << student.grades.size();
		for (double grade : student.grades) file << " " << grade;
		file << endl;
	}
	file.close();
}

void loadFromFile() {
	ifstream file(FILE_NAME);
	if (!file) return;
	students.clear();
	string id, name;
	int numGrades;
	while (file >> id >> name >> numGrades) {
		student student{ id, name, {} };
		for (int i = 0; i < numGrades; i++) {
			double grade;
			file >> grade;
			student.grades.push_back(grade);
		}
		students.push_back(student);
	}
	file.close();
}

void addStudent() {
	student student;
	cout << "Enter Student ID: "; cin >> student.id;
	cout << "Enter Student Name: "; cin >> student.name;
	int numGrades;
	cout << "Enter the number of grades (max 5): "; cin >> numGrades;
	student.grades.resize(numGrades);
	for (int i = 0; i < numGrades; i++) {
		cout << "Enter grade " << i + 1 << ": ";
		cin >> student.grades[i];
	}
	students.push_back(student);
	saveToFile();
	cout << "Student data saved to file.\n";
}

void searchStudent() {
	string searchID;
	cout << "Enter the Student ID to search for: "; cin >> searchID;
	for (const auto& student : students) {
		if (student.id == searchID) {
			cout << "Student Found!\nID: " << student.id << "\nName: " << student.name
				<< "\nAverage Grade: " << student.averageGrade()
				<< "\nHighest Grade: " << student.highestGrade()
				<< "\nLowest Grade: " << student.lowestGrade() << "\n";
			return;
		}
	}
	cout << "Student with ID " << searchID << " not found.\n";
}

void displayStatistics() {
	if (students.empty()) {
		cout << "No students to display.\n";
		return;
	}
	double sum = 0;
	double highest = numeric_limits<double>::min();
	double lowest = numeric_limits<double>::max();
	for (const auto& student : students) {
		double average = student.averageGrade();
		sum += average;
		if (average > highest) highest = average;
		if (average < lowest) lowest = average;
	}
	cout << "Average of all students: " << sum / students.size() << "\n";
	cout << "Highest average grade: " << highest << "\n";
	cout << "Lowest average grade: " << lowest << "\n";
}

void menu() {
	int choice;
	do {
		cout << "_____Student Grade Managment System_____\n"
			<< "1. Add a New Student\n"
			<< "2. Search for a student\n"
			<< "3. Display Class Statistics\n"
			<< "4. Exit\n"
			<< "5. Enter your choice (1-4): ";
		cin >> choice;
		switch (choice) {
		case 1: addStudent(); break;
		case 2: searchStudent(); break;
		case 3: displayStatistics(); break;
		case 4: cout << "exiting program.\n"; break;
		default: cout << "Invalid choice. Please try again.\n";
		}
	} while (choice != 4);

}

int main() {
	loadFromFile();
	menu();
	return 0;
}



