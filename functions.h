#ifndef FUNCTIONS
#define FUNCTIONS
#include <fstream>
#include <iostream>
#include <string>
#include <D:\Git\Library-Management-System\class.h>
using namespace std;

/*
dgtsIn()			line: 17
locatn()		line: 30
AddBook()			line: 72
viewDatabase()		line: 141
searchBook()		line: 156
uploadStdnts()	line: 175
createBkDatabs()	line: 211
viewDatabasestd()	line: 233
*/

int dgtsIn(long long int x)
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
	ifstream fin("books.txt",ios::in);
	int totalBook;
	fin >> totalBook;
	if(!totalBook)return -1;
	int dig = dgtsIn(totalBook);
	
	long long int beg = 0;
	long long int end = max((totalBook - 1)* sizeof(Book), (long long unsigned int)0);
	long long int mid;

	while(true){
		if(beg > end){
			mid = -1;
			break;
		}

		mid = (beg + end) / 2;
		mid -= (mid % sizeof(Book));
		fin.seekg(mid + dig, fin.beg);
		Book book;
		fin.read((char*)&book, sizeof(book));
		char name[50];
		book.name(name);
		int cmp = strcmp(bname, name);
		
		if(cmp < 0)end = mid - sizeof(Book);
		else if(cmp == 0)break;
		else beg = mid + sizeof(Book);
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
	ifstream fin("books.txt", ios::in);
	ofstream fout("newdata.txt", ios::out);
	int totalBook;
	fin >> totalBook;
	Book book;

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
		Book newBook(bname, auth, bp, copies, copies);
		++totalBook;		
		fout << totalBook;
		bool printd = false;

		while(fin.read((char*)&book, sizeof(book)))
		{
			char name[50];
			book.name(name);
			
			if (strcmp(name, bname) < 0 or printd)fout.write((char*)&book, sizeof(Book));
			else
			{
				fout.write((char*)&newBook, sizeof(Book));
				fout.write((char*)&book ,sizeof(Book));
				printd = true;
			}
		}
		
		if (!printd)fout.write((char*)&newBook, sizeof(Book));
	}

	else
	{
		fout << totalBook;
		cout << "Enter number of copies: ";
		int copies;
		cin >> copies;
		
		while(fin.read((char*)&book, sizeof(book)))
		{
			char name[50];
			book.name(name);
			if (strcmp(name, bname))fout.write((char*)&book, sizeof(Book));
			else
			{
				book.addCopies(copies);
				fout.write((char*)&book, sizeof(Book));
			}
		}	
	}
	fin.close();
	fout.close();
	remove("books.txt");
	rename("newdata.txt", "books.txt");
}

void viewBooks()
{
	ifstream fin("books.txt");
	int totalBook;
	fin >> totalBook;
	cout << endl << "Total number of Book: " << totalBook << endl << endl;
	Book book;
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
		ifstream fin("books.txt");
		fin.seekg(positn, fin.beg);
		Book book;
		fin.read((char*)&book, sizeof(Book));
		book.printDetails(0);
		fin.close();
	}
	else cout << "We don't have this book !!" << endl;
}

