#include <iostream>
#include <string>
#include "calculator.h"
#include <windows.h>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    using std::cout;
    using std::cin;
    using std::string;

    Calculator calculator;
    string input;

    cout << "Введите пример: ";
    std::getline(cin, input);

    if (input.find('x') != string::npos || input.find('X') != string::npos) {
        cout << "Введите значение переменной х: ";
        cin >> calculator.x_value;
        cin.ignore(); 
    }

    calculator.set_infix(input);

    try {
        double res = calculator.Calc();
        cout << "Инфиксная форма: " << calculator.getInfix() << "\n";
        cout << "Результат: " << res << "\n";
    }
    catch (...) {
        cout << "Error\n";
    }

    return 0;
}