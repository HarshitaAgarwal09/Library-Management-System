#include<iostream>
#include<fstream>
#include<string.h>
#include<cstdio>
#include<cmath>
using namespace std;

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
	};
	Books(){}
	void nameOfBook(char name[]){
		strcpy(name, bookname);
	}

	void addCopies(int a)
	{
		NoOfBooks += a;
	}
	// getBooksDetails() {
	// 	cout << "Enter name of the book: ";
	// 	cin.ignore();
	// 	cin.getline(bookname, 50);

	// 	cout << "Enter author name: ";
	// 	cin.ignore();
	// 	cin.getline(author, 50);

	// 	cout << "Enter the price of the Book: ";
	// 	cin >> bookprice;
	// 	cout << "Enter the no of copies of books: ";
	// 	cin >> NoOfBooks;
	// }
	printBookDetails() {
		cout << "Name of the Book: " << bookname << endl;
		cout << "Author of the Book: " << author << endl;	
		cout << "Price of the Book: " << bookprice << endl;
		cout << "Number of copies of Books: " << NoOfBooks << endl;
	};
};

int locatnInDb(char bname[]){			//binary search the database of the book
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
	int beg = dig;
	int end = beg;
	end += max((totalBooks - 1)* sizeof(Books), (long long unsigned int)0);
	int mid;

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
	return mid;
}

void AddBook(){
	cout << "Enter name of the Book : ";
	char bname[50];
	cin.getline(bname, 50);
	int positn = locatnInDb(bname);
	ifstream fin("data.txt", ios::in);
	ofstream fout("newdata.txt", ios::out);
	int totalBooks;
	fin >> totalBooks;
	int dig = 0;
	int num = totalBooks;
	
	while(num)
	{
		++ dig;
		num /= 10;
	}
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
		Books newBook(bname, auth, bp, copies);
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

int main() {
	cout << "(1) Add a book\n(2)Delete a book\n(3)Issue a book\n(4)Return a book\n(5)Exit" << endl;
	char c;

	do{
		cin >> c;
		cin.ignore();
		switch(c){
			case '1': AddBook();
			break;
			// case '2': DeleteBook();
			// break;
			// case '3': IssueBook();
			// break;
			// case '4': ReturnBook();
			// break;
			default:;
		};
	} while (c != '5');

	return 0;
}