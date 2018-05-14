#include <fstream>
#include <iostream>
#include <D:\Git\Library-Management-System\class.h>
using namespace std;

/*
dgtsIn()			line: 17
locatn()		line: 30
AddBook()			line: 72
viewDatabase()		line: 141
searchBook()		line: 156
createstdntDatabs()	line: 175
createBkDatabs()	line: 211
viewDatabasestd()	line: 233
*/

int dgtsIn(int x)
{
	int dig = 1;
	x /= 10;
	
	while(x)
	{
		dig++;
		x /= 10;
	}
	return dig;
}

long long int locatn(char bname[]){			//binary search the database of the book
	ifstream fin("data.txt",ios::in);
	int totalBooks;
	fin >> totalBooks;
	if(!totalBooks)return -1;
	int dig = dgtsIn(totalBooks);
	
	long long int beg = 0;
	long long int end = max((totalBooks - 1)* sizeof(Books), (long long unsigned int)0);
	long long int mid;

	while(true){
		if(beg > end){
			mid = -1;
			break;
		}

		mid = (beg + end) / 2;
		mid -= (mid % sizeof(Books));
		fin.seekg(mid + dig, fin.beg);
		Books book;
		fin.read((char*)&book, sizeof(book));
		char name[50];
		book.name(name);
		int cmp = strcmp(bname, name);
		
		if(cmp < 0)end = mid - sizeof(Books);
		else if(cmp == 0)break;
		else beg = mid + sizeof(Books);
	}

	fin.close();
	if(mid == -1)return -1;
	else return mid + dig;
}

void AddBook()
{
	cout << "Enter name of the Book : ";
	char bname[50];
	cin >> bname;
	long long int positn = locatn(bname);
	ifstream fin("data.txt", ios::in);
	ofstream fout("newdata.txt", ios::out);
	int totalBooks;
	fin >> totalBooks;
	Books book;

	if (positn == -1)
	{
		cout << "Enter name of the author: ";
		char auth[50];
		cin >> auth;
		cout << "Enter price of the book: ";
		int bp;
		cin >> bp;
		cout << "Enter number of copies of the book: ";
		int copies;
		cin >> copies;
		Books newBook(bname, auth, bp, copies, copies);
		++totalBooks;		
		fout << totalBooks;
		bool printd = false;

		while(fin.read((char*)&book, sizeof(book)))
		{
			char name[50];
			book.name(name);
			
			if (strcmp(name, bname) < 0 or printd)fout.write((char*)&book, sizeof(Books));
			else
			{
				fout.write((char*)&newBook, sizeof(Books));
				fout.write((char*)&book ,sizeof(Books));
				printd = true;
			}
		}
		
		if (!printd)fout.write((char*)&newBook, sizeof(Books));
	}

	else
	{
		fout << totalBooks;
		cout << "Enter number of copies: ";
		int copies;
		cin >> copies;
		
		while(fin.read((char*)&book, sizeof(book)))
		{
			char name[50];
			book.name(name);
			if (strcmp(name, bname))fout.write((char*)&book, sizeof(Books));
			else
			{
				book.addCopies(copies);
				fout.write((char*)&book, sizeof(Books));
			}
		}	
	}
	fin.close();
	fout.close();
	remove("data.txt");
	rename("newdata.txt", "data.txt");
}

void viewBooks()
{
	ifstream fin("data.txt");
	int totalBooks;
	fin >> totalBooks;
	cout << endl << "Total number of books: " << totalBooks << endl << endl;
	Books book;
	while(fin.read((char*)&book, sizeof(book)))
	{
		book.printDetails();
	}
	fin.close();
}

void searchBook()
{
	cout << "Enter name of the book: ";
	char bname[50];
	cin >> bname;
	long long int positn = locatn(bname);
	
	if (positn != -1)
	{
		ifstream fin("data.txt");
		fin.seekg(positn, fin.beg);
		Books book;
		fin.read((char*)&book, sizeof(Books));
		book.printDetails(0);
		fin.close();
	}
	else cout << "We don't have this book !!" << endl;
}

void createstdntDatabs()
{
	ifstream fin("studentdata.txt");
	ofstream fout("students.txt");
	int totl;
	fin >> totl;
	
	fout << totl;
	while(totl --)
	{
		int rollNo;
		fin >> rollNo;
		int nob;
		fin >> nob;
		int fine;
		fin >> fine;
		Student s1(rollNo, nob, fine);
		
		for (int i = 0; i < nob; ++i)
		{
			char bname[50];
			fin >> bname;
			long long int day;
			fin >> day;
			int time;
			fin >> time;
			struct IshDetails d1(bname, day, time);
			s1.addDetails(&d1, i);
		}

		fout.write((char*)&s1, sizeof(Student));
	}
	fin.close();
	fout.close();
}	

void uploadBooks()
{
	ifstream fin("bookdata.txt");
	ofstream fout("data.txt", ios::trunc);
	int tot;
	fin >> tot;
	fout << tot;
	
	while(tot --)
	{
		char bname[50], auth[50];
		fin >> bname >> auth;
		int bp, nob, nolb;
		fin >> bp >> nob >> nolb;
		Books book(bname, auth, bp, nob, nolb);
		fout.write((char*)&book, sizeof(Books));
	}

	fin.close();
	fout.close();
}

void viewStudents()
{
	ifstream fin("students.txt");
	int totl;
	fin >> totl;
	int dig = dgtsIn(totl);
	fin.seekg(dig, fin.beg);
	Student s;
	cout << endl << "Total number of students: " << totl << endl << endl;
	while(fin.read((char*)&s, sizeof(Student)))
	{
		s.printDetails();
		cout << endl;
	}
	fin.close();
}
