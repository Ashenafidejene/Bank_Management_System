/*
	This file is used to call the functions specified by the users input.
*/

#include "BMSLib.h"
int mode = 0;
int main()
{
	


	if (mode == 0)
	{

		clrscr();
		srand(time(0));
		//int mode = 0;

		cout << "\nLogin as: ";
		cout << "\n(1) Administrator";
		cout << "\n(any number) A user\n ";
		cin >> mode;
		cin.ignore();
	}


	ADMIN: if (mode == 1) {
		string input;
		cout << "\n admin~/";
		getline(cin, input);
		cin.ignore();

		if (input == "list")
		{
			listAllAccounts();
			goto ADMIN;
		}
		else if (input == "erase") {
			deleteAllAccounts();
			goto ADMIN;
		}
		else if (input == "help" || input == "-h") {
			listCommands(1);
			goto ADMIN;
		}
		else if (input == "sort") {
			sortUsers();
			goto ADMIN;
		}
		else if (input == "exit") {
			exit(0);
		}
		else if (input == "clear") {
			clearConsoleBuffer();
			goto ADMIN;
		}
		
		//else if (input == "sort") {
		//	//sortUsers();
		//}
		
		else {
			error("Invalid command. Please refer to the manual by selecting help or -h.\n");
		}
	}
	else {
		string input;
	USER:cout << "\n\n\nuser~/";
		getline(cin, input);
		cin.ignore();

		if (input == "register")
		{
			registerAccount();
			goto USER;

		}
		else if (input == "login") {
			login();
			goto USER;
		}
		else if (input == "help" || input == "-h") {
			listCommands(0);
			goto USER;
		}
		else if (input == "exit") {
			exit(0);
		}
		else if (input == "delete") {
			deleteAccount();
			goto USER;
		}
		//else if (input == "sort") {
		//	//sortUsers();
		//}
		else if (input == "*del") { // for debug purposes only
			deleteAllAccounts();
		}
		else if (input == "users") {
			listAllAccounts();
		}
		else {
			error("Invalid command. Please refer to the manual by selecting help or -h.\n");
		}

	}

	clearConsoleBuffer();
	main();
}

