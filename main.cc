#include <iostream>
#include <fstream>
#include <cstring>
#include <D:\Git\Library-Management-System\functions.h>
#include <D:\Git\Library-Management-System\class.h>

using namespace std;

int main(int argc, char const *argv[]) {																	
	int c;	
	do{
		if(argc == 1)cout << "(1)Add a book\n(2)Search a book\n(3)Search a student\n(4)View database of Book\n(5)View database of students\n";
		if(argc == 1)cout << "(6)Upload Books\n(7)Upload students\n(8)Issue a book\n(9)Return a book\n(10)Exit" << endl;
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
			case 1: AddBook();
			break;	
			case 2: searchBook();
			break;
			case 3: searchStudent();
			break;
			case 4: viewBooks();
         	break;
         	case 5: viewStudents();
  	       	break;
         	case 6: uploadBooks();
         	break;
         	case 7: uploadStudents();
         	break;
			case 8: issueBook();
			break;
			case 9: returnBook();
			break;
			default: return 0;
		}

		if(argc == 1){
			fflush(stdin);
			char x[2];
			cin.getline(x, 2);
			system("CLS");
		}

	} while (argc == 1);

	return 0;
}