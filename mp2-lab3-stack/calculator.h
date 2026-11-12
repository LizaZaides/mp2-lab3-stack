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

    int Priority(const Token& t) const {
        if (t.type != Operat) return 0;
        if (t.str == "+" || t.str == "-") return 1;
        if (t.str == "*" || t.str == "/") return 2;
        if (t.str == "^") return 3;
        return 0;
    }

    void infix_to_cont()
    {
        inf_cont.clear();
        inf_cont.push_back(Token(OpenBr, "(", 0.0, 0));

        int i = 0;
        while (i < infix.size())
        {
            if (infix[i] == ' ') {
                i++;
                continue;
            }
            if (infix[i] == '(') {
                inf_cont.push_back(Token(OpenBr, "(", 0.0, 0));
                i++;
                continue;
            }
            if (infix[i] == ')') {
                inf_cont.push_back(Token(CloseBr, ")", 0.0, 0));
                i++;
                continue;
            }


            if ((infix[i] >= '0' && infix[i] <= '9') || infix[i] == '.')
            {
                char* p;
                double val = strtod(&infix[i], &p);
                int delta = p - &infix[i];
                inf_cont.push_back(Token(Number, infix.substr(i, delta), val, 0));
                i += delta;
                continue;
            }
            if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^') {
                Token t(Operat, string(1, infix[i]));
                t.priority = Priority(t);
                inf_cont.push_back(t);
                i++;
                continue;
            }
        }
        inf_cont.push_back(Token(CloseBr, ")", 0.0, 0));
    }
public:


    Calculator()
    {
        infix = "";
        postfix = "";
        inf_cont.clear();
        post_cont.clear();
    }

    void set_infix(const string& s) {
        infix = s;
        postfix = "";
        inf_cont.clear();
        post_cont.clear();
        if (!infix.empty()) {
            infix_to_cont();
        }
    }

    void to_postfix() {
        oper.clear();
        post_cont.clear();
        postfix = "";
        for (int i = 0; i < inf_cont.get_count(); i++) {

            if (inf_cont[i].type == OpenBr) {
                oper.push(inf_cont[i]);
                continue;
            }

            if (inf_cont[i].type == Number) {
                post_cont.push_back(inf_cont[i]);
                continue;
            }

            if (inf_cont[i].type == CloseBr) {
                while (!oper.IsEmpty() && oper.top().type != OpenBr) {
                    post_cont.push_back(oper.pop());
                }
                if (oper.IsEmpty()) {
                    throw "Error";
                }
                oper.pop();
                continue;
            }

            if (inf_cont[i].type == Operat) {
                while (!oper.IsEmpty() && oper.top().type == Operat &&Priority(inf_cont[i]) <= Priority(oper.top())) {
                    post_cont.push_back(oper.pop());
                }
                oper.push(inf_cont[i]);
                continue;
            }
        }
        if (post_cont.get_count() > 0) {
            postfix += post_cont[0].str;
            for (int i = 1; i < post_cont.get_count(); i++) {
                postfix += " " + post_cont[i].str;
            }
        }
    }

    double CalcPostfix() {
        num.clear();
        for (int i = 0; i < post_cont.get_count(); i++) {
            if (post_cont[i].type == Number) {
                num.push(post_cont[i].val);
                continue;
            }
            if (post_cont[i].type == Operat) {
                double right, left, res = 0;
                if (num.IsEmpty()) {
                    throw "Error"; 
                }
                right = num.pop();
                if (num.IsEmpty()) {
                    throw "Error"; 
                }
                left = num.pop();
                if (post_cont[i].str == "+") {
                    res = left + right;
                }
                else if (post_cont[i].str == "-") {
                    res = left - right;
                }
                else if (post_cont[i].str == "*") {
                    res = left * right;
                }
                else if (post_cont[i].str == "/") {
                    if (right == 0) {
                        throw "Error"; 
                    }
                    res = left / right;
                }
                else if (post_cont[i].str == "^") {
                    res = pow(left, right);
                }
                num.push(res);
                continue;
            }
        }
        if (num.IsEmpty()) {
            throw "Error";
        }
        double ans = num.pop();
        if (!num.IsEmpty()) {
            throw "Error";
        }
        return ans;
    }
    string get_postfix() const { return postfix; }
};