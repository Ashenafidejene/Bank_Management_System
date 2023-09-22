//#include <iostream>
//#include <fstream>
//
//using namespace std;
//
//int main()
//{
//	/*fstream file("test.txt", ios::out | ios::binary);
//
//	char str1[50] = "1@12";
//	cout << str1 << endl;
//	file.write(str1, strlen(str1) + 1);
//
//	file.close();
//
//	file.open("test.txt", ios::in | ios::binary);
//
//	char str2[50];
//
//	file.seekg(0, ios::beg);
//	file.read(str2, strlen(str1) + 1);
//
//	cout << str2 << endl;
//
//	file.close();
//
//	return 0;*/
//
//
//	fstream file("test.txt", ios::out | ios::binary);
//
//	string str1 = "1@12";
//	cout << str1 << endl;
//	file.write((char*)&str1, str1.size());
//
//	file.close();
//
//	file.open("test.txt", ios::in | ios::binary);
//
//	string str2;
//
//	file.seekg(0, ios::beg);
//	file.read((char*)&str2, str1.size());
//
//	cout << str2 << endl;
//
//	file.close();
//
//	return 0;
//}