#ifndef SHUNTINGYARD_H
#define SHUNTINGYARD_H

#include <cmath>
#include <cstring>
#include "MyVector/MyVector.h"
#include "Queue/Queue.h"

class ShuntingYard {
public:
    ShuntingYard() {};

    //Токенизация, возвращается вектор указателей на абстрактный токен
    //(необходимо в исходнике вектора поменять ValueType = double на Token)
    static MyVector tokenize(const char* expression);

    //Очередь указателей на абстрактный токен
    //Представляет собой выражение в постфиксной записи, которую чаще называют обратной польской нотацией
    //RPN - Reverse Polish notation
    static Queue toRPN(MyVector& tokens);

    static double calculate(Queue& tokenQueue);

    static double calculate (const char* expression);

    ~ShuntingYard() {};

private:
    static bool checkPriority(const Token &bottom, const Token &top) {
        if (bottom.type() == Token::Type::Operator) {
            if (top.value() == "-" || top.value() == "+") {
                return true;
            } else if (top.value() == "*" || top.value() == "/") {
                if (bottom.value() != "-" && bottom.value() != "+")
                    return true;
            }
        }
        return false;
    };

    static std::string calcFunc(const Token &bottom, const Token &oper, const Token &top) {
        if (oper.value() == "-") {
            return std::to_string(std::stod(bottom.value()) - std::stod(top.value()));
        }
        else if (oper.value() == "+") {
            return std::to_string(std::stod(bottom.value()) + std::stod(top.value()));
        }
        else if (oper.value() == "*") {
            return std::to_string(std::stod(bottom.value()) * std::stod(top.value()));
        }
        else if (oper.value() == "/") {
            return std::to_string(std::stod(bottom.value()) / std::stod(top.value()));
        }
        else if (oper.value() == "^") {
            return std::to_string(std::pow(std::stod(bottom.value()), std::stod(top.value())));
        }
        else throw std::invalid_argument("Incorrect Token");
    };
};

#endif //SHUNTINGYARD_H
