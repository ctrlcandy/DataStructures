#ifndef SHUNTINGYARD_H
#define SHUNTINGYARD_H

#include <cmath>
#include <cstring>
#include <vector>
#include "MyVector/MyVector.h"
#include "Queue/Queue.h"

class ShuntingYard {
public:
    ShuntingYard() {};

    //Токенизация, возвращается вектор указателей на абстрактный токен
    //(необходимо в исходнике вектора поменять ValueType = double на AbstractToken)
    MyVector tokenize(const char* expression);

    //Очередь указателей на абстрактный токен
    static Queue shuntingYard(MyVector& tokens);

    double calc(Queue& tokenQueue);

    ~ShuntingYard() {};

private:
    static bool checkPriority(const Token& bottom, const Token& top) {
        if (bottom.value() == "-" || bottom.value() == "+") {
            if (top.value() == "*" || top.value() == "/" || top.value() == "^")
                return true;
        }
        else if (bottom.value() == "*" || bottom.value() == "/") {
            if (top.value() == "^")
                return true;
        }

        return false;
    };

    /*static double calcFunc(const char* oper, const AbstractToken& bottom, const AbstractToken& top) {
        if (strcmp(oper, "-") == 0 ) {
            return std::stoi(bottom.value()) - std::stoi(top.value());
        }
       else if (strcmp(oper, "+") == 0 ) {
            return std::stoi(bottom.value()) + std::stoi(top.value());
       }
       else if (strcmp(oper, "*") == 0 ) {
            return std::stoi(bottom.value()) * std::stoi(top.value());
       }
       else if (strcmp(oper, "/") == 0 ) {
            return std::stoi(bottom.value()) / std::stoi(top.value());
       }
       else if (strcmp(oper, "^") == 0 ) {
            return std::pow(std::stoi(bottom.value()), std::stoi(top.value()));
       }
    }*/
};


#endif //SHUNTINGYARD_H