void uploadStdnts()
{
	ifstream fin("studentdata.txt");
	char c;
	int totl;
	
	if (fin.read((char*)&c, sizeof(char))) {
		fin.seekg(0, fin.beg);		
		fin >> totl;
	}
	else
	{
		cout << endl << "No data available to upload !!" << endl;
		return;	
	}

	ofstream fout("studentsBin.txt");
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

	fin.open("studentsBin.txt");
	ifstream finOld("students.txt");
	Student s1;
	bool newEnd = false, oldEnd = true;
	
	if (finOld.read((char*)&s1, sizeof(Student))) {
		oldEnd = false;
		finOld.seekg(0, finOld.beg);
	}
	else
	{
		fin.close();
		rename("studentsBin.txt", "students.txt");
		return;
	}

	int newTotl, oldTotl;
	fin >> newTotl;
	finOld >> oldTotl;
	fout.open("newStdnts.txt");
	fout << newTotl + oldTotl;
	Student s2;

	if(!fin.read((char*)&s1, sizeof(Student))) newEnd = true;
	if(!finOld.read((char*)&s2, sizeof(Student))) oldEnd = true;
	
	while(true){
		if(!newEnd and !oldEnd){
			if (s1.RollNo() < s2.RollNo()) {
				fout.write((char*)&s1, sizeof(Student));
				if(!fin.read((char*)&s1, sizeof(Student))) newEnd = true;
			}
			else
			{
				fout.write((char*)&s2, sizeof(Student));
				if(!finOld.read((char*)&s2, sizeof(Student))) oldEnd = true;
			}
		}
		else if(!newEnd){
			fout.write((char*)&s1, sizeof(Student));
			if(!fin.read((char*)&s1, sizeof(Student))) newEnd = true;
		}
		else if(!oldEnd){
			fout.write((char*)&s2, sizeof(Student));
			if(!finOld.read((char*)&s2, sizeof(Student))) oldEnd = true;
		}
		else break;
	}
fin.close();
finOld.close();
fout.close();
remove("students.txt");
remove("studentsBin.txt");
rename("newStdnts.txt", "students.txt");	
}	


struct srting
{
	int num;
	char bname[50];
	srting(int x, char name[])
	{
		num = x;
		strcpy(bname, name);
	}
};

int partition(std::vector<struct srting>* dummy, int beg, int end)
{
	char endName[50];
	strcpy(endName, (*dummy)[end - 1].bname);
	int pivot = beg - 1;

	for (int i = beg; i < end; ++i) if(strcmp((*dummy)[i].bname, endName) <= 0)
	{
		swap((*dummy)[i], (*dummy)[pivot + 1]);
		++ pivot;
	}

	return pivot;
}

void quickSrt(std::vector<struct srting>* dummy, int beg, int end)
{
	if(beg >= end)return;
	int pivot = partition(dummy, beg, end);
	quickSrt(dummy, beg, pivot);
	quickSrt(dummy, pivot + 1, end);
}


