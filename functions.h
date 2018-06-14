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


void uploadBooks()
{
	ifstream finNew("bookdata.txt");
	ofstream fout("newdata.txt");
	int totlNew;
	finNew >> totlNew;
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
		Books b(bname, auth, price, tot, left);
		fout.write((char*)&b, sizeof(Books));
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
		finNew.seekg(dig + dummy[i].num * sizeof(Books), finNew.beg);
		Books book;
		finNew.read((char *)&book, sizeof(Books));
		foutTemp.write((char *)&book, sizeof(Books));
	}

	finNew.close();
	foutTemp.close();
	remove("newdata.txt");

	ifstream fin;
	fin.open("srtd.txt");
	ifstream finOld;
	finOld.open("data.txt");
	Books book2;

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
		Books book1, book2;
		bool prsntNew = true;
		fin.read((char *)&book1, sizeof(book1));
		bool prsntOld = true;
		finOld.read((char *)&book2, sizeof(book2));

		while(true){
			if (prsntNew and prsntOld){
				char name1[50], name2[50];
				book1.name(name1);
				book2.name(name2);
				
				if (strcmp(name1, name2) < 0) {
					fout.write((char *)&book1, sizeof(book1));
					if(!fin.read((char *)&book1, sizeof(book1)))prsntNew = false;				
				}
				else
				{
					fout.write((char *)&book2, sizeof(book2));
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

		fin.close();
		finOld.close();
		fout.close();
		remove("data.txt");
		remove("srtd.txt");
		rename("newdata.txt", "data.txt");		
		
	}
	else
	{
		fin.close();
		rename("srtd.txt", "data.txt");
	}
	
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
