#include "BMSLib.h"


void registerAccount()
{
	AccountHolder user;

	ofstream ofs(accountsFile, ios::out|ios::app|ios::binary);

	clrscr();

	cout << "\n\nWelcome to our Bank, we're glad you are here. Fill out the information below to get started.\n";
	
	int id = getId() + 1;  // assign a new id to current applicant
	user.idNumber = id;

	cout << "(+) Username: ";
	getline(cin, user.name);
	clearConsoleBuffer();
	cout << "(+) E-Mail: ";
	getline(cin, user.email);
	clearConsoleBuffer();
	cout << "(+) Password: ";
	getline(cin, user.accountPassword);
	clearConsoleBuffer();
	cout << "(+) Address: ";
	getline(cin, user.address);
	clearConsoleBuffer();
	cout << "(+) Phonenumber: ";
	getline(cin, user.phoneNumber);
	clearConsoleBuffer();
	cout << "(+) Gender: ";
	getline(cin, user.gender);
	clearConsoleBuffer();
	cout << "(+) Nationality: ";
	getline(cin, user.nationality);
	clearConsoleBuffer();
	cout << "(+) Age: ";
	cin >> user.age;
	clearConsoleBuffer();
	cout << "(+) Birthday (mm.dd.yy) separated by \".\": ";
	getline(cin, user.birthdate);

	if (user.birthdate.empty()) {
		warning("\nCan't be empty! Press [Enter] key ...");
		cin.get();
		return;
	}

	int cnt = 0;
	for (int i = 0; i < user.birthdate.size(); i++) {
		if (user.birthdate[i] == '.') cnt++;
	}

	if (cnt != 2) {
		error("\nInvalid format. Correct format is: mm.dd.yy , press [Enter] key ...\n");
		cin.get();
		return;
	}


	user.balance = 100;
	user.accountStatus = "Active";
	user.accountType = "Savings";

	ofs.write((char*)&user, sizeof(user));
	ofs.close();

	success("Your account was successfully created! Thanks for choosing our bank.\n");


	cin.get();
}

void login()
{
	
	clrscr();
	string email, password;


	GBACK:cout << "\nLogin to your account.\n";
	cout << "\nEnter E-Mail: ";
	getline(cin,email);
	clearConsoleBuffer();
	cout << "\nEnter Password: ";
	getline(cin, password);
	clearConsoleBuffer();

	if (email.empty() || password.empty())
	{
		warning( "\n\nEmail or Password is empty. Press [Enter] key ...");

		goto GBACK;
	}
	ifstream ifs(accountsFile, ios::binary);

	AccountHolder user2;
	while (ifs.read((char*)&user2, sizeof(user2)))
	{
		if (user2.email == email && user2.accountPassword == password)
		{
			dashBoard(user2);
			return;
		}
	}

	error("\nIncorrect Username or Password. Please try again...\n");
	ifs.clear();
	ifs.close();
	cin.get();
	clearConsoleBuffer();
	main();
}

void transfer(AccountHolder user)
{
	cout << "\nEnter reciever's information:";
	cout << "\n-----------------------------";

	string email1, email2;
	double balance;
	cout << "\nReceivers e-mail: ";
	getline(cin, email1);
	clearConsoleBuffer();
	cout << "\nConfirm Receivers e-mail: ";
	getline(cin, email2);
	clearConsoleBuffer();

	if (email1 != email2) {
		cout << "\nThe e-mail's don't match. Press [Enter] key ...";
		cin.get();
		dashBoard(user);
	}

	cout << "\nBalance: ";
	cin >> balance;
	clearConsoleBuffer();

	if (balance > user.balance) {
		cout << "\nYou don't have such credits. Please try again! Press [Enter] key ...";
		cin.get();
		dashBoard(user);
	}

	fstream file(accountsFile, ios::in | ios::out | ios::binary);

	AccountHolder receiver;
	while (file.read((char*)&receiver, sizeof(receiver))) {
		if (receiver.email == email1) {
			receiver.balance += balance;
			
			int pos = file.tellg(); // keeping the current position of the reader

			file.seekg(0, ios::beg);      // reseting the reader to pos(0) to start looking for the sender

			// Editing the information of the sender
			AccountHolder tuser;
			while (file.read((char*)&tuser, sizeof(tuser))) {
				if (tuser.email == user.email) {    // if the sender is found
					user.balance -= balance;        // subtract his balance
					file.seekp(file.tellg() - (streampos)sizeof(tuser), ios::beg);
					file.write((char*)&user, sizeof(user));  
					break;
				}
			}

			// change the position of the writer(putter) back to the recievers position
			file.seekp(pos - (streampos)sizeof(receiver), ios::beg);
			file.write((char*)&receiver, sizeof(receiver));
			file.close();

			clearConsoleBuffer();
			success("\nA credit of $" + to_string(balance) + " successfully sent to " + email1 );
			cout << "Press [Enter] ...";
			cin.get();
			return;
		}
	}
	
	file.clear();
	file.close();
	error("The receiver account couldn't be found, please try again. Press [Enter] key ...");
	cin.get();
	main();
}

