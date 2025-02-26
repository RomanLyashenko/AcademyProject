
// êëàññ, õðàíÿùèé îñíîâíþ èíôîðìàöèþ î ïîëüçîâàòåëå + ðåãèñòðàöèÿ
#include "UsersData.h"


UsersData::UsersData()
{
}

void UsersData::setName(string name)
{
	this->name = name;
}

string UsersData::getName()
{
	return this->name;
}

void UsersData::setLastName(string lastName)
{
	this->lastName = lastName;
}

string UsersData::getLastName()
{
	return this->lastName;
}

void UsersData::setPatronymic(string patronymic)
{
	this->patronymic = patronymic;
}

string UsersData::getPatronymic()
{
	return this->patronymic;
}

void UsersData::setAdress(string adrees)
{
	this->adress = adress;
}

string UsersData::getAdress()
{
	return this->adress;
}

void UsersData::setPhone(string phone)
{
	this->phone = phone;
}

string UsersData::getPhone()
{
	return this->phone;
}

void UsersData::setLogin(string login)
{
	this->login = login;
}

string UsersData::getLogin()
{
	return this->login;
}

void UsersData::setPassword(string password)
{
	this->password = password;
}

string UsersData::getPassword()
{
	return this->password;
}

void UsersData::setPathToUsersData(string pathToUsersData)
{
	this->pathToUsersData = pathToUsersData;
}

string UsersData::getPathToUsersData()
{
	return this->pathToUsersData;
}

string UsersData::normalizePhoneNumber(const string& phone) // ôóíêöèÿ èñïðàâëåíèÿ íîìåðà òåëåôîíà
{
	string result;

	// Ïðîáåãàåì ïî êàæäîìó ñèìâîëó â ñòðîêå
	for (char ch : phone) {
		if (isdigit(ch)) {
			result += ch;  // Äîáàâëÿåì òîëüêî öèôðû
		}
	}

	// Åñëè íîìåð íà÷èíàåòñÿ ñ "+7", çàìåíÿåì åãî íà "8"
	if (result.size() > 0 && result[0] == '7') {
		result[0] = '8';  // Çàìåíÿåì ïåðâóþ öèôðó íà 8
	}

	return result;
}

bool UsersData::loginCheck(const string& login, string pathToUsersData) // Ôóíêöèÿ äëÿ ïðîâåðêè, çàíÿò ëè ëîãèí
{
	string line = "";
	ifstream in;
	in.open(pathToUsersData);
	while (getline(in, line)) {  // ×èòàåì ôàéë ïîñòðî÷íî
		stringstream ss(line);  // Ñòðèì äëÿ ðàçäåëåíèÿ ñòðîêè
		string name, lastName, patronymic, userLogin, password, address, phone;

		// Ðàçäåëÿåì ñòðîêó ïî ñèìâîëó ':'
		if (getline(ss, name, ':') &&
			getline(ss, lastName, ':') &&
			getline(ss, patronymic, ':') &&
			getline(ss, userLogin, ':') &&
			getline(ss, password, ':') &&
			getline(ss, address, ':') &&
			getline(ss, phone)) {

			// Ñðàâíèâàåì ëîãèí ñ òåêóùèì çíà÷åíèåì â ñòðîêå
			if (userLogin == login) {
				in.close();  // Çàêðûâàåì ôàéë
				return true;   // Ëîãèí çàíÿò
			}
		}
	}

	in.close();  // Çàêðûâàåì ôàéë
	return false;  // Ëîãèí ñâîáîäåí
}



void UsersData::registration()
{
	string name, lastName, patronymic, address, phone, login, password;
	string pathToUsersData = "Data/Users.txt";
	cout << "\t\t** Registration **" << endl;

	// Input for name
	do {
		cout << "Enter your name: ";
		getline(cin, name);
	} while (containsColon(name));

	// Input for last name
	do {
		cout << "Enter your last name: ";
		getline(cin, lastName);
	} while (containsColon(lastName));

	// Input for patronymic
	do {
		cout << "Enter your patronymic: ";
		getline(cin, patronymic);
	} while (containsColon(patronymic));

	// Input for address
	do {
		cout << "Enter your address (spell together please): ";
		getline(cin, address);
	} while (containsSpaces(address) || containsColon(address));

	// Input for phone
	do {
		cout << "Enter your phone (spell together please): ";
		getline(cin, phone);
		phone = normalizePhoneNumber(phone); // Normalize phone number
	} while (containsSpaces(phone) || containsColon(phone) || isPhoneNumberValid(phone));


	// Input for login
	do {
		cout << "Enter your login: ";
		getline(cin, login);
		if (login.size() > 8) {
			cout << "Login is too long. Use another one." << endl;
		}
		if (loginCheck(login, pathToUsersData) == true) {
			cout << "Login is already used. Use another one." << endl;
		}
	} while (loginCheck(login, pathToUsersData) == true || login.size() > 8 || containsColon(login));

	// Input for password
	do {
		cout << "Enter your password: ";
		getline(cin, password);
	} while (isPasswordFits(password) || containsColon(password));

	// Open file for writing
	ofstream file(pathToUsersData, ios::app);
	if (!file.is_open()) {
		cout << "Unable to open file for writing.\n";
		return;
	}

	// Write user data to file
	file << name << ":" << lastName << ":" << patronymic << ":"
		<< login << ":" << password << ":" << address << ":" << phone << endl;

	file.close();
	cout << "Registration successful!" << endl;
}

