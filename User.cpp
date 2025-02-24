#include "User.h"

User::User(string login, string pass, string firstName, string lastName, string patronymic, string adress, string phone)
{
	data["login"] = login;
	data["pass"] = pass;
	data["firstName"] = firstName;
	data["lastName"] = lastName;
	data["patronymic"] = patronymic;
	data["adress"] = adress;
	data["phone"] = phone;
	this->id++;
	if (id == 1) {
		this->isAdmin = true;
	}
}

void User::showData()
{
	for (auto pair : data) {
		cout << pair.first << ": " << pair.second << endl;
	}
}

int User::getId()
{
	return this->id;
}

bool User::getIsAdmin()
{
	return this->isAdmin;
}

User::~User()
{
}
