//
// Created by zhangqianyi on 2017/7/6.
//

#include "Factory.h"

/**
 * @author zhangqianyi
 * @date 2017/7/6
 * @brief 一些类对象的具体定义实现，放到cpp文件里面，不会暴露给外部
 */
class Rectangle : public Shape{
public:
    std::string draw() { return "Rectangle::draw()"; }
};

class Square : public Shape{
public:
    std::string draw() { return "Square::draw()"; }
};

class Circle : public Shape{
public:
    std::string draw() { return "Circle::draw()"; }
};

/**
 * @author zhangqianyi
 * @date 2017/7/6
 * @brief 实现工厂产生对象的方法，一个工厂根据不同的需求来生产不同的对象
 */
Shape* ShapeFactory::GetShape(std::string shapeType) {
    if (shapeType.empty()) return NULL;
    if (shapeType == "Rectangle") {
        return new Rectangle();
    } else if (shapeType == "Square") {
        return new Square();
    } else if (shapeType == "Circle") {
        return new Circle();
    }
    return NULL;
}