void withdraw(AccountHolder user)
{
	cout << "Withdraw Money\n-----------------\n";
	cout << "Enter cash amount: ";
	double cash;
	cin >> cash;
	
	if (user.balance - cash < 0) {
		clearConsoleBuffer();
		error("\nSorry, not enough balance! Press [Enter] key ...");
		cin.get();
		return;
	}

	cout << "Enter password: ";
	string password;
	clearConsoleBuffer();
	getline(cin, password);

	if (password.empty() || user.accountPassword != password) {
		error("\nInvalid Password. Press [Enter] key ...");
		cin.get();
		return;
	}

	AccountHolder tuser;

	fstream file(accountsFile, ios::in | ios::out | ios::binary);

	while (file.read((char*)&tuser, sizeof(tuser)))
	{
		if (tuser.email == user.email && tuser.accountPassword == password) {
			tuser.balance -= cash;
			file.seekp(file.tellg() - (streampos)sizeof(tuser), ios::beg);
			file.write((char*)&tuser, sizeof(tuser));
			file.close();
			success("\n\nWithdraw successfull! Press [Enter] key ...");
			cin.get();
			return;
		}
	}
	error("\nOops! An error has occured, please try again. Press [Enter] key ...");
}

void deleteAccount()
{
	cout << "\nDelete Account\n------------\n";
	char choice;
	warning("\nWarning! You are about to delete your account from our system, this will result in permanent removal and you won't be able to make use of our services.\n");
	cout << "Are you sure? [Y/n] : ";
	cin >> choice;
	if(choice != 'y' && choice != 'Y') {
		cout << choice << endl;
		error("\n\nAccount deletion unsuccessful. Press [Enter] key ...");
		clearConsoleBuffer();
		cin.get();
		main();
	}

	string email;
	string password1, password2;

	clearConsoleBuffer();
	cout << "\n\nEnter your e-mail: ";
	getline(cin, email);
	clearConsoleBuffer();
	cout << "\nEnter your password: ";
	getline(cin, password1);
	clearConsoleBuffer();
	cout << "\nConfirm your password: ";
	getline(cin, password2);

	if (password1 != password2) {
		error("\nPasswords don't match. Press [Enter] key ...");
		cin.get();
		return;
	}

	AccountHolder user;

	fstream file1(accountsFile, ios::in | ios::binary);
	fstream file2("temp.bms", ios::out | ios::trunc | ios::binary);
	bool found = 0;
	
	while (file1.read((char*)&user, sizeof(user)))
	{
		if (user.email == email && user.accountPassword == password1)
		{
			found = 1;
			continue;
		}
		file2.write((char*)&user, sizeof(user));
	}

	file1.close();
	file2.close();

	if (!found) {
		error("\nEmail or password not correct, please try again. Press [Enter] key ...");
		cin.get();
		return;
	}

	file1.open(accountsFile, ios::out |ios::trunc);
	file2.open("temp.bms", ios::in);
	while (file2.read((char*)&user, sizeof(user)))
	{		
		file1.write((char*)&user, sizeof(user));
	}
	file1.close();
	file2.close();
	success("\n\nAccount successfully deleted. We're sad to see you leave. Press [Enter] key ...");
	cin.get();
	main();
}
//deposite
void Deposite(AccountHolder user)
{
	cout << "Deposite Money\n-----------------\n";
	cout << "Enter cash amount: ";
	double cash;
	cin >> cash;


	cout << "Enter password: ";
	string password;
	clearConsoleBuffer();
	getline(cin, password);

	if (password.empty() || user.accountPassword != password) {
		error("\nInvalid Password. Press [Enter] key ...");
		cin.get();
		return;
	}

	AccountHolder tuser;

	fstream file(accountsFile, ios::in | ios::out | ios::binary);

	while (file.read((char*)&tuser, sizeof(tuser)))
	{
		if (tuser.email == user.email && tuser.accountPassword == password) {
			tuser.balance += cash;
			file.seekp(file.tellg() - (streampos)sizeof(tuser), ios::beg);
			file.write((char*)&tuser, sizeof(tuser));
			file.close();
			success("\n\nDeposite successfull! Press [Enter] key ...");
			cin.get();
			main();
		}
	}
	error("\nOops! An error has occured, please try again. Press [Enter] key ...");
	main();
}

