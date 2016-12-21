// CS 161 Assignment 7 - Library Database (main.cpp)
// May 27, 2016
// Author: Joseph Schell
// Sources: None

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

struct Book {
	string title;
	string author;
};

const int ARRAY_SIZE = 1000;
Book books[ARRAY_SIZE];

// Function Prototypes
int loadData(int & count, string pathname);
void showAll(int count);
int showBooksByAuthor(int count, string name);
int showBooksByTitle(int count, string title);
void sortByTitle(int count);
void sortByAuthor(int count);

int main()
{
	string menuSelection, filePath, authorName, titleName;
	int currentIndex = 0;

	cout << "Welcome to Joe's Library Database" << endl;
	cout << "Please enter the name of the backup file: ";
	getline(cin, filePath);
	loadData(currentIndex, filePath);

	do {

		cout << "\nEnter Q to (Q)uit, Search (A)uthor, Search (T)itle, (S)how All: ";
		getline(cin, menuSelection);

		if (menuSelection.length() == 0) {
			menuSelection = ".";
		}
		switch (menuSelection.at(0)) {
		case 'a':
		case 'A':
			cout << "Author's Name: ";
			getline(cin, authorName);
			showBooksByAuthor(currentIndex, authorName);
			break;
		case 't':
		case 'T':
			cout << "Title: ";
			getline(cin, titleName);
			showBooksByTitle(currentIndex, titleName);
			break;
		case 's':
		case 'S':
			showAll(currentIndex);
			break;
		case 'q':
		case 'Q':
			break;
		default:
			cout << "Invalid selection. Please try again." << endl;
			break;
		}
	} while (menuSelection.substr(0, 1) != "q" && menuSelection.substr(0, 1) != "Q");
	return 0;
}

// Loads data of file name that was input by user.
int loadData(int & count, string pathname) {

	ifstream inFile;
	inFile.open(pathname.c_str());


	if (!inFile.is_open()) {
		cout << "Error opening input file." << endl;
		return 0;
	}
	getline(inFile, pathname);

	for (int i = 0; i < pathname.length(); i++) {
		books[i].title = pathname;
		getline(inFile, pathname);
		books[i].author = pathname;
		getline(inFile, pathname);

		count++;
	}
	inFile.close();
	inFile.clear(std::ios_base::goodbit);

	cout << count << " records loaded successfully." << endl;
	return 0;
}

// Converts a string to all lowercase.
string toLower(string input) {
	string output = "";
	for (int i = 0; i < input.length(); i++) {
		output += tolower(input[i]);
	}
	return output;
}

// Search function to find books by inputting Author's name.
int showBooksByAuthor(int count, string name) {
	int records = 0;
	sortByAuthor(count);  // Sort prior to searching

	for (int i = 0; i < count; i++) {
		if (toLower(books[i].author).find(toLower(name)) != string::npos) {
			// Converts both strings to lowercase for comparison
			records++;
			cout << books[i].title << " (" << books[i].author << ")\n";
		}
	}
	cout << records << " record(s) found." << endl;
	return 0;
}

// Search function to find books by inputting the name of the book.
int showBooksByTitle(int count, string title) {
	int records = 0;
	sortByTitle(count);  // Sort prior to searching

	for (int i = 0; i < count; i++) {
		if (toLower(books[i].title).find(toLower(title)) != string::npos) {
			// Converts both strings to lowercase for comparison
			records++;
			cout << books[i].title << " (" << books[i].author << ")\n";
		}
	}
	cout << records << " record(s) found." << endl;
	return 0;
}

// Shows all books in database.
void showAll(int count) {
	cout << "\n";
	sortByTitle(count);

	for (int i = 0; i < count; i++) {
		cout << books[i].title << " " << "(" << books[i].author << ")" << endl;
	}
}

// Simple bubble sort, sorts author's names alphabetically.
void sortByAuthor(int count) {
	Book t;
	for (int i = count - 1; i >= 0; i--) {
		for (int j = 1; j <= i; j++) {
			if (books[j - 1].author > books[j].author) {
				t = books[j - 1];
				books[j - 1] = books[j];
				books[j] = t;
			}
		}
	}
}

// Another bubble sort, sorts book titles alphabetically.  
void sortByTitle(int count) {
	Book t;
	for (int i = count - 1; i >= 0; i--) {
		for (int j = 1; j <= i; j++) {
			if (books[j - 1].title > books[j].title) {
				t = books[j - 1];
				books[j - 1] = books[j];
				books[j] = t;
			}
		}
	}
}





