#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token {
public:
    enum class Type {
        Number,
        Operator,
        LeftParen,
        RightParen,
        None,
    };

    Token() : _type(Type::None), _value("\0") {};
    Token(Type type, std::string value) : _type(type), _value(value) {};

    Type type() const { return _type; };

    std::string value() const { return _value; };

    ~Token() {};

private:
    Type _type;
    std::string _value;
};

#endif //TOKEN_H