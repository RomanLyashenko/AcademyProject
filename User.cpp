#include "User.h"

User::User(map<string, string> data)
{
	this->id++;
	this->data = data;
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

void User::changeData(map<string, string> data)
{
	for (auto pairs : this->data) {
		this->data[pairs.first] = data[pairs.first];
	}
}

User::~User()
{
}
