#include <iostream>
#include <fstream>
#include <cstring>
#include <D:\Git\Library-Management-System\functions.h>
#include <D:\Git\Library-Management-System\class.h>

using namespace std;

int main() {																	
	cout << "(1)Add a book\n(2)Search a book\n(3)Search a student\n(4)View database of Book\n(5)View database of students\n";
	cout << "(6)Upload Book\n(7)Upload students\n(8)Issue a book\n(9)Exit" << endl;
	char c;

	do{	
		cin >> c;
		cin.ignore();
		switch(c){
			case '1': AddBook();
			break;	
			case '2': searchBook();
			break;
			case '3': searchStudent();
			break;
			case '4': viewBooks();
         	break;
         	case '5': viewStudents();
  	       	break;
         	case '6': uploadBook();
         	break;
         	case '7': uploadStdnts();
         	break;
			case '8': issueBook();
			default:;
		};
	} while (c != '9');

	return 0;
}