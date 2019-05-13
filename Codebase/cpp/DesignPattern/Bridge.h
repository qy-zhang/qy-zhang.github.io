//
// Created by zhangqianyi on 2017/7/7.
//

#ifndef DESIGNPATTERN_BRIDGE_H
#define DESIGNPATTERN_BRIDGE_H

#include <iostream>

class DrawAPI {
public:
    virtual void DrawCircle(int radius, int x, int y) = 0;
};

class RedCircle : public DrawAPI {
public:
    void DrawCircle(int radius, int x, int y) {
        std::cout << "Drawing Circle[ color: red, radius: " << radius << ", x: " << x << ", y: " << y << "]" << std::endl;
    }
};

class GreenCircle : public DrawAPI {
public:
    void DrawCircle(int radius, int x, int y) {
        std::cout << "Drawing Circle[ color: green, radius: " << radius << ", x: " << x << ", y: " << y << "]" << std::endl;
    }
};

class Shape {
public:
    virtual void Draw() = 0;

protected:
    Shape(DrawAPI drawAPI1) : drawAPI(drawAPI1) {}
    DrawAPI drawAPI;
};

class Circle : public Shape {
public:
    Circle(int x, int y, int radius, DrawAPI drawAPI) : m_x(x), m_y(y), m_radius(radius), Shape(drawAPI) {}
    void Draw() {
        drawAPI.DrawCircle(m_radius, m_x, m_y);
    }
private:
    int m_radius;
    int m_x;
    int m_y;
};


#endif //DESIGNPATTERN_BRIDGE_H
