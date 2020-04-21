#ifndef SHUNTINGYARD_H
#define SHUNTINGYARD_H

#include <cmath>
#include <cstring>
#include <vector>
#include "MyVector/MyVector.h"
#include "Queue/Queue.h"
#include "Tokens/AbstractToken.h"

class ShuntingYard {
public:
    ShuntingYard() {};

    //Токенизация, возвращается вектор указателей на абстрактный токен
    //(необходимо в исходнике вектора поменять ValueType = double на AbstractToken)
    std::vector<AbstractToken> tokenize(const char* expression);

    //Очередь указателей на абстрактный токен
    static Queue shuntingYard(std::vector<AbstractToken>& tokens);

    double calc(Queue& tokenQueue);

    ~ShuntingYard() {};

private:
    static bool checkPriority(const AbstractToken& bottom, const AbstractToken& top) {
        if (strcmp(bottom.value(), "-") == 0 || strcmp(bottom.value(), "+") == 0) {
            if (strcmp(top.value(), "*") == 0 || strcmp(top.value(), "/") == 0 ||
                strcmp(top.value(), "^") == 0)
                return true;
        }
        else if (strcmp(bottom.value(), "*") == 0 || strcmp(bottom.value(), "/") == 0) {
            if (strcmp(top.value(), "^") == 0)
                return true;
        }

        return false;
    };

    static double calcFunc(const char* oper, const AbstractToken& bottom, const AbstractToken& top) {
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
    }
};


#endif //SHUNTINGYARD_H
