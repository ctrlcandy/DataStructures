#include <cstring>
#include <stdexcept>
#include "ShuntingYard.h"
#include "Stack/Stack.h"
#include "Queue/Queue.h"
#include <iostream>

using std::cout;
using std::endl;

MyVector ShuntingYard::tokenize(const char* expression) {
    size_t len = strlen(expression);
    MyVector result;
    std::string bufNum;
    std::string bufChar;

    for (size_t i = 0; i < len; i++) {
        switch (expression[i]) {
            case ('('):
                if (!bufNum.empty()) {
                    result.pushBack(Token(Token::Type::Number, bufNum));
                    bufNum.clear();
                }
                bufChar = expression[i];
                result.pushBack(Token(Token::Type::LeftParen, bufChar));
                break;
            case (')'):
                if (!bufNum.empty()) {
                    result.pushBack(Token(Token::Type::Number, bufNum));
                    bufNum.clear();
                }
                bufChar = expression[i];
                result.pushBack(Token(Token::Type::RightParen, bufChar));
                break;
            case ('+'):
            case ('-'):
            case ('/'):
            case ('*'):
            case ('^'):
                if (!bufNum.empty()) {
                    result.pushBack(Token(Token::Type::Number, bufNum));
                    bufNum.clear();
                }
                bufChar = expression[i];
                result.pushBack(Token(Token::Type::Operator, bufChar));
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
            case (','):
            case ('.'):
                bufNum += expression[i];
                break;
            case(' '):
                continue;
            default:
                throw std::invalid_argument("Incorrect token");
        }
    }
    if (!bufNum.empty()) {
        result.pushBack(Token(Token::Type::Number, bufNum));
    }

    for (size_t i = 0; i < len; i++) {
        std::cout << result[i].value();
    }

    return result;
}

Queue ShuntingYard::shuntingYard(MyVector& tokens) {
    Stack stack;
    Queue queue;

    //for (size_t i = 0; i < tokens.size(); i++) {
    //    std::cout << tokens[i].value();
    //}

    /*size_t size = tokens.size();
    for (size_t i = 0; i < size; ++i) {
        if (tokens[i].type() == Token::Type::Operator) {
            while (tokens[i].type() == Token::Type::Operator ||
                   ShuntingYard::checkPriority(stack.top(), tokens[i]) &&
                   tokens[i].value() == "(") {
                queue.enqueue(stack.top());
                stack.pop();
                stack.push(tokens[i]);
            }
        } else if (tokens[i].type() == Token::Type::Number) {
            queue.enqueue(tokens[i]);
        } else if (tokens[i].type() == Token::Type::LeftParen) {
            stack.push(tokens[i]);
        } else if (tokens[i].type() == Token::Type::RightParen) {
            while (stack.top().type() != Token::Type::LeftParen) {
                queue.enqueue(stack.top());
                stack.pop();

                if (stack.isEmpty()) {
                    throw std::invalid_argument("Incorrect ParenthesesToken");
                }
            }
            stack.pop();
        } else throw std::invalid_argument("Incorrect token");
    }

    while (!stack.isEmpty()) {
        if (stack.top().type() == Token::Type::LeftParen || stack.top().type() == Token::Type::RightParen) {
            throw std::invalid_argument("Incorrect ParenthesesToken");
        }
        queue.enqueue(stack.top());
        stack.pop();
    } */

    return  queue;
}

double ShuntingYard::calc(Queue& tokenQueue) {
    Stack stack;
    size_t res;
    size_t size = tokenQueue.size();
    /*for (size_t i = 0; i < size; i++) {
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
    }*/
    return res;
}
