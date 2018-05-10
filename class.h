#include <iostream>
#include <array>
#include <cstring>
#include <vector>
#include <utility>
using namespace std;

#ifndef BOOK_LIMIT
#define BOOK_LIMIT 3
#endif

class Books{
private:
	char bookname[50];
	char author[50];
	int bookprice;
	int NoOfBooks;
	int NoOfIssuedBooks;
	int NoOfLeftBooks;

public:
	Books(char bname[], char auth[], int bp, int nob){
		strcpy(bookname, bname);
		strcpy(author, auth);
		NoOfBooks = nob;
		NoOfLeftBooks = nob;
		NoOfIssuedBooks = 0;
		bookprice = bp;
	}

	Books(){}
	void nameOfBook(char name[]){
		strcpy(name, bookname);
	}

	void addCopies(int a)
	{
		NoOfBooks += a;
	}

	bool ifLeft()
	{
		return NoOfLeftBooks;
	}

	printBookDetails() {
		cout << "Name of the Book: " << bookname << endl;
		cout << "Author of the Book: " << author << endl;	
		cout << "Price of the Book: " << bookprice << endl;
		cout << "Number of copies of Books: " << NoOfBooks << endl;
	}

	printBookDetails(int x)
	{
		cout << "Author of the Book: " << author << endl;	
		cout << "Price of the Book: " << bookprice << endl;
		cout << "Number of copies of Books: " << NoOfBooks << endl;	
	}
};

struct IshDetails
{
	int date;
	int time;
	char bookname[50];	
};

class Student
{
private:
	long long int rollNo;
	int booksIssued;
	int fine;
	struct IshDetails details[BOOK_LIMIT];
public:
	Student();
	~Student();
	
};