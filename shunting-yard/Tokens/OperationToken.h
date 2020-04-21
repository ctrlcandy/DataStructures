#ifndef OPERATIONTOKEN_H
#define OPERATIONTOKEN_H


#include <cstring>
#include "AbstractToken.h"

class OperationToken : public AbstractToken  {
public:
    OperationToken() {};
    explicit OperationToken(const char* value) : AbstractToken(value) {};

    const char* name() const override { return "OperationToken"; };

    ~OperationToken() {};
};


#endif //OPERATIONTOKEN_H
