#include "Admin.h"

Admin::Admin()
{
}

void Admin::createNewUser()
{
    registration();
}

void Admin::deleteUser()
{
    string userLogin;
    int counter = 0;
    cout << "Login of the user who must to be deleted: ";
    cin >> userLogin;

    // Проверка на наличие пользователя
    if (!loginCheck(userLogin, getPathToUsersData())) {
        cout << "User not found." << endl;
        return;
    }
    else {
        ifstream in(getPathToUsersData());  // Открываем файл для чтения
        ofstream out("temp_users.txt");     // Открываем временный файл для записи
        string line;
        bool userFound = false;  // Флаг, который покажет, нашли ли мы пользователя

        // Чтение строк из файла
        while (getline(in, line)) {
            stringstream ss(line);
            string name, lastName, patronymic, login, password, address, phone;

            // Разделение строки по разделителю ':'
            if (getline(ss, name, ':') &&
                getline(ss, lastName, ':') &&
                getline(ss, patronymic, ':') &&
                getline(ss, login, ':') &&
                getline(ss, password, ':') &&
                getline(ss, address, ':') &&
                getline(ss, phone))
            {
                // Если логин совпал, пропускаем эту строку (не записываем в новый файл)
                if (userLogin == login) {
                    userFound = true;
                    continue;  // Пропускаем текущую строку
                }
            }

            // Если логин не совпал, записываем строку в новый файл
            out << line << endl;
            counter++;
        }

        // Закрываем файлы
        in.close();
        out.close();

        // Если пользователь был найден, заменяем оригинальный файл временным
        if (userFound) {
            remove(getPathToUsersData().c_str());  // Удаляем старый файл
            rename("temp_users.txt", getPathToUsersData().c_str());  // Переименовываем временный файл в оригинальный
            cout << "User with login " << userLogin << " deleted successfully!" << endl;
        }
        else {
            cout << "User with login " << userLogin << " not found." << endl;
        }
    }
}

bool Admin::isTestNameTaken(const string& testName)
{
    // Открываем файл "Tests.txt" в режиме чтения
    ifstream testFile("Tests.txt");

    if (!testFile.is_open()) {
        return false;  // Если файл не существует или не открыт, возвращаем false (тест не найден)
    }

    string line;
    while (getline(testFile, line)) {
        // Разбиваем строку на части по символу ":"
        stringstream ss(line);
        string category, existingTestName, rest;
        getline(ss, category, ':');
        getline(ss, existingTestName, ':');

        // Если имя теста совпадает, значит, оно занято
        if (existingTestName == testName) {
            testFile.close();
            return true;
        }
    }

    testFile.close();
    return false;  // Имя не найдено
}

void Admin::createTest() {
    vector<string> validCategories = { "Physics", "Math", "Law", "Programming", "Geography", "Other" };

    string category;
    bool validCategory = false;

    do {
        // Вводим категорию теста
        cout << "Enter the category of the test (Physics, Math, Law, Programming, Geography, Other): ";
        cin >> category;

        validCategory = false;
        for (const string& validCat : validCategories) {
            if (category == validCat) {
                validCategory = true;
                break;
            }
        }

        if (!validCategory) {
            cout << "Invalid category! Please choose one of the following: Physics, Math, Law, Programming, Geography, Other." << endl;
        }

    } while (!validCategory); // Повторяем, пока категория не будет верной

    // Вводим название теста и проверяем, занято ли оно
    string testName;
    bool nameTaken = false;
    do {
        cout << "Enter the name of the test: ";
        cin >> testName;

        // Проверяем, занято ли название
        nameTaken = isTestNameTaken(testName);
        if (nameTaken) {
            cout << "Test name '" << testName << "' is already taken. Please choose another name." << endl;
        }

    } while (nameTaken);  // Повторяем, пока название не будет уникальным

    // Создаем объект теста
    Test test;
    test.category = category;
    test.name = testName;

    // Вводим количество вопросов
    int numQuestions = 0;
    do {
        cout << "How many questions would you like to add? (Max 12): ";
        cin >> numQuestions;

        if (numQuestions < 1 || numQuestions > 12) {
            cout << "You can add between 1 and 12 questions only." << endl;
        }
    } while (numQuestions < 1 || numQuestions > 12);

    if (numQuestions != 1) {
        cout << "Attention!\nIf your test has 2 or more questions, press the spacebar before entering the text\nof the second and subsequent questions to avoid errors when saving your questions." << endl;
    }

    // Считываем вопросы и ответы
    for (int i = 0; i < numQuestions; ++i) {
        string question, correctAnswer, incorrectAnswer;

        cout << "Enter question " << (i + 1) << ": ";
        cin.ignore();  // Игнорируем символ новой строки перед вводом вопроса
        getline(cin, question);

        cout << "Enter the correct answer: ";
        getline(cin, correctAnswer);

        cout << "Enter the incorrect answer: ";
        getline(cin, incorrectAnswer);

        // Добавляем вопрос и ответы в объект теста
        test.questions.push_back(question);
        test.answers.push_back({ correctAnswer, incorrectAnswer });
    }

    // Сохраняем тест в файл
    test.saveToFile("Tests.txt");

    cout << "Test created successfully and saved to Tests.txt" << endl;
}

Admin::~Admin()
{
}
