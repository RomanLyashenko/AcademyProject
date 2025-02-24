#include "User.h"

User::User(string login, Admin& admin) : UsersData(), admin(admin) {

}

void User::testing() {
    string testName;
    Test test;

    do {
        cout << "Enter the name of the test you want to take: ";
        cin >> testName;

        // Проверяем, существует ли тест с таким названием
        if (!admin.isTestNameTaken(testName)) {
            cout << "Test with the name '" << testName << "' not found. Please try again." << endl;
        }
        else {
            test = loadTestFromFile(testName);  // Загружаем тест из файла
        }
    } while (!admin.isTestNameTaken(testName)); // Повторяем цикл, пока не выберем существующий тест

    if (test.questions.empty()) {
        cout << "No questions found for this test." << endl;
        return;  // Если вопросы не загружены, выходим из функции
    }

    // Сбор ответов пользователя
    vector<string> userAnswers;
    cout << "\nStarting test: " << test.name << " (" << test.category << ")\n" << endl;

    for (size_t i = 0; i < test.questions.size(); ++i) {
        string userAnswer;
        cout << "Question " << (i + 1) << ": " << test.questions[i] << endl;
        cout << "Enter your answer (y/n): ";
        cin.ignore(); // Очищаем буфер перед вводом
        getline(cin, userAnswer);
        userAnswers.push_back(userAnswer);
    }

    // Оценка результатов
    int correctAnswers = 0;
    for (size_t i = 0; i < test.answers.size(); ++i) {
        // Сравниваем ответ пользователя с правильным ответом (первый элемент пары)
        if (userAnswers[i] == test.answers[i].first) {
            correctAnswers++;
        }
    }

    // Оценка по 12-бальной шкале
    double maxScore = 12.0; // Максимальный балл
    double score = (correctAnswers * maxScore) / test.questions.size();  // Оценка на основе количества правильных ответов

    cout << "\nYour score: " << score << endl;

    // Запись результата в файл
    saveResultToFile(test.name, score);
}

Test User::loadTestFromFile(const string& testName) {
    ifstream testFile("Tests.txt");
    string line;
    Test test;

    if (!testFile.is_open()) {
        cout << "Error opening the test file." << endl;
        return test;
    }

    while (getline(testFile, line)) {
        stringstream ss(line);
        string category, name;
        vector<string> questions;
        vector<pair<string, string>> answers;

        // Читаем категорию и название теста
        getline(ss, category, ':');
        getline(ss, name, ':');
        test.category = category;
        test.name = name;

        // Чтение вопросов и ответов, разделённых через "::"
        while (getline(ss, line, ':')) {
            // Читаем вопрос
            string question = line;

            // Читаем правильный и неправильный ответ
            getline(ss, line, ':');
            string correctAnswer = line;
            getline(ss, line, ':');
            string incorrectAnswer = line;

            questions.push_back(question);
            answers.push_back({ correctAnswer, incorrectAnswer });

            // Если следующий символ в потоке - это ":", значит, мы переходим к следующему вопросу
            if (ss.peek() == ':') {
                ss.get();  // Пропускаем одно двоеточие
            }
        }

        if (test.name == testName) {
            test.questions = questions;
            test.answers = answers;
            break;
        }
    }

    testFile.close();
    return test;
}

void User::saveResultToFile(const string& testName, int score)
{
    // Формируем путь к файлу с результатами
    string resultFileName = getLogin() + "Results.txt";  // Формируем имя файла с результатами
    ofstream resultFile(resultFileName, ios::app);  // Открываем файл для добавления данных

    if (!resultFile.is_open()) {
        cout << "Error opening the results file." << endl;
        return;
    }

    // Записываем результат в файл
    resultFile << "Test: " << testName << ", Score: " << score << endl;

    resultFile.close();

    cout << "Your result has been saved in " << resultFileName << "!" << endl;
}

User::~User()
{

}