void uploadBook()
{
	ifstream finNew("bookdata.txt");
	ofstream fout("newdata.txt");
	int totlNew;
	char c;
	
	if (finNew.read((char*)&c, sizeof(char))) {
		finNew.seekg(0, finNew.beg);
		finNew >> totlNew;
	}
	else
	{
		cout << endl << "No books to upload" << endl;
		return;
	}
	
	
	fout << totlNew;
	int dig = dgtsIn(totlNew);
	std::vector<struct srting> dummy;
	int num = -1;
 	
	for (int i = 0; i < totlNew; ++i)
	{
		char bname[50];
		finNew >> bname;
		char auth[50];
		finNew >> auth;
		int price, tot, left;
		finNew >> price >> tot >> left;
		Book b(bname, auth, price, tot, left);
		fout.write((char*)&b, sizeof(Book));
		++ num;
		struct srting s(num, bname);
		dummy.push_back(s);
	}
	finNew.close();
	fout.close();
	finNew.open("newdata.txt");
	quickSrt(&dummy, 0, num + 1);
	ofstream foutTemp("srtd.txt");
	foutTemp << totlNew;	

	for (int i = 0; i < num + 1; ++i)
	{
		finNew.seekg(dig + dummy[i].num * sizeof(Book), finNew.beg);
		Book book;
		finNew.read((char *)&book, sizeof(Book));
		foutTemp.write((char *)&book, sizeof(Book));
	}
	//created srtd.txt from bookdata.txt
	finNew.close();
	foutTemp.close();
	remove("newdata.txt");

	ifstream fin;
	fin.open("srtd.txt");
	ifstream finOld;
	finOld.open("books.txt");
	Book book2;

	if(finOld.read((char *)&book2, sizeof(book2)))
	{
		finOld.seekg(0, finOld.beg);
		ofstream fout("newdata.txt");
		int newTot;
		fin >> newTot;
		int oldTot;
		finOld >> oldTot;
		int digN = dgtsIn(newTot);
		int digO = dgtsIn(oldTot);
		fout << newTot + oldTot;
		fin.seekg(digN, fin.beg);
		finOld.seekg(digO, finOld.beg);
		Book book1, book2;
		bool prsntNew = true;
		fin.read((char *)&book1, sizeof(book1));
		bool prsntOld = true;
		finOld.read((char *)&book2, sizeof(book2));
		int dcrmnt = 0;

		while(true){
			if (prsntNew and prsntOld){
				char name1[50], name2[50];
				book1.name(name1);
				book2.name(name2);
				
				if (strcmp(name1, name2) < 0) {
					fout.write((char *)&book1, sizeof(book1));
					if(!fin.read((char *)&book1, sizeof(book1)))prsntNew = false;				
				}
				else if(strcmp(name1, name2) > 0)
				{
					fout.write((char *)&book2, sizeof(book2));
					if(!finOld.read((char *)&book2, sizeof(book2)))prsntOld = false;
				}
				else
				{
					book2.mergeBooks(book1.copies(), book1.left());
					dcrmnt ++;
					fout.write((char*)&book2, sizeof(Book));
					if(!fin.read((char *)&book1, sizeof(book1)))prsntNew = false;				
					if(!finOld.read((char *)&book2, sizeof(book2)))prsntOld = false;
				}
				
			}
			else if(prsntNew){
				fout.write((char *)&book1, sizeof(book1));
				if(!fin.read((char *)&book1, sizeof(book1)))prsntNew = false;
			}
			else if(prsntOld){
				fout.write((char *)&book2, sizeof(book2));
				if(!finOld.read((char *)&book2, sizeof(book2))) prsntOld = false;
			}
			else break;
		}
		//merged bookdata.txt with books.txt in newdata.txt
		fin.close();
		finOld.close();
		fout.close();
		
		if (dcrmnt) {
			fin.open("newdata.txt");
			fout.open("newdataDcr.txt");
			fin >> totlNew;
			fout << totlNew - dcrmnt;
			
			while(fin.read((char*)&book1, sizeof(Book))) fout.write((char*)&book1, sizeof(Book));
			
			fin.close();
			fout.close();
			remove("newdata.txt");
			rename("newdataDcr.txt", "newdata.txt");
		}
		
		remove("books.txt");
		remove("srtd.txt");
		rename("newdata.txt", "books.txt");		
		
	}
	else
	{
		fin.close();
		rename("srtd.txt", "books.txt");
	}
	
}

void viewStudents()
{
	ifstream fin("students.txt");
	int totl;
	
	if (!fin.read((char *)&totl, sizeof(int))){
		cout << endl << "Total number of students: 0" << endl;
		return;
	}
	fin.seekg(0, fin.beg);
	
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

void searchStudent()
{
	ifstream fin("students.txt");
	long long int totlStudents;
	fin >> totlStudents;
	int digits = dgtsIn(totlStudents);
	cout << "Enter Roll number: ";
	long long int rollNo;
	cin >> rollNo;
	long long int begin = 0;
	long long int end = max(digits + (totlStudents - 1) * sizeof(Student), (long long unsigned int)0 );
	long long mid;
	
	while(true){
		
		if (begin > end) {
			mid = -1;
			break;
		}
		
		mid = (begin + end) / 2;
		mid -= mid % sizeof(Student);
		fin.seekg(mid + digits, fin.beg);
		Student s1;
		fin.read((char*)&s1, sizeof(Student));
		if (s1.RollNo() == rollNo) break;
		else if(s1.RollNo() > rollNo) end = mid - sizeof(Student);
		else begin = mid + sizeof(Student);
	}
	
	if (mid == -1) {
		cout << endl << " Roll number " << rollNo << " has no book issued." << endl;
		return;
	}
	else
	{
		Student s1;
		fin.seekg(mid + digits, fin.beg);
		fin.read((char*)&s1, sizeof(Student));
		s1.printDetails(0);
	}
}

#endif