void modifyAccount(AccountHolder user)
{
	cout << "\nModify your account\n---------------------\n";
	cout << "Choose what to edit:\n";
	cout << "        L (1) Username\n";
	cout << "        L (2) Password\n";
	cout << "        L (3) Address\n";
	cout << "        L (4) Nationality\n";
	cout << "        L (5) Email\n";
	cout << "        L (6) Birthdate\n";
	cout << "        L (7) Gender\n";
	cout << "        L (8) AccountType\n";
	cout << ":";
	int choice;
	cin >> choice;

	clearConsoleBuffer();
	if (choice == 1) {
		cout << "\nEnter new username: ";
		getline(cin, user.name);
		if (user.name.empty()) {
			cout << "\nCan't be empty! Press [Enter] key ...";
			cin.get();
			return;
		}
	}
	else if (choice == 2) {		
		cout << "\nEnter new password: ";
		getline(cin, user.accountPassword);
		if (user.accountPassword.empty()) {
			cout << "\nCan't be empty! Press [Enter] key ...";
			cin.get();
			return;
		}
	}
	else if (choice == 3) {
		cout << "\nEnter new address: ";
		getline(cin, user.address);
		if (user.address.empty()) {
			cout << "\nCan't be empty! Press [Enter] key ...";
			cin.get();
			return;
		}
	}
	else if (choice == 4) {
		cout << "\nEnter new nationality: ";
		getline(cin, user.nationality);
		if (user.nationality.empty()) {
			cout << "\nCan't be empty! Press [Enter] key ...";
			cin.get();
			return;
		}
	}
	else if (choice == 5) {
		cout << "\nEnter new e-mail: ";
		getline(cin, user.email);
		if (user.email.empty()) {
			cout << "\nCan't be empty! Press [Enter] key ...";
			cin.get();
			return;
		}
	}
	else if (choice == 6) {
		cout << "\nEnter new birth day (mm.dd.yy) separated by \".\": ";
		getline(cin, user.birthdate);
		if (user.birthdate.empty()) {
			cout << "\nCan't be empty! Press [Enter] key ...";
			cin.get();
			return;
		}

		int cnt = 0;
		for (int i = 0; i < user.birthdate.size(); i++) {
			if (user.birthdate[i] == '.') cnt++;
		}

		if (cnt != 2) {
			cout << "\nInvalid format. Correct format is: mm.dd.yy , press [Enter] key ...\n";
			cin.get();
			return;
		}
	}
	else if (choice == 7) {
		cout << "\nEnter new gender: ";
		getline(cin, user.gender);
		if (user.gender.empty()) {
			cout << "\nCan't be empty! Press [Enter] key ...";
			cin.get();
			return;
		}
	}
	else if (choice == 8) {
		cout << "\nEnter new account type: ";
		getline(cin, user.accountType);
		if (user.accountType.empty()) {
			cout << "\nCan't be empty! Press [Enter] key ...";
			cin.get();
			return;
		}
	}
	else {
		cout << "\nInvalid choice. Press [Enter] key ...";
		cin.get();
		return;
	}



	fstream file(accountsFile, ios::in | ios::out | ios::binary);
	AccountHolder tuser;

	while (file.good() && file.read((char*)&tuser, sizeof(tuser))) {
		if (tuser.idNumber == user.idNumber) {
			file.seekp(file.tellg() - (streampos)sizeof(tuser), ios::beg);
			file.write((char*)&user, sizeof(user));
			file.close();

			cout << "\n\nAccount successfully updated! Press [Enter] key ...";
			
			break;
			
		}
		
	}
	clearConsoleBuffer();
	main();
	
}

