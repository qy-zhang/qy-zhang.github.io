//
// Created by zhangqianyi on 2017/7/6.
//

#include "AbstractFactory.h"

// 形状
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

// 颜色
class Red : public Color{
public:
    std::string fill() { return "Red::draw()"; }
};
class Green : public Color{
public:
    std::string fill() { return "Green::draw()"; }
};
class Blue : public Color{
public:
    std::string fill() { return "Blue::draw()"; }
};

// 抽象工厂
class ShapeFactory2 : public AbstractFactory {
public:
    Shape* GetShape(std::string shapeType) {
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
    Color* GetColor(std::string colorType) {
        return NULL;
    }
};

class ColorFactory : public AbstractFactory {
public:
    Shape* GetShape(std::string shapeType) {
        return NULL;
    }
    Color* GetColor(std::string colorType) {
        if (colorType.empty()) return NULL;
        if (colorType == "Red") {
            return new Red();
        } else if (colorType == "Green") {
            return new Green();
        } else if (colorType == "Blue") {
            return new Blue();
        }
        return NULL;
    }
};

/**
 * @author zhangqianyi
 * @date 2017/7/6
 * @brief 创建不同的工厂
 */
AbstractFactory* FactoryProducer::GetFactory(std::string factoryType) {
    if (factoryType == "ShapeFactory") {
        return new ShapeFactory2();
    } else if (factoryType == "ColorFactory") {
        return new ColorFactory();
    }
    return NULL;
}