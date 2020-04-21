#ifndef ABSTRACTTOKEN_H
#define ABSTRACTTOKEN_H


class AbstractToken {
public:
    AbstractToken() {};
    AbstractToken(const char* value) : _value(value) {};

    virtual const char* name() const { return "AbstractToken"; };

    const char* value() const { return _value; };

    ~AbstractToken() {};
private:
    const char* _value;
};


#endif //ABSTRACTTOKEN_H