//void sortUsers()
//{
//	fstream file(accountsFile, ios::in | ios::out | ios::binary);
//
//	file.seekg(0, ios::end);
//	int fileSize = file.tellg();
//
//	int tmp = (fileSize / sizeof(AccountHolder));
//}

void dashBoard(AccountHolder user)
{
	GETHERE:clrscr();

	cout << " Welcome " << user.name;
	cout << "\n\n Account Information :";

	ifstream file(accountsFile, ios::in | ios::binary);
	AccountHolder tuser;
	// Get latest information from file for dashboard view
	while (file.read((char*)&tuser, sizeof(tuser))) {
		if (tuser.email == user.email && tuser.accountPassword == user.accountPassword) {
			user = tuser;
			file.close();
			break;
		}
	}

	printUser(user);

	string input;
	cout << "\n~/";
	getline(cin, input);
	clearConsoleBuffer();


	if (input == "transfer") {
		transfer(user);
		dashBoard(user);
	}
	else if (input == "withdraw") {
		withdraw(user);
		dashBoard(user);
	}
	else if (input == "deposite") {
		Deposite(user);
		dashBoard(user);
	}
	else if (input == "modify") {
		modifyAccount(user);
		dashBoard(user);
	}
	else if (input == "pay")
	{
		billPayment(user);
		dashBoard(user);
	}
	else if (input == "help" || input == "-h") {
		cout << "\nCommand     \tFunction";
		cout << "\n---------   \t--------";
		cout << "\ntransfer    \tSend a balance to another account-holder.\n";
		cout << "\nwithdraw    \tTake your money in-cash.\n";
		cout << "\ndeposite    \tDeposite your money into your bank account.\n";
		cout << "\nmodify	   \tChange account information.\n";
		cout << "\npay         \tPay your bills.\n";
		cout << "\nhome        \tGo back to the homepage.\n";
		cout << "\nPress [Enter] key to continue...\n";
		cin.get();
		dashBoard(user);
	}
	else if (input == "home") {
		main();
	}
	else {
		cerr << "Invalid! Read the manual using \"help\" or \"-h\"...";
		cin.get();
		dashBoard(user);
	}
}


void printUser(AccountHolder user) {
	cout << "\n ----------------------\t------------------";
	cout << "\n 1. Id:                \t#" << user.idNumber;
	cout << "\n ----------------------\t------------------";
	cout << "\n 2. Username:          \t" << user.name;
	cout << "\n ----------------------\t------------------";
	cout << "\n 3. Password:          \t" << user.accountPassword;
	cout << "\n ----------------------\t------------------";
	cout << "\n 4. Balance:           \t$" << fixed << setprecision(2) << user.balance;
	cout << "\n ----------------------\t------------------";
	cout << "\n 5. Address:           \t" << user.address;
	cout << "\n ----------------------\t------------------";
	cout << "\n 6. E-mail:            \t" << user.email;
	cout << "\n ----------------------\t------------------";
	cout << "\n 7. Gender:            \t" << user.gender;
	cout << "\n ----------------------\t------------------";
	cout << "\n 8. Birthdate:         \t" << user.birthdate;
	cout << "\n ----------------------\t------------------";
	cout << "\n 9. Date-Created:      \t" << user.dateCreated;
	cout << "\n ----------------------\t------------------";
	cout << "\n10. Last-Transaction:  \t" << user.lastTransaction;
	cout << "\n ----------------------\t------------------";
	cout << "\n11. Account-Status:    \t" << user.accountStatus;
	cout << "\n ----------------------\t------------------";
	cout << "\n12. Account-Type:      \t" << user.accountType;
	cout << "\n ----------------------\t------------------\n";
}


int getId()
{
	ifstream ifs(accountsFile, ios::binary);
	AccountHolder user;
	int lastId;
	if (!ifs) {
		cout << " an error occured while opening the file!\n";
		return 0;
	}
	else {
		ifs.seekg(0, ios::end);
		lastId = (ifs.tellg() / sizeof(user));
		ifs.close();

		return lastId;
	}
}
