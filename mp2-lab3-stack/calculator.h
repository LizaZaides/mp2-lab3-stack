#pragma once
#include <string>
#include "container.h"
#include "Token.h"
#include <cctype>
#include <cstdlib>
#include <cmath>
#include "Stack.h"

using std::string;


class Calculator
{
    string infix, postfix;
    Container<Token> inf_cont, post_cont;
    Stack<Token> oper;
    Stack<double> num;
    void infix_to_cont()
    {
        inf_cont.clear();
        int i = 0;
        Token t;
        while (i < infix.size())
        {
            if (infix[i] == '(')
            {
                Token t;
                t.type = OpenBr;
                t.str = "(";
                inf_cont.push_back(t);
            }
            if ((infix[i] >= '0' && infix[i] <= '9') || infix[i] == '.')
            {
                char* p;
                double val = strtod(&infix[i], &p);
                t.val = val;
                t.type = Number;
                int delta = p - &infix[i];
                t.str = infix.substr(i, delta);
                inf_cont.push_back(t);
                i += delta-1;
            }
            if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/') {
                t.type = Operat;
                t.str = infix[i];
                inf_cont.push_back(t);
            }
            i++;
        }
    }
public:
    Calculator()
    {
        infix = "";
        postfix = "";
        inf_cont.clear();
        post_cont.clear();
    }
    void to_postfix() {
        oper.clear();
        post_cont.clear();
        for (int i = 0; i < inf_cont.size(); i++) {

            if (inf_cont[i].type == OpenBr) {
                oper.push(inf_cont[i]);
                continue;
            }

            if (inf_cont[i].type == Number) {
                post_cont.push_back(inf_cont[i]);
                continue;
            }

            if (inf_cont[i].type == CloseBr) {
                while (oper.top().type != OpenBr) {
                    post_cont.push_back(oper.pop());
                }
                if (oper.IsEmpty()) {
                    throw "Error"; // была закрывающаяся скобка, но нет открывающейся скобки, после отладки удалить
                }
                oper.pop();
                continue;
            }

            if (inf_cont[i].type == Operat) {
                while (inf_cont[i].priority <= oper.top().priority) {
                    post_cont.push_back(oper.pop());
                }
                oper.push(inf_cont[i]);
                continue;
            }
        }
        if (post_cont.size() > 0) {
            postfix += post_cont[0].str;
            for (int i = 1; i < post_cont.size(); i++) {
                postfix += " " + post_cont[i].str;
            }
        }
    }

    double CalcPostfix() {
        num.clear();
        for (int i = 0; i < post_cont.size(); i++) {
            if (post_cont[i].type == Number) {
                num.push(post_cont[i].val);
                continue;
            }
            if (post_cont[i].type == Operat) {
                double right, left, res;
                if (num.IsEmpty()) {
                    throw "Error"; // Стек пустой, после отладки удалить
                }
                right = num.pop();
                if (num.IsEmpty()) {
                    throw "Error"; // Стек пустой, после отладки удалить
                }
                left = num.pop();
                if (post_cont[i].str == "+") {
                    res = left + right;
                }
                if (post_cont[i].str == "-") {
                    res = left - right;
                }
                if (post_cont[i].str == "*") {
                    res = left * right;
                }
                if (post_cont[i].str == "/") {
                    if (right == 0) {
                        throw "Error"; // Деление на ноль
                    }
                    res = left / right;
                }
                if (post_cont[i].str == "^") {
                    res = pow(left, right);
                }
                num.push(res);
                continue;
            }
        }
        if (num.IsEmpty()) {
            throw "Error"; // Нет ответа, после отладки удалить
        }
        double ans = num.pop();
        if (!num.IsEmpty()) {
            throw "Error";
        }
        return ans;
    }
    
};