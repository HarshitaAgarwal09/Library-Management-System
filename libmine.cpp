#include<iostream>
#include<fstream>
#include<cstring>
#include <D:\Git\Library-Management-System\functions.h>

using namespace std;

int main() {
	cout << "(1)Add a book\n(2)View database of books\n(3)Search a book\n(4)Issue a Book\n(6)Exit" << endl;
	char c;

	do{
		cin >> c;
		cin.ignore();
		switch(c){
			case '1': AddBook();
			break;
			case '2': viewDatabase();
			break;
			case '3': searchBook();
         break;
         // case '4': issueBook();
			default:;
		};
	} while (c != '6');

	return 0;
}