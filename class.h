#ifndef CLASS
#define CLASS
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
using namespace std;

#define BOOK_LIMIT 3

class Book{
private:
	char Title[50];
	char author[50];
	int price;
	int NoOfCopies;
	int NoOfLeftCps;

public:
	Book(char bname[], char auth[], int bp, int nob, int nolb){
		strcpy(Title, bname);
		strcpy(author, auth);
		NoOfCopies = nob;
		NoOfLeftCps = nolb;
		price = bp;
	}

	Book(){}
	void name(char name[]){
		strcpy(name, Title);
	}

	void addCopies(int a)
	{
		NoOfCopies += a;
		NoOfLeftCps += a;
	}

	int copies(){
		return NoOfCopies;
	}

	void mergeBooks(int cps, int left)
	{
		NoOfCopies += cps;
		NoOfLeftCps += left;
	}

	int left(){
		return NoOfLeftCps;
	}

	bool ifLeft()
	{
		return NoOfLeftCps;
	}

	void printDetails() {
		cout << "Name of the Book: " << Title << endl;
		cout << "Author of the Book: " << author << endl;	
		cout << "Price of the Book: " << price << endl;
		cout << "Total number of copies of Book: " << NoOfCopies << endl;
		cout << "Number of copies available: " << NoOfLeftCps << endl;
		cout << endl;
	}

	void printDetails(int x) {
		cout << "Author of the Book: " << author << endl;	
		cout << "Price of the Book: " << price << endl;
		cout << "Total number of copies of Book: " << NoOfCopies << endl;
		cout << "Number of copies available: " << NoOfLeftCps << endl;
		cout << endl;
	}

	void dcr(){
		--NoOfLeftCps;
	}
};

struct IshDetails
{
	long int date = -1;
	int time = -1;
	char Title[50] = "\0";	

	IshDetails(char bname[], long int day, int t)
	{
		strcpy(Title, bname);
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
	Student(long long int rn, int fn)
	{
		rollNo = rn;
		booksIssued = 0;
		fine = fn;
		struct IshDetails s;
		details[0] = s;
	}

	Student(){}

	long long int RollNo()
	{
		return rollNo;
	}

	int totlIssued(){
		return booksIssued;
	}

	bool ifIssued(char bname[]){
		
		for(int i = 0; i < booksIssued; i++)
		{
			if(strcmp(details[i].Title, bname) == 0) return true;
		}

		return false;
	}

	void addDetails(struct IshDetails* s)
	{
		details[booksIssued] = *s;
		++booksIssued;
	}

	void printDetails()
	{
		cout << "Student Roll number: " << rollNo <<endl;
		cout << "Fine on Student: " <<fine << endl;
		cout << "Book issued on Student: " << booksIssued << endl;
		for (int i = 0; i < booksIssued; ++i)
		{
			cout << details[i].Title << '\t' << details[i].date / 1000000 << "-" << (details[i].date % 1000000) / 10000 << "-" << details[i].date % 10000;
			cout << '\t' << details[i].time / 100 << ":" << details[i].time % 100 << endl;

		}
	}

	void printDetails(int x)
	{
		cout << "Fine on Student: " <<fine << endl;
		cout << "Book issued on Student: "<< booksIssued << endl;
		for (int i = 0; i < booksIssued; ++i)
		{
			cout << details[i].Title << '\t' << details[i].date / 1000000 << "-" << (details[i].date % 1000000) / 10000 << "-" << details[i].date % 10000;
			cout << '\t' << details[i].time / 100 << ":" << details[i].time % 100 << endl;

		}
	}
};

#endif