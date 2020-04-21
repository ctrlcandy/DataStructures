#ifndef PARENTHESESTOKEN_H
#define PARENTHESESTOKEN_H


#include <cstddef>
#include "AbstractToken.h"

class ParenthesesToken : public AbstractToken {
public:
    ParenthesesToken(){};
    explicit ParenthesesToken(const char* value): AbstractToken(value){};

    const char* name() const override { return "ParenthesesToken"; };

    ~ParenthesesToken(){};
};


#endif //PARENTHESESTOKEN_H
