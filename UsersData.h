
// êëàññ, õðàíÿùèé îñíîâíþ èíôîðìàöèþ î ïîëüçîâàòåëå + ðåãèñòðàöèÿ
#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

class UsersData
{
private:
	string name;
	string lastName;
	string patronymic;
	string adress;
	string phone;
	string login;
	string password;
	string pathToUsersData = "Data.txt";
public:
	UsersData();
	void setName(string name);
	string getName();
	void setLastName(string lastName);
	string getLastName();
	void setPatronymic(string patronymic);
	string getPatronymic();
	void setAdress(string adrees);
	string getAdress();
	void setPhone(string phone);
	string getPhone();
	void setLogin(string login);
	string getLogin();
	void setPassword(string password);
	string getPassword();
	void setPathToUsersData(string pathToUsersData);
	string getPathToUsersData();
	string normalizePhoneNumber(const string& phone);
	bool loginCheck(const string& login, string pathToUsersData);
	void registration(); // ôóíêöèÿ ðåãèñòðàöèè
	bool loginUser(); // ôóíêöèÿ àâòîðèçàöèè
	bool isPasswordFits(string password); // проверка пароля 
	void toCipherWord(string word, string key);
	bool containsSpaces(string str);
	bool containsColon(string str);
	~UsersData();
};

