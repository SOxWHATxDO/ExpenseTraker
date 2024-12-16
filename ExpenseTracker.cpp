#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <Windows.h>

using namespace std;

// Структура для хранения данных о расходах
struct Expense {
    string category;
    double amount;
    string description;
    string date;
};

// Функция для загрузки данных из файла
vector<Expense> loadData(const string& filename) {
    vector<Expense> expenses;
    ifstream file(filename);

    if (!file.is_open()) {
        return expenses; // Если файл не найден, возвращаем пустой список
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        Expense expense;
        getline(iss, expense.category, ',');
        iss >> expense.amount;
        iss.ignore(); // Пропускаем запятую
        getline(iss, expense.description, ',');
        getline(iss, expense.date, ',');
        expenses.push_back(expense);
    }

    file.close();
    return expenses;
}

// Функция для сохранения данных в файл
void saveData(const vector<Expense>& expenses, const string& filename) {
    ofstream file(filename);

    for (const auto& expense : expenses) {
        file << expense.category << "," << expense.amount << "," << expense.description << "," << expense.date << endl;
    }

    file.close();
}

// Функция для добавления новой записи о расходе
void addExpense(vector<Expense>& expenses) {
    cout << "\nДобавление нового расхода\n";
    Expense expense;

    cout << "Введите категорию: ";
    cin.ignore();
    getline(cin, expense.category);

    cout << "Введите сумму расхода: ";
    cin >> expense.amount;

    cout << "Введите описание (необязательно): ";
    cin.ignore();
    getline(cin, expense.description);

    cout << "Введите дату (в формате ГГГГ-ММ-ДД): ";
    getline(cin, expense.date);

    expenses.push_back(expense);
    cout << "Запись успешно добавлена!" << endl;
}

// Функция для просмотра всех расходов
void viewExpenses(const vector<Expense>& expenses) {
    cout << "\nИстория расходов:\n";

    if (expenses.empty()) {
        cout << "Нет записей о расходах.\n";
        return;
    }

    for (size_t i = 0; i < expenses.size(); ++i) {
        cout << i + 1 << ". " << expenses[i].date << " | "
            << expenses[i].category << " | "
            << expenses[i].amount << " | "
            << expenses[i].description << endl;
    }
}

// Функция для подсчета общей суммы расходов
void calculateTotal(const vector<Expense>& expenses) {
    double total = 0.0;

    for (const auto& expense : expenses) {
        total += expense.amount;
    }

    cout << "\nОбщая сумма расходов: " << total << endl;
}

// Функция для поиска расходов по категории
void searchByCategory(const vector<Expense>& expenses) {
    cout << "\nВведите категорию для поиска: ";
    string category;
    cin.ignore();
    getline(cin, category);

    vector<Expense> filteredExpenses;
    for (const auto& expense : expenses) {
        if (expense.category == category) {
            filteredExpenses.push_back(expense);
        }
    }

    if (filteredExpenses.empty()) {
        cout << "Записи с указанной категорией не найдены.\n";
    }
    else {
        cout << "Расходы в категории '" << category << "':\n";
        for (size_t i = 0; i < filteredExpenses.size(); ++i) {
            cout << i + 1 << ". " << filteredExpenses[i].date << " | "
                << filteredExpenses[i].amount << " | "
                << filteredExpenses[i].description << endl;
        }
    }
}

// Главное меню
void showMenu() {
    cout << "\nМеню:\n";
    cout << "1. Добавить запись о расходе\n";
    cout << "2. Просмотреть историю расходов\n";
    cout << "3. Подсчитать общую сумму расходов\n";
    cout << "4. Поиск расходов по категории\n";
    cout << "5. Выйти\n";
    cout << "Выберите действие (1-5): ";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const string DATA_FILE = "expenses.txt";
    vector<Expense> expenses = loadData(DATA_FILE);

    while (true) {
        showMenu();
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            addExpense(expenses);
            saveData(expenses, DATA_FILE);
            break;
        case 2:
            viewExpenses(expenses);
            break;
        case 3:
            calculateTotal(expenses);
            break;
        case 4:
            searchByCategory(expenses);
            break;
        case 5:
            cout << "Выход из программы. До свидания!\n";
            return 0;
        default:
            cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
        }
    }

    return 0;
}