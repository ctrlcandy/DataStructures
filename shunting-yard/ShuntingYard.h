#ifndef SHUNTINGYARD_H
#define SHUNTINGYARD_H

#include <cmath>
#include <cstring>
#include <vector>
#include <iostream>
#include "MyVector/MyVector.h"
#include "Queue/Queue.h"

class ShuntingYard {
public:
    ShuntingYard() {};

    //Токенизация, возвращается вектор указателей на абстрактный токен
    //(необходимо в исходнике вектора поменять ValueType = double на Token)
    MyVector tokenize(const char *expression);

    //Очередь указателей на абстрактный токен
    static Queue shuntingYard(MyVector &tokens);

    double calc(Queue &tokenQueue);

    ~ShuntingYard() {};

private:
    static bool checkPriority(const Token &bottom, const Token &top) {
        if (top.value() == "-" || top.value() == "+") {
            if (bottom.value() == "*" || bottom.value() == "/" || bottom.value() == "^")
                return true;
        } else if (top.value() == "*" || top.value() == "/") {
            if (bottom.value() == "^")
                return true;
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
