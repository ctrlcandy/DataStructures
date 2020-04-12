#include <iostream>
#include "MyVector.h"

int main() {
    std::cout << "!--- RESIZESTRATEGY::Additive ---!" << std::endl;
    MyVector vectorFirst(10, ResizeStrategy::Additive, 2);
    std::cout << "---Constructor---" << std::endl;
    std::cout << "Expected size and capacity: " << 10 << " " << 12 << std::endl;
    std::cout << "Received size and capacity: " << vectorFirst.size() << " " << vectorFirst.capacity() << std::endl;

    for (int i = 0; i < vectorFirst.size(); ++i) {
        vectorFirst[i] = i;
    }
    std::cout << "---Initialization---" << std::endl;
    std::cout << "Expected: " <<  "0 1 2 3 4 5 6 7 8 9" << std::endl;
    std::cout << "Received: ";
    for (size_t i : vectorFirst)
        std::cout << i << " ";
    std::cout << std::endl;

    vectorFirst.resize(100, 5);
    std::cout << "---Resize (bigger than size)---" << std::endl;
    std::cout << "Expected size and capacity: " << 100 << " " << 102 << std::endl;
    std::cout << "Received size and capacity: " << vectorFirst.size() << " " << vectorFirst.capacity() << std::endl;

    vectorFirst.resize(15, 0);
    std::cout << "---Resize (smaller than size)---" << std::endl;
    std::cout << "Expected size and capacity: " << 15 << " " << 17 << std::endl;
    std::cout << "Received size and capacity: " << vectorFirst.size() << " " << vectorFirst.capacity() << std::endl;

    std::cout << "---Initialization in resize---" << std::endl;
    std::cout << "Expected: " <<  "0 1 2 3 4 5 6 7 8 9 5 5 5 5 5" << std::endl;
    std::cout << "Received: ";
    for (size_t i : vectorFirst)
        std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "---Copy constructor---" << std::endl;
    MyVector v1(vectorFirst);
    std::cout << "Expected: " <<  "0 1 2 3 4 5 6 7 8 9 5 5 5 5 5" << std::endl;
    std::cout << "Received: ";
    for (size_t i : v1)
        std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "---Operator =---" << std::endl;
    MyVector v3 = vectorFirst;
    std::cout << "Expected: " <<  "0 1 2 3 4 5 6 7 8 9 5 5 5 5 5" << std::endl;
    std::cout << "Received: ";
    for (size_t i : v1)
        std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "---Push back & pop back---" << std::endl;
    vectorFirst.pushBack(4);
    vectorFirst.popBack();
    vectorFirst.pushBack(3);
    vectorFirst.pushBack(2);
    vectorFirst.popBack();
    vectorFirst.popBack();
    vectorFirst.pushBack(1);
    vectorFirst.pushBack(0);
    std::cout << "Expected: " <<  "0 1 2 3 4 5 6 7 8 9 5 5 5 5 5 1 0" << std::endl;
    std::cout << "Received: ";
    for (size_t i : vectorFirst)
        std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "---Erase (const size_t i)---" << std::endl;
    vectorFirst.erase(10);
    std::cout << "Expected: " <<  "0 1 2 3 4 5 6 7 8 9 5 5 5 5 1 0" << std::endl;
    std::cout << "Received: ";
    for (size_t i : vectorFirst)
        std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "---Erase (const size_t i, const size_t len)---" << std::endl;
    vectorFirst.erase(10, 5);
    std::cout << "Expected: " <<  "0 1 2 3 4 5 6 7 8 9 0" << std::endl;
    std::cout << "Received: ";
    for (size_t i : vectorFirst)
        std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "---find(isBegin = true)---" << std::endl;
    std::cout << "Expected: " <<  0 << std::endl;
    std::cout << "Received: " << vectorFirst.find(0) << std::endl;

    std::cout << "---find(isBegin = false)---" << std::endl;
    std::cout << "Expected: " <<  10 << std::endl;
    std::cout << "Received: " << vectorFirst.find(0, false) << std::endl;



    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "!--- RESIZESTRATEGY::Multiplicative ---!" << std::endl;
    MyVector vectorSecond(10, ResizeStrategy::Multiplicative, 2);
    std::cout << "---Constructor---" << std::endl;
    std::cout << "Expected size and capacity: " << 10 << " " << 20 << std::endl;
    std::cout << "Received size and capacity: " << vectorSecond.size() << " " << vectorSecond.capacity() << std::endl;

    for (int i = 0; i < vectorSecond.size(); ++i) {
        vectorSecond[i] = i;
    }
    std::cout << "---Initialization---" << std::endl;
    std::cout << "Expected: " <<  "0 1 2 3 4 5 6 7 8 9" << std::endl;
    std::cout << "Received: ";
    for (size_t i : vectorSecond)
        std::cout << i << " ";
    std::cout << std::endl;

    vectorSecond.resize(2, 0);
    std::cout << "---Resize (smaller than size)---" << std::endl;
    std::cout << "Expected size and capacity: " << 2 << " " << " 4 <= cap < 20" << std::endl;
    std::cout << "Received size and capacity: " << vectorSecond.size() << " " << vectorSecond.capacity() << std::endl;

    vectorSecond.resize(10, 7);
    std::cout << "---Resize (bigger than size)---" << std::endl;
    std::cout << "Expected size and capacity: " << 10 << " " << " 10 <= cap < 20" << std::endl;
    std::cout << "Received size and capacity: " << vectorSecond.size() << " " << vectorSecond.capacity() << std::endl;

    std::cout << "---Initialization in resize---" << std::endl;
    std::cout << "Expected: " <<  "0 1 7 7 7 7 7 7 7 7" << std::endl;
    std::cout << "Received: ";
    for (size_t i : vectorSecond)
        std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "---Copy constructor---" << std::endl;
    MyVector v2(vectorSecond);
    std::cout << "Expected: " <<  "0 1 7 7 7 7 7 7 7 7" << std::endl;
    std::cout << "Received: ";
    for (size_t i : v2)
        std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "---Operator =---" << std::endl;
    MyVector v4 = vectorSecond;
    std::cout << "Expected: " <<  "0 1 7 7 7 7 7 7 7 7" << std::endl;
    std::cout << "Received: ";
    for (size_t i : v2)
        std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "---Push back & pop back---" << std::endl;
    vectorSecond.pushBack(4);
    vectorSecond.popBack();
    vectorSecond.pushBack(3);
    vectorSecond.pushBack(2);
    vectorSecond.popBack();
    vectorSecond.popBack();
    vectorSecond.pushBack(1);
    vectorSecond.pushBack(0);
    std::cout << "Expected: " <<  "0 1 7 7 7 7 7 7 7 7 1 0" << std::endl;
    std::cout << "Received: ";
    for (size_t i : vectorSecond)
        std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "---Erase (const size_t i)---" << std::endl;
    vectorSecond.erase(10);
    std::cout << "Expected: " <<  "0 1 7 7 7 7 7 7 7 7 0" << std::endl;
    std::cout << "Received: ";
    for (size_t i : vectorSecond)
        std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "---Erase (const size_t i, const size_t len)---" << std::endl;
    vectorSecond.erase(2, 8);
    std::cout << "Expected: " <<  "0 1 0" << std::endl;
    std::cout << "Received: ";
    for (size_t i : vectorSecond)
        std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "---find(isBegin = true)---" << std::endl;
    std::cout << "Expected: " <<  0 << std::endl;
    std::cout << "Received: " << vectorSecond.find(0) << std::endl;

    std::cout << "---find(isBegin = false)---" << std::endl;
    std::cout << "Expected: " <<  2 << std::endl;
    std::cout << "Received: " << vectorSecond.find(0, false) << std::endl;


    return 0;
}
