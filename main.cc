#include<iostream>
#include<fstream>
#include<cstring>
#include <D:\Git\Library-Management-System\functions.h>
#include <D:\Git\Library-Management-System\class.h>

using namespace std;

int main() {																	
	cout << "(1)Add a book\n(2)Search a book\n(3)View database of Book\n(4)View database of students\n";
	cout << "(5)Upload Book\n(6)Upload students\n(7)Exit" << endl;
	char c;

	do{	
		cin >> c;
		cin.ignore();
		switch(c){
			case '1': AddBook();
			break;	
			case '2': searchBook();
			break;
			case '3': viewBook();
         	break;
         	case '4': viewStudents();
  	       	break;
         	case '5': uploadBook();
         	break;
         	case '6': uploadStdnts();
         	break;
			default:;
		};
	} while (c != '7');

	return 0;
}