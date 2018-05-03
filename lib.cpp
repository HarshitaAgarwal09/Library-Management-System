#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
class Student {

	char name[50];
	int Rollno;
	int fine;
	int booksissued = 0;
public:
	getStudentDetails() {
		cout << "Enter the name of student: ";
		cin.getline(name, 50);
		cout << "Enter the Roll no.: ";
		cin >> Rollno;
	}
	printStudentDetails() {
		cout << "Name of the Student: " << name << endl;
		cout << "Rollno of the Student: " << Rollno << endl;
		if (fine > 0) {
			cout << "Fine of the Student: " << fine << endl;
		}
		else
		{
			cout << "No fine" << endl;
		}
		if (booksissued == 0) {
			cout << "No Books Issued: " << endl;
		}
	}
	modifyStudentDetails() {
		cout << "Enter the modified name of Student: ";
		gets(name);
	}
	int setbookissued() {
		booksissued = 1;
		return booksissued;
	}
	void resetbookissued() {
		booksissued = 0;
	}
};

class Books {
	char bookname[50];
	int NoOfBooks;
	int NoOfLeftBooks;
	int NoOfIssuedBooks = 0;
	char author[50];
	int bookprice;
public:
	getBooksDetails() {
		cout << "Enter name of the book: ";
		cin.sync();
		cin.getline(bookname, 50);

		cout << "Enter author name: ";
		cin.sync();
		cin.getline(author, 50);

		cout << "Enter the price of the Book: ";
		cin >> bookprice;
		cout << "Enter the no of copies of books: ";
		cin >> NoOfBooks;
	}
	printBookDetails() {
		cout << "Name of the Book: " << bookname << endl;
		cout << "Author of the Book: " << author << endl;
		cout << "Price of the Book: " << bookprice << endl;
		cout << "Number of copies of Books: " << NoOfBooks << endl;
	}
	modifyBookDetails() {
		cout << "Enter modified Books name: ";
		gets(bookname);
		cout << "Enter modified price: ";
		cin >> bookprice;
	}
};

Books bk;
int total = 0;

void write_Books() {
	int added;
	char ch = 'Y';
	ofstream bf("books.txt");
	while (ch == 'y' || ch == 'Y') {
		bk.getBooksDetails();
		bf.write((char*)&bk, sizeof(bk));
		cout << "Continue(Y/N)?";
		cin >> ch;
	}
	bf.close();
}

void read_Books() {
	ifstream b("books.txt");
	while (b.read((char*)&bk, sizeof(bk))) {
	bk.printBookDetails();
		b.read((char*)&bk, sizeof(bk));
	}
	b.close();
}

ofstream sf("student.txt");
void addStudents() {
	Student stud;

	while (read((char*)&stud),) {

	}
}

int main() {
	write_Books();
	/* cout<<"1. Enter Book Details."<<endl;
		cout<<"2. Print Book Details."<<endl;
		cout<<"3. Enter Student Record."<<endl;
		cout<<"4. Print Student Record."<<endl;
	*/
	//cout << "total: " << total;
	return 0;

}