// Function for user login
bool UsersData::loginUser()
{
	int attemptCount = 0;  // Number of failed attempts
	string pathToUsersData = "Data/Users.txt";
	string inputLogin, inputPassword;
	cout << "\t\t** Authorization **" << endl;

	// Enter login and password
	cout << "Enter your login: ";
	getline(cin, inputLogin);
	// Check if the login exists in the file
	if (!loginCheck(inputLogin, pathToUsersData)) {
		cout << "Login not found. Redirecting to registration..." << endl;
		registration();  // Redirect to registration
		return false;  // Login not found
	}
	// Loop for password attempts (up to 3 attempts)
	while (attemptCount < 3) {
		cout << "Enter your password: ";
		getline(cin, inputPassword);

		// Open file for reading
		ifstream in(pathToUsersData);
		if (!in.is_open()) {
			cout << "Unable to open file.\n";
			return false;
		}

		string line;
		bool loginFound = false;
		while (getline(in, line)) {  // Read file line by line
			stringstream ss(line);  // Stream for parsing the line
			string name, lastName, patronymic, userLogin, userPassword, address, phone;

			// Parse the line by delimiter ':'
			if (getline(ss, name, ':') &&
				getline(ss, lastName, ':') &&
				getline(ss, patronymic, ':') &&
				getline(ss, userLogin, ':') &&
				getline(ss, userPassword, ':') &&
				getline(ss, address, ':') &&
				getline(ss, phone)) {

				// Check login and password
				if (userLogin == inputLogin && userPassword == inputPassword) {
					in.close();  // Close file
					cout << "Authorization successful!" << endl;
					return true;  // Successful authorization
				}
			}
		}

		in.close();  // Close file
		cout << "Invalid login or password. Try again." << endl;
		attemptCount++;  // Increment attempt count

		if (attemptCount == 3) {
			cout << "You have entered wrong password 3 times." << endl;
			cout << "You will now be redirected to the registration page." << endl;
			return false;  // Redirect to registration
			registration();  // Redirect to registration
		}
	}
}

bool UsersData::isPasswordFits(string password)
{
	bool flagForNumber = false;
	bool flagForBigLetter = false;
	bool flagForSpecialSymbol = false;
	if (password.size() < 8 || password.size() > 14) {
		cout << "The password must contain from 8 to 14 characters. Use another one." << endl;
		return true;
	}
	vector<char> arr(password.begin(), password.end()); // разбиение строки на символы
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] > 47 && arr[i] < 58) flagForNumber = true;
		if (arr[i] > 64 && arr[i] < 91) flagForBigLetter = true;
		if (arr[i] > 32 && arr[i] < 48) flagForSpecialSymbol = true;
		if (arr[i] > 57 && arr[i] < 65) flagForSpecialSymbol = true;
	}
	if (flagForNumber && flagForBigLetter && flagForSpecialSymbol) return false; // пароль подходит
	if (!flagForNumber) {
		cout << "The password must have at least one number" << endl;
		return true;
	}
	if (!flagForSpecialSymbol) {
		cout << "The password must have at least one special symbol" << endl;
		return true;
	}
	if (!flagForBigLetter) {
		cout << "The password must have at least one big letter" << endl;
		return true;
	}
	return true;
}

void UsersData::toCipherWord(string word, string key) {
	for (int i = 0; key[i] != '\0'; i++) {
		key[i] = tolower(key[i]);
	}
	int counter = 0;
	string wordWithKey = word;
	string sipheredWord = word;
	for (int i = 0; word[i] != '\0'; i++) {
		if (key[counter] == '\0') {
			counter = 0;
		}
		wordWithKey[i] = key[counter++];
	}
	int numOfLetter;
	for (int i = 0; word[i] != '\0'; i++) {
		numOfLetter = word[i];
		if (isupper(word[i])) {
			numOfLetter = word[i] + (wordWithKey[i] - 96);
			if (numOfLetter > 90) {
				numOfLetter -= 26;
			}
		}
		else if (islower(word[i])) {
			numOfLetter = word[i] + (wordWithKey[i] - 96);
			if (numOfLetter > 122) {
				numOfLetter -= 26;
			}
		}
		else if (isdigit(word[i])) {
			numOfLetter = word[i] + (wordWithKey[i] - 96);
			while (numOfLetter > 57) {
				numOfLetter -= 10;
			}
		}
		sipheredWord[i] = numOfLetter;
	}
	cout << sipheredWord << endl;
}


bool UsersData::containsSpaces(string str)
{
	for (char ch : str) {
		if (ch == ' ') {
			return true;
		}
	}
	return false; 
}


bool UsersData::containsColon(string str)
{
	for (char ch : str) {
		if (ch == ':') {
			return true;
		}
	}
	return false;
}

bool UsersData::isPhoneNumberValid(string phoneNumber) {
	if (phoneNumber.size() == 11) {
		return false; 
	}
	else
	{
		return true;
	}
	for (int i = 0; i < phoneNumber.length(); i++) {
		if (phoneNumber[i] < 48 || phoneNumber[i] > 57) {
			cout << "enter numbers only" << endl;
			return true; 
		}
		else
		{
			return false;
		}
	}

}


UsersData::~UsersData()
{
}
