#include "BMSLib.h"

//char* getTime()
//{
//	auto curTime = chrono::system_clock::now(); // gets he current time
//
//	time_t curTime_t = chrono::system_clock::to_time_t(curTime); // converts it to time_t format
//
//	static char curTimeStr[100];
//	
//	tm timeInfo;
//	localtime_s(&timeInfo, &curTime_t); // to change the time_t to tm format
//
//	// %I - 12hr fmt, %p - am/pm designation
//	strftime(curTimeStr, sizeof(curTimeStr), "%m-%d-%Y %I:%M:%S %p", &timeInfo);
//	
//	return curTimeStr;
//}

/*
	A function to list all the available commands for navigating and making use of the
	bank system. Make sure you add the command along with its function after you implement it!
*/
void listCommands(int mode)
{
	if (mode != 0) {
		cout << "\nCommand	      \tFunction";
		cout << "\n-------        \t--------";
		cout << "\nerase       \tErases all records of users\n";
		cout << "\nlist          \tLists all of users' information\n";
		cout << "\nsort         \tSorts the users by name\n";
		cout << "\nexit           \tExits the Program.\n";

		cout << "\n\nPress [Enter] key to go to the command terminal...";
	}
	else {
		cout << "\nCommand	      \tFunction";
		cout << "\n-------        \t--------";
		cout << "\nregister       \tCreates new account.\n";
		cout << "\nlogin          \tLogin to your account.\n";
		cout << "\ndelete         \tTo delete your account.\n";
		cout << "\nexit           \tExits the Program.\n";

		cout << "\n\nPress [Enter] key to go to the command terminal...";
	}
}


/*
	A helper function that clears the console buffer so that the next coming input doesn't
	trace back to the previous and intermingle data.
*/
void clearConsoleBuffer()
{
	cin.clear();
	cin.ignore(INT_MAX, '\n');
}

/*
	A helper function that identifies a string as either digit or non-digit
*/
bool isDigit(string& s)
{
	for (int i = 0; i < s.size(); i++) {
		if (s[i] - '0' < 0 || s[i] - '0' > 9) return false;
	}
	return true;
}

void success(string s) {
	
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 10);//blue
	cout << s << endl; 
	SetConsoleTextAttribute(h, 7);
}
void warning(string w) {

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 14);//blue
	cout << w << endl;
	SetConsoleTextAttribute(h, 7);
}
void error(string e) {

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 12);//blue
	cout << e << endl;
	SetConsoleTextAttribute(h, 7);
}
