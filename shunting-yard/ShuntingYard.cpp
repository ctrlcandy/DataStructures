#include <cstring>
#include <stdexcept>
#include "ShuntingYard.h"
#include "Tokens/NumberToken.h"
#include "Tokens/ParenthesesToken.h"
#include "Tokens/OperationToken.h"
#include "Tokens/AbstractToken.h"
#include "Stack/Stack.h"
#include "Queue/Queue.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

std::vector<AbstractToken> ShuntingYard::tokenize(const char* expression) {
    size_t len = strlen(expression);
    std::vector<AbstractToken> result;
    std::string bufNum;
    std::string sym;
    char* buf;
    for (size_t i = 0; i < len; i++) {
        switch (expression[i]) {
            case ('('):
            case (')'):
                if (!bufNum.empty()) {
                    result.push_back(NumberToken(bufNum.c_str()));
                    bufNum = "";
                }

                sym = expression[i];
                result.push_back(ParenthesesToken(sym.c_str()));
                cout << sym << endl;
                break;
            case ('+'):
            case ('-'):
            case ('/'):
            case ('*'):
            case ('^'):
                if (!bufNum.empty()) {
                    result.push_back(NumberToken(bufNum.c_str()));
                    cout << bufNum.c_str() << endl;
                    bufNum = "";
                }

                sym = expression[i];
                result.push_back(OperationToken(sym.c_str()));
                cout << sym << endl;
                break;
            case ('0'):
            case ('1'):
            case ('2'):
            case ('3'):
            case ('4'):
            case ('5'):
            case ('6'):
            case ('7'):
            case ('8'):
            case ('9'):
                bufNum += expression[i];
                break;
            default:
                throw std::invalid_argument("Incorrect token");

        }
    }
    if (!bufNum.empty()) {
        cout << bufNum.c_str() << endl;
        result.push_back(NumberToken(bufNum.c_str()));
    }

    return result;
}

Queue ShuntingYard::shuntingYard(std::vector<AbstractToken>& tokens) {
    Stack stack;
    Queue queue;

    size_t size = tokens.size();
    for (size_t i = 0; i < size; ++i) {
        if (strcmp(tokens[i].name(), "OperationToken") == 0) {
            while (strcmp(tokens[i].name(), "OperationToken") == 0 ||
            ShuntingYard::checkPriority(stack.top(), tokens[i]) &&
            strcmp(tokens[i].name(), "(") == 0) {
                queue.enqueue(stack.top());
                stack.pop();
                stack.push(tokens[i]);
            }
        }
        else if (strcmp(tokens[i].name(), "NumberToken") == 0){
            queue.enqueue(tokens[i]);
        }
        else if (strcmp(tokens[i].name(), "ParenthesesToken") == 0) {
            if (strcmp(tokens[i].name(), "(") == 0) {
                stack.push(tokens[i]);
            }
            else if (strcmp(tokens[i].name(), ")") == 0) {
                while (strcmp(stack.top().value(), "(") != 0) {
                    queue.enqueue(stack.top());
                    stack.pop();

                    if (stack.isEmpty()) {
                        throw std::invalid_argument("Incorrect ParenthesesToken");
                    }
                }
                stack.pop();
            }
        }
        else throw std::invalid_argument("Incorrect token");
    }

    while (!stack.isEmpty()) {
        if (strcmp(stack.top().value(), "(") == 0 || strcmp(stack.top().value(), ")") == 0) {
            throw std::invalid_argument("Incorrect ParenthesesToken");
        }
        queue.enqueue(stack.top());
        stack.pop();
    }

    return  queue;
}

double ShuntingYard::calc(Queue& tokenQueue) {
    Stack stack;
    size_t res;
    size_t size = tokenQueue.size();
    for (size_t i = 0; i < size; i++) {
        if (strcmp(tokenQueue.front().name(), "NumberToken") == 0) {
            if (strcmp(stack.top().name(), "OperationToken") == 0) {
                NumberToken top(tokenQueue.front().value());
                tokenQueue.dequeue();
                const char* oper = stack.top().value();
                stack.pop();
                NumberToken bottom(stack.top().value());
                res += ShuntingYard::calcFunc(oper, bottom, top);
            }
        }
        else {
            stack.push(tokenQueue.front());
            tokenQueue.dequeue();
        }
    }
    return res;
}
