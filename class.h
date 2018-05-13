#include <iostream>
#include <array>
#include <cstring>
#include <vector>
#include <utility>
#include <fstream>
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
	Books(char bname[], char auth[], int bp, int nob, int noib){
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
		NoOfLeftBooks += a;
	}

	bool ifLeft()
	{
		return NoOfLeftBooks;
	}

	void issue()
	{
		NoOfLeftBooks--;
		NoOfIssuedBooks ++;
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
	long long int date;
	int time;
	char bookname[50];	

	IshDetails(char bname[], long long int day, int t)
	{
		strcpy(bookname, bname);
		date = day;
		time = t;
	};

	IshDetails(){}
};

class Student
{
private:
	long long int rollNo;
	int booksIssued;
	int fine;
	struct IshDetails details[BOOK_LIMIT];
public:
	Student(int rn, int nob, int fn)
	{
		rollNo = rn;
		booksIssued = nob;
		fine = fn;
		struct IshDetails s;
		details[0] = s;
	}

	Student(){}

	void addDetails(struct IshDetails* s, int i)
	{
		details[i] = *s;
	}

	void printDetails()
	{
		cout << "Student Roll number: " << rollNo <<endl;
		cout << "Fine on Student: " <<fine << endl;
		cout << "Books issued on Student: "<< endl;
		for (int i = 0; i < booksIssued; ++i)
		{
			cout << details[i].bookname << '\t' << details[i].date / 1000000 << "-" << (details[i].date % 1000000) / 10000 << "-" << details[i].date % 10000;
			cout << '\t' << details[i].time / 100 << ":" << details[i].time % 100 << endl;

		}
	}
};

