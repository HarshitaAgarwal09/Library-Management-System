#include<fstream>
#include<iostream>
#include<cstring>
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
	Books(char bname[], char auth[], int bp, int nob, int noib, int nolb){
		strcpy(bookname, bname);
		strcpy(author, auth);
		NoOfBooks = nob;
		NoOfLeftBooks = nolb;
		NoOfIssuedBooks = noib;
		bookprice = bp;
	};
	Books(){

	}
	getBooksDetails() {
		cout << "Enter name of the book: ";
		cin.getline(bookname, 50);

		cout << "Enter author name: ";
		cin.getline(author, 50);

		cout << "Enter the price of the Book: ";
		cin >> bookprice;
		cin.ignore();
		cout << "Enter the no of copies of books: ";
		cin >> NoOfBooks;
		cin.ignore();
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
// 
int main(){
	ifstream fin("data.txt", ios::in);
	// ifstream fin("newData.txt", ios::in);
	int totl;
	fin >> totl;
	cout << "total books: " << totl << endl;
	Books book;
	while(fin.read((char*)&book, sizeof(book)))
	{
		book.printBookDetails();
	}
	fin.close();
}