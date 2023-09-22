#include "BMSLib.h"

void deleteAllAccounts()
{
	fstream file(accountsFile, ios::out | ios::trunc | ios::binary);
    if (file.is_open())
        file.close();
    else
        cerr << "error in opening the file\n";
}

void listAllAccounts()
{
	//sortUsers();
	ifstream file(accountsFile , ios::binary);
    if (file.is_open())
    {
        AccountHolder user;

        while (file.good() && file.read((char*)&user, sizeof(user))) {
            cout << "\n\n<#> " << user.name;
            printUser(user);
        }

        file.close();
        cin.get();
        main();
    }
    else
        cerr << "error in opening the file\n";
}
void sortUsers()
{
    int size = getId();
    fstream file1(accountsFile, ios::binary|ios::in|ios::out);
    AccountHolder users[10000];
    if (!file1) {
        error("the file1 doesn't exist");
        return;
    }
    int i = 0;
    while (file1.good() && file1.read((char*)&users[i], sizeof(users[i]))) {
        i++;
    }

    file1.clear();
    // sort algorithm[bubble sort]
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if ((users[j]).name > (users[j + 1]).name)
            {
                AccountHolder temp = users[j];
                users[j] = users[j + 1];
                users[j + 1] = temp;

            }
        }
    }

    
    for (int i = 0; i < size; i++) {
        file1.write((char*)&users[i], sizeof(users[i]));
    }
    file1.close();
    cin.get();


}