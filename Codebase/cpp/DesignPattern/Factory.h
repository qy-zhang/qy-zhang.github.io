//
// Created by zhangqianyi on 2017/7/6.
//

#ifndef DESIGNPATTERN_FACTORY_H
#define DESIGNPATTERN_FACTORY_H

#include <iostream>

/**
 * @author zhangqianyi
 * @date 2017/7/6
 * @brief
 */
class Shape {
public:
    virtual std::string draw() = 0;
};

/**
 * @author zhangqianyi
 * @date 2017/7/6
 * @brief 工厂方法模式的公共接口，作为一个工厂来实例化不同的对象
 */
class ShapeFactory {
public:
    Shape* GetShape(std::string shapeType);
};


#endif //DESIGNPATTERN_FACTORY_H
