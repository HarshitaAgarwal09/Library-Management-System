#ifndef CLASS
#define CLASS
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
using namespace std;

#define BOOK_LIMIT 3

class Book{
private:
	char Title[50];
	char author[50];
	int price;
	int NoOfCopies;
	int NoOfLeftCps;

public:
	Book(char bname[], char auth[], int bp, int nob, int nolb){
		strcpy(Title, bname);
		strcpy(author, auth);
		NoOfCopies = nob;
		NoOfLeftCps = nolb;
		price = bp;
	}

	Book(){}
	void name(char name[]){
		strcpy(name, Title);
	}

	void addCopies(int a)
	{
		NoOfCopies += a;
		NoOfLeftCps += a;
	}

	int copies(){
		return NoOfCopies;
	}

	void Return(){
		NoOfLeftCps++;
	}

	void mergeBooks(int cps, int left)
	{
		NoOfCopies += cps;
		NoOfLeftCps += left;
	}

	int left(){
		return NoOfLeftCps;
	}

	bool ifLeft()
	{
		return NoOfLeftCps;
	}

	void printDetails() {
		cout << "Name of the Book: " << Title << endl;
		cout << "Author of the Book: " << author << endl;	
		cout << "Price of the Book: " << price << endl;
		cout << "Total number of copies of Book: " << NoOfCopies << endl;
		cout << "Number of copies available: " << NoOfLeftCps << endl;
		cout << endl;
	}

	void printDetails(int x) {
		cout << "Author of the Book: " << author << endl;	
		cout << "Price of the Book: " << price << endl;
		cout << "Total number of copies of Book: " << NoOfCopies << endl;
		cout << "Number of copies available: " << NoOfLeftCps << endl;
		cout << endl;
	}

	void dcr(){
		--NoOfLeftCps;
	}
};

bool isLeapYr(int yr)
{
	if(yr % 4) return false;
	if(yr % 100) return true;
	if(yr % 400) return false;
	return true;
}

int daysInMnth(int mnth, int yr)
{
	int days;
	switch(mnth)
	{
		case 1: days = 31;
		break;
		case 2: days = (isLeapYr(yr))? 28 : 29;
		break;
		case 3: days = 31;
		break;
		case 4: days = 30;
		break;
		case 5: days = 31;
		break;
		case 6: days = 30;
		break;
		case 7: days = 31;
		break;
		case 8: days = 31;
		break;
		case 9: days = 30;
		break;
		case 10: days = 31;
		break;
		case 11: days = 30;
		break;
		case 12: days = 31; 
	}
	return days;
}

int daysInBtw(long int dateP, long int dateI)
{
	int days = 0;
	int prsntYr = dateP % 10000;
	int prsntMnth = (dateP / 10000) % 100;
	int prsntDay = dateP / 1000000;
	int issueYr = dateI % 10000;
	int issueMnth = (dateI / 10000) % 100;
	int issueDay = dateI / 1000000;
	
	for(int yr = issueYr + 1; yr < prsntYr; yr++)
	{
		if(isLeapYr(yr)) days += 366;
		else days += 365; 
	}
	
	int uprLimit = (issueYr == prsntYr)?(prsntMnth - 1): 12;
	for(int mnth = issueMnth + 1; mnth <= uprLimit; mnth++) days += daysInMnth(mnth, issueYr);
	
	int lwrLimit = (issueYr == prsntYr)? prsntMnth :1;
	for(int mnth = lwrLimit; mnth < prsntMnth; mnth ++) days += daysInMnth(mnth, prsntYr);	

	days += (issueMnth == prsntMnth)?(prsntDay - issueDay): daysInMnth(issueMnth, issueYr) - issueDay + prsntDay;
	return days;	
}

void dateNtime(long int* date, int* Time)
{
	time_t t = time(0);
	tm* now = localtime(&t);
	char buf[20];
	strftime(buf, 20, "%Y-%m-%d.%X", now);
	buf;
	*Time = 100 * now ->tm_hour + now -> tm_min;
	*date = 1000000 * now ->tm_mday + 10000 * (now ->tm_mon + 1) + 1900 + now ->tm_year;
}

struct IshDetails
{
	long int date = -1;
	int time = -1;
	char Title[50] = "\0";	

	IshDetails(char bname[], long int day, int t)
	{
		strcpy(Title, bname);
		date = day;
		time = t;
	};

	IshDetails(){}
};

class Student
{
private:
	long long int rollNo;
	int booksIssued;
	struct IshDetails details[BOOK_LIMIT];
public:
	Student(long long int rn)
	{
		rollNo = rn;
		booksIssued = 0;
		struct IshDetails s;
		details[0] = s;
	}

	Student(){}

	long long int RollNo()
	{
		return rollNo;
	}

	int totlIssued(){
		return booksIssued;
	}

	int updateFine()
	{
		int Fine = 0;
		long int date;
		int Time;
		dateNtime(&date, &Time);
		
		for(int i = 0; i < booksIssued; i++)
		{
			int days = daysInBtw(date, details[i].date);
			
			if(days <= 15)continue;
			else days -= 15;
			
			Fine += min(7, days);
			
			if (days > 7) {
				Fine += 10 * (days - 7);
			}
		}
		
		return Fine;		
	}

	void Return(char bname[50]){
		for(int i = 0, j = 0; i < booksIssued; i++, j++)
		{
			if (!strcmp(details[i].Title, bname)) ++ i;
			if(i == booksIssued) break;
			
			details[j] = details[i];
		}

		-- booksIssued;
	}

	bool ifIssued(char bname[]){
		
		for(int i = 0; i < booksIssued; i++)
		{
			if(strcmp(details[i].Title, bname) == 0) return true;
		}

		return false;
	}



	void addDetails(struct IshDetails* s)
	{
		details[booksIssued] = *s;
		++booksIssued;
	}

	void printDetails()
	{
		int fine = updateFine();
		cout << "Student Roll number: " << rollNo <<endl;
		cout << "Fine on Student: " <<fine << endl;
		cout << "Book issued on Student: " << booksIssued << endl;
		for (int i = 0; i < booksIssued; ++i)
		{
			cout << details[i].Title << '\t' << details[i].date / 1000000 << "-" << (details[i].date % 1000000) / 10000 << "-" << details[i].date % 10000;
			cout << '\t' << details[i].time / 100 << ":" << details[i].time % 100 << endl;

		}
	}

	void printDetails(int x)
	{
		int fine = updateFine();
		cout << "Fine on Student: " <<fine << endl;
		cout << "Book issued on Student: "<< booksIssued << endl;
		for (int i = 0; i < booksIssued; ++i)
		{
			cout << details[i].Title << '\t' << details[i].date / 1000000 << "-" << (details[i].date % 1000000) / 10000 << "-" << details[i].date % 10000;
			cout << '\t' << details[i].time / 100 << ":" << details[i].time % 100 << endl;

		}
	}

	int fineOn(char bname[50])
	{
		int i;
		
		for(i = 0; i < booksIssued; i++) if(strcmp(details[i].Title, bname) == 0) break;	
		
		long int date;
		int Time;
		dateNtime(&date, &Time);
		int days = daysInBtw(date, details[i].date);
		
		if (days <= 15) return 0;
		
		days -= 15;
		if(days <= 7) return days;
		else return 7 + (days - 7) * 10;
	}
};

#endif