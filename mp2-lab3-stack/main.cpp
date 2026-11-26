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

    cout << "¬ведите пример: ";
    std::getline(cin, input);
    calculator.set_infix(input);

    try {
        double res = calculator.Calc();
        cout << "инфиксна€ форма: " << calculator.getInfix() << "\n";
        cout << "результат: " << res << "\n";
    }
    catch (...) {
        cout << "Error\n";
    }

    return 0;
}