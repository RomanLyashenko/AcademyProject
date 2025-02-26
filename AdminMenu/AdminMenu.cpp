#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

struct User {
    string username;
    string password;
    string fullName;
    string address;
    string phone;
};

vector<User> users;

// Функция для загрузки данных пользователей из файла
void loadUsers(const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        User temp;
        while (getline(inFile, temp.username)) {
            getline(inFile, temp.password);
            getline(inFile, temp.fullName);
            getline(inFile, temp.address);
            getline(inFile, temp.phone);
            users.push_back(temp);
        }
        inFile.close();
    }
}

// Функция для сохранения данных пользователей в файл
void saveUsers(const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& user : users) {
            outFile << user.username << endl;
            outFile << user.password << endl;
            outFile << user.fullName << endl;
            outFile << user.address << endl;
            outFile << user.phone << endl;
        }
        outFile.close();
    }
}

// Функции для управления пользователями
void addUser() {
    User newUser;
    cout << "Введите логин пользователя: ";
    cin >> newUser.username;
    cout << "Введите пароль пользователя: ";
    cin >> newUser.password;
    cout << "Введите ФИО пользователя: ";
    cin.ignore();
    getline(cin, newUser.fullName);
    cout << "Введите адрес пользователя: ";
    getline(cin, newUser.address);
    cout << "Введите телефон пользователя: ";
    getline(cin, newUser.phone);

    users.push_back(newUser);
    cout << "Пользователь успешно добавлен." << endl;
}

void deleteUser() {
    string username;
    cout << "Введите логин пользователя для удаления: ";
    cin >> username;

    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->username == username) {
            users.erase(it);
            cout << "Пользователь удален." << endl;
            return;
        }
    }
    cout << "Пользователь не найден." << endl;
}

void modifyUser() {
    string username;
    cout << "Введите логин пользователя для изменения данных: ";
    cin >> username;

    for (auto& user : users) {
        if (user.username == username) {
            cout << "Изменение данных для пользователя " << username << endl;
            cout << "1. Изменить ФИО" << endl;
            cout << "2. Изменить адрес" << endl;
            cout << "3. Изменить телефон" << endl;
            cout << "4. Изменить пароль" << endl;
            int choice;
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                cout << "Введите новое ФИО: ";
                getline(cin, user.fullName);
                break;
            case 2:
                cout << "Введите новый адрес: ";
                getline(cin, user.address);
                break;
            case 3:
                cout << "Введите новый телефон: ";
                getline(cin, user.phone);
                break;
            case 4:
                cout << "Введите новый пароль: ";
                getline(cin, user.password);
                break;
            default:
                cout << "Неверный выбор." << endl;
            }
            cout << "Данные пользователя обновлены." << endl;
            return;
        }
    }
    cout << "Пользователь не найден." << endl;
}

void manageUsers() {
    int choice;
    cout << "1. Добавить пользователя" << endl;
    cout << "2. Удалить пользователя" << endl;
    cout << "3. Изменить данные пользователя" << endl;
    cout << "Выберите опцию: ";
    cin >> choice;

    switch (choice) {
    case 1:
        addUser();
        break;
    case 2:
        deleteUser();
        break;
    case 3:
        modifyUser();
        break;
    default:
        cout << "Неверный выбор, попробуйте снова." << endl;
    }
}

// Функция для регистрации администратора
void registerAdmin(const string& filename) {
    string login, password;

    // Запросить логин и пароль
    cout << "Регистрация администратора." << endl;
    cout << "Введите логин: ";
    cin >> login;
    cout << "Введите пароль: ";
    cin >> password;

    // Открыть файл для записи
    ofstream outFile(filename);
    if (outFile.is_open()) {
        // Сохранить логин и пароль в файл
        outFile << login << endl << password;
        outFile.close();
        cout << "Администратор успешно зарегистрирован." << endl;
    }
    else {
        cout << "Ошибка при сохранении данных." << endl;
    }
}

// Функция для входа администратора
bool loginAdmin(const string& filename) {
    string login, password;

    // Открыть файл для чтения
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        return false; // Файл не найден, значит, администратор еще не зарегистрирован
    }

    string storedLogin, storedPassword;
    getline(inFile, storedLogin);
    getline(inFile, storedPassword);
    inFile.close();

    // Запросить логин и пароль
    cout << "Введите логин: ";
    cin >> login;
    cout << "Введите пароль: ";
    cin >> password;

    // Проверить, совпадают ли введенные данные с сохраненными
    if (login == storedLogin && password == storedPassword) {
        return true;
    }
    return false;
}

// Функция для изменения логина и пароля администратора
void changePassword(const string& filename) {
    string newLogin, newPassword;

    cout << "Введите новый логин: ";
    cin >> newLogin;
    cout << "Введите новый пароль: ";
    cin >> newPassword;

    // Перезаписываем файл с новым логином и паролем
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << newLogin << endl << newPassword;
        outFile.close();
        cout << "Логин и пароль успешно изменены." << endl;
    }
    else {
        cout << "Ошибка при сохранении данных." << endl;
    }
}

void menu() {
    int choice;
    cout << "Меню администратора:" << endl;
    cout << "1. Управление пользователями" << endl;
    cout << "2. Изменить логин и пароль" << endl;
    cout << "3. Выйти" << endl;
    cout << "Выберите опцию: ";
    cin >> choice;

    switch (choice) {
    case 1:
        manageUsers();
        break;
    case 2:
        changePassword("admin_data.txt"); // Файл с данными администратора
        break;
    case 3:
        cout << "Выход из программы..." << endl;
        exit(0);
    default:
        cout << "Неверный выбор, попробуйте снова." << endl;
    }
}

int main() {

    setlocale(LC_ALL, "rus");

    string filename = "admin_data.txt"; // Файл для хранения данных о пользователе
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        // Если файл не существует, значит, администратор не зарегистрирован, и нужно его зарегистрировать
        registerAdmin(filename);
    }

    // Проверка логина и пароля
    if (loginAdmin(filename)) {
        cout << "Добро пожаловать, администратор!" << endl;
        while (true) {
            menu();
        }
    }
    else {
        cout << "Неверный логин или пароль." << endl;
    }

    return 0;
}