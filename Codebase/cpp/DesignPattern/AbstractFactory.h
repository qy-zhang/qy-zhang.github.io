//
// Created by zhangqianyi on 2017/7/6.
//

#ifndef DESIGNPATTERN_ABSTRACTFACTORY_H
#define DESIGNPATTERN_ABSTRACTFACTORY_H

#include <iostream>

class Shape {
public:
    virtual std::string draw() = 0;
};
class Color {
public:
    virtual std::string fill() = 0;
};

/**
 * @author zhangqianyi
 * @date 2017/7/6
 * @brief 抽象工厂，是一个超级工厂，能够创建颜色和形状工厂，
 */
class AbstractFactory {
public:
    virtual Shape* GetShape(std::string shapeType) = 0;
    virtual Color* GetColor(std::string colorType) = 0;
};

class FactoryProducer {
public:
    AbstractFactory* GetFactory(std::string factoryType);
};

#endif //DESIGNPATTERN_ABSTRACTFACTORY_H
