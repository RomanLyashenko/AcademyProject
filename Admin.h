#pragma once
using namespace std;
#include <iostream>
#include "User.h"
#include <string>
#include <map>


class Admin : public User{

public:
	Admin(map<string, string> data, bool isAdmin, int id);
	~Admin();


};

