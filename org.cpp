#include "BMSLib.h"

using namespace::std;

void payElectricity(AccountHolder& user);
void payISP(AccountHolder& user);
void payWater(AccountHolder& user);

void billPayment(AccountHolder user)
{
	clrscr();

	cout << "\nWelcome to Bill Payment portal. Choose a service:";
	cout << "\n\t(1) Electricity (EELPA)";
	cout << "\n\t(2) Internet Service (ISP)";
	cout << "\n\t(3) Water Resources";

	cout << "\n:";

	int choice;
	cin >> choice;

	if (choice == 1) {
		payElectricity(user);
	}
	else if (choice == 2) {
		payISP(user);
	}
	else if (choice == 3) {
		payWater(user);
	}
}

void payElectricity(AccountHolder& user)
{
	clrscr();

	fstream file(accountsFile, ios::in | ios::out | ios::binary);
	Organization org;

	char choice;
	double amount = ((rand() + 25) % 25) * 3.1415;                  // assigning random value to be paid (For demonstration purposes)
	cout << "\nPay $" << amount << " electricity bills? [Y/n] : ";
	clearConsoleBuffer();
	cin >> choice;
	
	if (choice == 'y' || choice == 'Y') {
		file.seekg(0, ios::beg);

		if (amount > user.balance) {
			error("\nSorry, buy you don't have enough credits. Your balance is $" + to_string(user.balance));
			clearConsoleBuffer();
			cin.get();
			main();
			
		}

		AccountHolder tuser;
		while (file.read((char*)&tuser, sizeof(tuser)))
		{
			if (tuser.email == user.email && tuser.accountPassword == user.accountPassword) {
				user.balance -= amount;
				file.seekp(file.tellg() - (streampos)sizeof(user), ios::beg);
				file.write((char*)&user, sizeof(user));
				file.clear();
				file.close();

				fstream ofile(orgsFile, ios::in | ios::out | ios::binary);
				
				Organization org;
				while (ofile.read((char*)&org, sizeof(org)))
				{
					if (org.name == "EELPA") {
						org.balance += amount;
						ofile.seekp(ofile.tellg() - (streampos)sizeof(org), ios::beg);
						ofile.write((char*)&org, sizeof(org));
					}
				}

				success("\n\n$" +to_string(amount) +" successfully paid! Remaining balance is $" + to_string(user.balance) );
				cout << "Press [Enter] key ...";
				clearConsoleBuffer();
				cin.get();
				main();
			}
		}
	}
	error("\n\nCouldn't perform transaction. Please try again. Press [Enter] key ...");
	clearConsoleBuffer();
	cin.get();
	file.clear();
	file.close();
	main();
}

void payISP(AccountHolder& user)
{
	clrscr();

	fstream file(accountsFile, ios::in | ios::out | ios::binary);
	Organization org;

	char choice;
	double amount = ((rand() + 25) % 50) * 3.1415;                  // assigning random value to be paid (For demonstration purposes)
	cout << "\nPay $" << amount << " Telecom bills? [Y/n] : ";
	clearConsoleBuffer();
	cin >> choice;

	if (choice == 'y' || choice == 'Y') {
		file.seekg(0, ios::beg);

		if (amount > user.balance) {
			error("\nSorry, buy you don't have enough credits. Your balance is $" + to_string(user.balance));
			clearConsoleBuffer();
			cin.get();
			main();

		}

		AccountHolder tuser;
		while (file.read((char*)&tuser, sizeof(tuser)))
		{
			if (tuser.email == user.email && tuser.accountPassword == user.accountPassword) {
				user.balance -= amount;
				file.seekp(file.tellg() - (streampos)sizeof(user), ios::beg);
				file.write((char*)&user, sizeof(user));
				file.clear();
				file.close();

				fstream ofile(orgsFile, ios::in | ios::out | ios::binary);

				Organization org;
				while (ofile.read((char*)&org, sizeof(org)))
				{
					if (org.name == "ISP") {
						org.balance += amount;
						ofile.seekp(ofile.tellg() - (streampos)sizeof(org), ios::beg);
						ofile.write((char*)&org, sizeof(org));
					}
				}

				success("\n\n$" + to_string(amount) + " successfully paid! Remaining balance is $" + to_string(user.balance));
				cout << "Press [Enter] key ...";
				clearConsoleBuffer();
				cin.get();
				main();
			}
		}
	}
	error("\n\nCouldn't perform transaction. Please try again. Press [Enter] key ...");
	clearConsoleBuffer();
	cin.get();
	file.clear();
	file.close();
	main();
}

void payWater(AccountHolder& user)
{
	clrscr();

	fstream file(accountsFile, ios::in | ios::out | ios::binary);
	Organization org;

	char choice;
	double amount = ((rand() + 25) % 25) * 3.1415;                  // assigning random value to be paid (For demonstration purposes)
	cout << "\nPay $" << amount << " Water bills? [Y/n] : ";
	clearConsoleBuffer();
	cin >> choice;

	if (choice == 'y' || choice == 'Y') {
		file.seekg(0, ios::beg);

		if (amount > user.balance) {
			error("\nSorry, buy you don't have enough credits. Your balance is $" + to_string(user.balance));
			clearConsoleBuffer();
			cin.get();
			main();

		}

		AccountHolder tuser;
		while (file.read((char*)&tuser, sizeof(tuser)))
		{
			if (tuser.email == user.email && tuser.accountPassword == user.accountPassword) {
				user.balance -= amount;
				file.seekp(file.tellg() - (streampos)sizeof(user), ios::beg);
				file.write((char*)&user, sizeof(user));
				file.clear();
				file.close();

				fstream ofile(orgsFile, ios::in | ios::out | ios::binary);

				Organization org;
				while (ofile.read((char*)&org, sizeof(org)))
				{
					if (org.name == "AWSAA") {
						org.balance += amount;
						ofile.seekp(ofile.tellg() - (streampos)sizeof(org), ios::beg);
						ofile.write((char*)&org, sizeof(org));
					}
				}

				success("\n\n$" + to_string(amount) + " successfully paid! Remaining balance is $" + to_string(user.balance));
				cout << "Press [Enter] key ...";
				clearConsoleBuffer();
				cin.get();
				main();
			}
		}
	}
	error("\n\nCouldn't perform transaction. Please try again. Press [Enter] key ...");
	clearConsoleBuffer();
	cin.get();
	file.clear();
	file.close();
	main();
}