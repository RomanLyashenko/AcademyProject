#pragma once
using namespace std;
#include <string>
#include <vector>
#include "UsersData.h"
#include <fstream>
#include "Test.h"

class Admin : public UsersData
{
public:
	Admin();
	void createNewUser();
	void deleteUser();
	bool isTestNameTaken(const string& testName);
	void createTest();
	~Admin();
};

