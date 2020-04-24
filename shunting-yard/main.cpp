#include <iostream>
#include <vector>
#include "ShuntingYard.h"

int main() {
    MyVector res;
    Queue lastres;
    ShuntingYard s;
    res = s.tokenize("(5* 4+3* 2)-1");
    //std::cout << res[0]->value() << std::endl;
    //lastres = ShuntingYard::shuntingYard(res);
    //std::cout << s.calc(lastres) << std::endl;
    return 0;
}
