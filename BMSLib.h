#pragma once

/*
	This is a library for our "Bank Management System". It will serve as a 
	place to store all our function declarations and library inclusions.

	In line with this, there is a separately defined file "BMSLib.cpp" 
	which uses this "BMSLib.h" file and implements the functions declared HERE.
	
	You can see that all our programs #include "BMSLib.h" and no other header,
	this will keep our code clean and maintain functionality across different files.
*/
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <random>
#include <ctime>
#include <cmath>
#include <windows.h>



using namespace std;

#define clrscr() system("cls")	

const string accountsFile = "accounts.bms";
const string orgsFile = "organizations.bms";

struct AccountHolder
{
	string name = "";
	string gender = "";
	unsigned int age = 0;
	string birthdate = "";

	double balance = 0.0;
	string dateCreated = "";
	string lastTransaction = "";

	string address = "";
	string phoneNumber = "";
	string accountPassword = "";

	double loanAmount = 0.0;
	double interestRate = 0.0;

	int idNumber = 0;
	string email = "";
	string accountType = "";
	string nationality = "";
	string accountStatus = "";
};

struct Organization
{
	int id = 0;
	string name = "";
	string email = "";
	string address = "";
	double balance = 0.0;
};

// Main Functions

int main();


// For Acc Holders only

void registerAccount();

void login();

void transfer(AccountHolder);

void deleteAccount();

void withdraw(AccountHolder);

void Deposite(AccountHolder);

void modifyAccount(AccountHolder);

void dashBoard(AccountHolder);

void sortUsers();

void listCommands(int);

int getId();


// Organizations

void billPayment(AccountHolder);


// For Staff Only

void deleteAllAccounts();

void listAllAccounts();

void printUser(AccountHolder user);



// Helper functions

void clearConsoleBuffer();

bool search(string, string);

bool isDigit(string&);


//status indicator functions
void success(string s);
void error(string e);
void warning(string w);



//char* getTime();



