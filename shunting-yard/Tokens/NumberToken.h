#ifndef NUMBERTOKEN_H
#define NUMBERTOKEN_H


#include <cstddef>
#include "AbstractToken.h"

class NumberToken : public AbstractToken {
public:
    NumberToken(){};
    explicit NumberToken(const char* value) : AbstractToken(value) {};

    const char* name() const override { return "NumberToken"; };

    ~NumberToken(){};
};


#endif //NUMBERTOKEN_H
