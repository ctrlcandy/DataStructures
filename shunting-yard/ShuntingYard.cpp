#include <cstring>
#include <stdexcept>
#include "ShuntingYard.h"
#include "Stack/Stack.h"
#include "Queue/Queue.h"


MyVector ShuntingYard::tokenize(const char* expression) {
    size_t len = strlen(expression);
    MyVector result;
    std::string bufNum;
    std::string bufChar;

    for (size_t i = 0; i < len; i++) {
        switch (expression[i]) {
            case ('('):
                if (!bufNum.empty() && bufNum != "-") {
                    result.pushBack(Token(Token::Type::Number, bufNum));
                    bufNum.clear();
                }
                bufChar = expression[i];
                result.pushBack(Token(Token::Type::LeftParen, bufChar));
                break;
            case (')'):
                if (!bufNum.empty() && bufNum != "-") {
                    result.pushBack(Token(Token::Type::Number, bufNum));
                    bufNum.clear();
                }
                bufChar = expression[i];
                result.pushBack(Token(Token::Type::RightParen, bufChar));
                break;
            case ('+'):
            case ('-'):
                if (i == 0) {
                    bufNum += "-";
                    continue;
                }
            case ('/'):
            case ('*'):
            case ('^'):
                if (!bufNum.empty() && bufNum != "-") {
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
            case (','): // Если поставить русскую локаль зачем-то
            case ('.'):
                bufNum += expression[i];
                break;
            case (' '):
                continue;
            default:
                throw std::invalid_argument("Incorrect token");
        }
    }
    if (!bufNum.empty()) {
        result.pushBack(Token(Token::Type::Number, bufNum));
    }

    return result;
}

Queue ShuntingYard::shuntingYard(MyVector& tokens) {
    Stack stack;
    Queue queue;
    size_t size = tokens.size();

    for (size_t i = 0; i < size; ++i) {
        switch (tokens[i].type()) {
            case (Token::Type::Operator) :
                while (tokens[i].type() == Token::Type::Operator &&
                       ShuntingYard::checkPriority(stack.top(), tokens[i])) {
                    queue.enqueue(stack.top());
                    stack.pop();
                }
                stack.push(tokens[i]);
                break;
            case (Token::Type::Number):
                queue.enqueue(tokens[i]);
                break;
            case (Token::Type::LeftParen):
                stack.push(tokens[i]);
                break;
            case (Token::Type::RightParen) :
                while (stack.top().type() != Token::Type::LeftParen) {
                    queue.enqueue(stack.top());
                    stack.pop();

                    if (stack.isEmpty()) {
                        throw std::invalid_argument("Incorrect ParenthesesToken");
                    }
                }
                stack.pop();
                break;
            default:
                throw std::invalid_argument("Incorrect token");
        }
    }

    while (!stack.isEmpty()) {
        if (stack.top().type() == Token::Type::LeftParen ||
            stack.top().type() == Token::Type::RightParen) {
            throw std::invalid_argument("Incorrect ParenthesesToken");
        }
        queue.enqueue(stack.top());
        stack.pop();
    }

    return queue;
}

double ShuntingYard::calc(Queue& tokenQueue) {
    Stack stack;
    double res = 0;
    size_t size = tokenQueue.size();

    for (size_t i = 0; i < size; i++) {
        if (tokenQueue.front().type() == Token::Type::Operator) {
            Token top(stack.top());
            stack.pop();
            Token bottom(stack.top());
            stack.pop();
            Token res(Token::Type::Number, ShuntingYard::calcFunc(bottom, tokenQueue.front(), top));
            tokenQueue.dequeue();
            stack.push(res);
        } else if (tokenQueue.front().type() == Token::Type::Number) {
            stack.push(tokenQueue.front());
            tokenQueue.dequeue();
        } else throw std::invalid_argument("Incorrect ParenthesesToken");
    }
    res = std::stod(stack.top().value());

    return res;
}
