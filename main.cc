#include <iostream>
#include <fstream>
#include <cstring>
#include <D:\Git\Library-Management-System\functions.h>
#include <D:\Git\Library-Management-System\class.h>

using namespace std;

int main(int argc, char const *argv[]) {																	
	char c;	
	do{
		if(argc == 1)cout << "(1)Add a book\n(2)Search a book\n(3)Search a student\n(4)View database of Book\n(5)View database of students\n";
		if(argc == 1)cout << "(6)Upload Books\n(7)Upload students\n(8)Issue a book\n(9)Exit" << endl;
		cin >> c;
		cin.ignore();
		
		if (argc != 1) {
			int Time;
			long int date;
			dateNtime(&date, &Time);
			cout << date / 1000000 << "-" << (date % 1000000) / 10000 << "-" << date % 10000 << "\t";
			cout << Time / 100 << ":" << Time % 100 << endl;
		}

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
			break;
			case '9': return 0;
		}

		if(argc == 1){
			fflush(stdin);
			char x[1];
			cin.getline(x, 1);
			system("CLS");
		}

	} while (c != '9' and argc == 1);

	return 0;
}