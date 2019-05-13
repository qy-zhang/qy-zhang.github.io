//
// Created by zhangqianyi on 2017/7/6.
//

#ifndef DESIGNPATTERN_PROTOTYPE_H
#define DESIGNPATTERN_PROTOTYPE_H

#include <iostream>
using namespace std;

class Base {
public:
    virtual Base* Clone() { return new Base(*this); }
    virtual void Show() { cout << "Base" << endl; }
};

class Derived : public Base {
public:
    virtual Base* Clone() { return new Derived(*this); }
    virtual void Show() { cout << "Derived" << endl; }
};

#endif //DESIGNPATTERN_PROTOTYPE_H
