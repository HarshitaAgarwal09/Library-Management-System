#include<iostream>
#include<fstream>
#include<string.h>
#include<cstdio>
#include<cmath>
using namespace std;

// class Student {
// private:
// 	char name[50];
// 	int Rollno;
// 	int fine;
// 	int booksissued = 0;
// public:
// 	getStudentDetails() {
// 		cout << "Enter the name of student: ";
// 		cin.getline(name, 50);
// 		cout << "Enter the Roll no.: ";
// 		cin >> Rollno;
// 	}
// 	printStudentDetails() {
// 		cout << "Name of the Student: " << name << endl;
// 		cout << "Rollno of the Student: " << Rollno << endl;
// 		if (fine > 0) {
// 			cout << "Fine of the Student: " << fine << endl;
// 		}
// 		else
// 		{
// 			cout << "No fine" << endl;
// 		}
// 		if (booksissued == 0) {
// 			cout << "No Books Issued: " << endl;
// 		}
// 	}
// 	modifyStudentDetails() {
// 		cout << "Enter the modified name of Student: ";
// 		gets(name);
// 	}
// 	int setbookissued() {
// 		booksissued = 1;
// 		return booksissued;
// 	}
// 	void resetbookissued() {
// 		booksissued = 0;
// 	}
// };

class Books{
private:
	char bookname[50];
	char author[50];
	int bookprice;
	int NoOfBooks;
	int NoOfIssuedBooks;
	int NoOfLeftBooks;
public:
	Books(char bname[], char auth[], int bp, int nob, int noib, int nolb){
		strcpy(bookname, bname);
		strcpy(author, auth);
		NoOfBooks = nob;
		NoOfLeftBooks = nolb;
		NoOfIssuedBooks = noib;
		bookprice = bp;
	};
	Books(){}
	void nameOfBook(char name[]){
		strcpy(name, bookname);
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
	// modifyBookDetails() {
	// 	cout << "Enter modified Books name: ";
	// 	gets(bookname);
	// 	cout << "Enter modified price: ";
	// 	cin >> bookprice;
	// }
};

// void write_Books() {
// 	ofstream fout("books.txt");
// 	char ch;
// 	Books bk("hey", "hii", 1, 2, 3, 4);
// 	do{
// 		bk.getBooksDetails();
// 		fout.write((char*)&bk, sizeof(bk));
// 		cout << "Continue to add more books(Y/N)?" << endl;
// 		cin >> ch;
// 	}while(ch == 'y' || ch == 'Y');

// 	fout.close();
// }

// void read_Books() {
// 	Books bk("hey", "hii", 1, 2, 3, 4);

// 	ifstream b("books.txt");
// 	while (b.read((char*)&bk, sizeof(bk))) {
// 	bk.printBookDetails();
// 		b.read((char*)&bk, sizeof(bk));
// 	}
// 	b.close();
// }

// ofstream sf("student.txt");
// void addStudents() {
// 	Student stud;

// 	while (read((char*)&stud),) {

// 	}
// }

int totalBooks;

int locatnInDb(char bname[]){			//binary search the database of the book
	ifstream fin("data.txt",ios::in);
	fin >> totalBooks;
	int totalBooksSize;
	if(totalBooks < 256)totalBooksSize = 2;
	else totalBooksSize = 4;
	int beg = totalBooksSize;
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
		fin.seekg(mid + totalBooksSize, fin.beg);
		Books book;
		fin.read((char*)&book, sizeof(book));
		char name[50];
		book.nameOfBook(name);
		int cmp = strcmp(bname, name);
		if(cmp < 0)end = mid - sizeof(Books);
		else if(cmp == 0)break;
		else beg = mid + sizeof(Books);
	}

	return mid + totalBooksSize;
}

void AddBook(){
	cout << "Enter name of the Book : ";
	char bname[50];
	cin.getline(bname, 50);
	int positn = locatnInDb(bname);
	
	if(positn != -1){

	}else{

	}
	
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