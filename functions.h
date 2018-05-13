#include <fstream>
#include <iostream>
#include <D:\Git\Library-Management-System\class.h>
using namespace std;

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

long long int locatnInDb(char bname[]){			//binary search the database of the book
	ifstream fin("data.txt",ios::in);
	int totalBooks;
	fin >> totalBooks;
	if(!totalBooks)return -1;
	int dig = 0;
	int num = totalBooks;

	while(num)
	{
		++ dig;
		num /= 10;
	}

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
		book.nameOfBook(name);
		int cmp = strcmp(bname, name);
		if(cmp < 0)end = mid - sizeof(Books);
		else if(cmp == 0)break;
		else beg = mid + sizeof(Books);
	}

	fin.close();
	if(mid == -1)return -1;
	else return mid + dig;
}

void AddBook(){
	cout << "Enter name of the Book : ";
	char bname[50];
	cin.getline(bname, 50);
	long long int positn = locatnInDb(bname);
	ifstream fin("data.txt", ios::in);
	ofstream fout("newdata.txt", ios::out);
	int totalBooks;
	fin >> totalBooks;
	Books book;

	if (positn == -1)
	{
		cout << "Enter name of the author: ";
		char auth[50];
		cin.getline(auth, 50);
		cout << "Enter price of the book: ";
		int bp;
		cin >> bp;
		cout << "Enter number of copies of the book: ";
		int copies;
		cin >> copies;
		Books newBook(bname, auth, bp, copies, 0);
		++totalBooks;		
		fout << totalBooks;
		bool printd = false;

		while(fin.read((char*)&book, sizeof(book)))
		{
			char name[50];
			book.nameOfBook(name);
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
			book.nameOfBook(name);
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

void viewDatabase()
{
	ifstream fin("data.txt");
	int totalBooks;
	fin >> totalBooks;
	cout << "Total number of books: " << totalBooks << endl;
	Books book;
	while(fin.read((char*)&book, sizeof(book)))
	{
		book.printBookDetails();
		cout << endl;
	}
	fin.close();
}

void searchBook()
{
	cout << "Enter name of the book: ";
	char bname[50];
	cin.getline(bname, 50);
	long long int positn = locatnInDb(bname);
	
	if (positn != -1)
	{
		ifstream fin("data.txt");
		fin.seekg(positn, fin.beg);
		Books book;
		fin.read((char*)&book, sizeof(Books));
		book.printBookDetails(1);
		fin.close();
	}
	else cout << "The following book does not exists!!" << endl;
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

void createBkDatabs()
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
		int bp, nob, noib;
		fin >> bp >> nob >> noib;
		Books book(bname, auth, bp, nob, noib);
		fout.write((char*)&book, sizeof(Books));
	}

	fin.close();
	fout.close();
}

void viewDatabasestd()
{
	ifstream fin("students.txt");
	int totl;
	fin >> totl;
	int dig = dgtsIn(totl);
	fin.seekg(dig, fin.beg);
	Student s;
	cout << "Total number of students: " << totl << endl;
	while(fin.read((char*)&s, sizeof(Student)))
	{
		s.printDetails();
		cout << endl;
	}
	fin.close();
}
// void issueBook()
// {
//    cout << "Enter the name of the book: ";
//    char bname[50];
//    cin.getline(bname, 50);
//    long long int positn = locatnInDb(bname);
   
//    if(positn == -1)
//    {
//       cout << "Sorry! we don't have this book" << endl;
//       return;
//    }

//    Books book;
//    ifstream fin("data.txt");
//    fin.seekg(positn, fin.beg());
//    fin.read((char*)&book, sizeof(book));
   
//    if(!book.ifLeft())
//    {
//       cout << "Sorry! we are out of stock for this book" << endl;
//       return;
//    }

//    long long int rollNO;
//    cout << "Enter the roll number of the student: ";
//    cin >> rollNO;
//    fin.close();
//    issueBook(rollNO, bname);
// }

// void issueBook(long long int rollNO, char bname[])
// {
// 	ifstream fin("data.txt");
// 	ofstream fout("newdata.txt");
// 	Books book;
// 	int totalBooks;
// 	fin >> totalBooks;
// 	fout << totalBooks;
// 	int dig = 0;
// 	int num = totalBooks;

// 	while(num)
// 	{
// 		++ dig;
// 		num /= 10;
// 	}
// 	fin.seekg(dig, fin.beg);

// 	while(fin.read((char*)&book, sizeof(Books)))
// 	{
// 		char name[50];
// 		book.nameOfBook(name);
// 		if(strcmp(name, bname) != 0)fout.write((char*)&book, sizeof(Books));
// 		else{
// 			book.issue();
// 			fout.write((char*)&book, sizeof(Books));
// 		}
// 	}

// 	//to be continued
// }
