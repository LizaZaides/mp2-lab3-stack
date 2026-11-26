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
    string infix;
    Container<Token> inf_cont;
    Stack<Token> st_oper;
    Stack<double> st_num;
    int Priority(const Token& t) const {
        if (t.t_type == Function) return 4;
        if (t.t_type != Operat) return 0;
        if (t.str == "+" || t.str == "-") return 1;
        if (t.str == "*" || t.str == "/") return 2;
        if (t.str == "^") return 3;
        return 0;
    }

    void infix_to_cont()
    {
        inf_cont.clear();
        //пробелы убрать для strtod
        string c_infix = "";
        for (int i = 0; i < infix.length(); i++) {
            char c = infix[i];
            if (c != ' ') c_infix += c;
        }
        inf_cont.push_back(Token(OpenBr, "(", 0.0, 0));

        int i = 0;
        while (i < c_infix.size())
        {
            /*if (infix[i] == ' ') {
                i++;
                continue;
            }*/

            if (c_infix.empty()) throw "error";
            if (c_infix[i] == '(') {
                inf_cont.push_back(Token(OpenBr, "(", 0.0, 0));
                i++;
                continue;
            }
            if (c_infix[i] == ')') {
                inf_cont.push_back(Token(CloseBr, ")", 0.0, 0));
                i++;
                continue;
            }

            if (c_infix.substr(i, 3) == "sin") {
                inf_cont.push_back(Token(Function, "sin", 0.0, 4));
                i += 3;
                continue;
            }
            if (c_infix.substr(i, 3) == "cos") {
                inf_cont.push_back(Token(Function, "cos", 0.0, 4));
                i += 3;
                continue;
            }
            if (c_infix.substr(i, 3) == "exp") {
                inf_cont.push_back(Token(Function, "exp", 0.0, 4));
                i += 3;
                continue;
            }
            if (c_infix.substr(i, 2) == "ln") {
                inf_cont.push_back(Token(Function, "ln", 0.0, 4));
                i += 2;
                continue;
            }


            if ((c_infix[i] >= '0' && c_infix[i] <= '9') || c_infix[i] == '.' ||
                (c_infix[i] == '-' && (i == 0 || c_infix[i - 1] == '(' || c_infix[i - 1] == '+' || c_infix[i - 1] == '-' || c_infix[i - 1] == '*' || c_infix[i - 1] == '/')))
            {
                char* p;
                double val = strtod(&c_infix[i], &p);
                int delta = p - &c_infix[i];
                if (c_infix[i + delta] == '.') throw "error";
                inf_cont.push_back(Token(Number, c_infix.substr(i, delta), val, 0));
                i += delta;
                continue;
            }
            if (c_infix[i] == '+' || c_infix[i] == '-' || c_infix[i] == '*' || c_infix[i] == '/' || c_infix[i] == '^') {
                Token t(Operat, string(1, c_infix[i]));
                t.priority = Priority(t);
                inf_cont.push_back(t);
                i++;
                continue;
            }
            throw "error";
        }
        inf_cont.push_back(Token(CloseBr, ")", 0.0, 0));
    }

public:
    void set_infix(const string& s) {
        infix = s;
        inf_cont.clear();
        if (!infix.empty()) {
            infix_to_cont();
        }
    }

    double Calc() {
        st_oper.clear();
        st_num.clear();

        for (int i = 0; i < inf_cont.get_count();i++) {
            if (inf_cont[i].t_type == OpenBr) {
                st_oper.push(inf_cont[i]);
            }
            else if (inf_cont[i].t_type == Number) {
                st_num.push(inf_cont[i].val);
            }

            else if (inf_cont[i].t_type == Function) {
                st_oper.push(inf_cont[i]);
            }

            else if (inf_cont[i].t_type == CloseBr) {
                while (!st_oper.IsEmpty() && st_oper.top().t_type != OpenBr) {
                    double op2 = st_num.pop(), op1 = st_num.pop();
                    double tmp = 0;
                    string op = st_oper.pop().str;
                    if (op == "+") tmp = op1 + op2;
                    else if (op == "-") tmp = op1 - op2;
                    else if (op == "*") tmp = op1 * op2;
                    else if (op == "/") {
                        if (op2 == 0) throw "error";
                        tmp = op1 / op2;
                    }
                    else if (op == "^") tmp = pow(op1, op2);
                    st_num.push(tmp);
                }
                if (st_oper.IsEmpty()) throw "error";

                if (!st_oper.IsEmpty()) {
                    st_oper.pop();
                }

                if (!st_oper.IsEmpty() && st_oper.top().t_type == Function) {
                    double v = st_num.pop();
                    string f = st_oper.pop().str;
                    double res = 0;
                    if (f == "sin") res = sin(v);
                    else if (f == "cos") res = cos(v);
                    else if (f == "exp") res = exp(v);
                    else if (f == "ln") { 
                        if (v <= 0) throw "error";
                        res = log(v); 
                    }
                    st_num.push(res);
                }
                
            }
            else if (inf_cont[i].t_type == Operat) {
                while (!st_oper.IsEmpty() && st_oper.top().t_type == Operat &&
                    Priority(st_oper.top()) >= inf_cont[i].priority) {


                    double op2 = st_num.pop();
                    double op1 = st_num.pop();
                    double tmp = 0;
                    string op = st_oper.pop().str;

                    if (op == "+") tmp = op1 + op2;
                    else if (op == "-") tmp = op1 - op2;
                    else if (op == "*") tmp = op1 * op2;
                    else if (op == "/") {
                        if (op2 == 0) throw "error";
                        tmp = op1 / op2;
                    }
                    else if (op == "^") tmp = pow(op1, op2);

                    st_num.push(tmp);
                }
                st_oper.push(inf_cont[i]);
            }
        }
        while (!st_oper.IsEmpty()) {
            if (st_oper.top().t_type == OpenBr) throw "error";
            if (st_num.IsEmpty()) throw "error";
            double op2 = st_num.pop();
            if (st_num.IsEmpty()) throw "error";
            double op1 = st_num.pop();

            double tmp = 0;
            string op = st_oper.pop().str;
            if (op == "+") tmp = op1 + op2;
            else if (op == "-") tmp = op1 - op2;
            else if (op == "*") tmp = op1 * op2;
            else if (op == "/") {
                if (op2 == 0) throw "error";
                tmp = op1 / op2;
            }
            else if (op == "^") tmp = pow(op1, op2);
            st_num.push(tmp);
        }


        if (st_num.IsEmpty()) throw "error";
        double result = st_num.pop();
        if (!st_num.IsEmpty()) throw "error";
        return result;
    }


    string getInfix() const {
        return infix;
    }

    friend std::ostream& operator<<(std::ostream& os, const Calculator& c) {
        os << c.infix;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Calculator& c) {
        string s;
        getline(is, s);
        c.set_infix(s);
        return is;
    }

};
