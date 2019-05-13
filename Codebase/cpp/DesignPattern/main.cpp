#include <iostream>
//#include "Prototype.h"
//#include "Singleton.h"
//#include "Factory.h"
//#include "AbstractFactory.h"
//#include "Builder.h"

using namespace std;

int main()
{
//    /* Factory Pattern */
//    ShapeFactory shapeFactory;
//    Shape* shape = shapeFactory.GetShape("Circle");
//    cout << shape->draw() << endl;

//    /* AbstractFactory Pattern */
//    FactoryProducer factoryProducer;
//    AbstractFactory* abstractFactory = factoryProducer.GetFactory("ColorFactory");
//    Color* color = abstractFactory->GetColor("Blue");
//    cout << color->fill() << endl;

//    /* Singleton Pattern */
//    SingletonLazy singletonPattern = SingletonLazy::GetInstance();
//    singletonPattern.showMessage();
//
//    SingletonHungry singletonHungry = SingletonHungry::GetInstance();
//    singletonHungry.showMessage();

//    /* Builder Pattern */
//    MealBuilder mealBuilder;
//    Meal vegMeal = mealBuilder.PrepareVegMeal();
//    vegMeal.ShowItems();
//    cout << "Total Cost: " << vegMeal.GetCost() << endl;

//    /* Prototype Pattern*/
//    Base* obj1 = new Derived(); // 基类指针指向派生类对象，触发虚机制
//    obj1->Show(); // 调用派生类虚函数，输出Derived
//    Base* obj2 = obj1->Clone(); // 使用原型模式拷贝对象，返回的是指针，也是基类指针指向派生类对象，也会触发虚机制
//    obj2->Show(); // 调用派生类虚函数，输出Derived
//    Base obj3(*obj1); // 直接使用拷贝构造函数，返回的是类对象，不是指针或者引用，不会触发虚机制
//    obj3.Show(); // 没有虚机制触发，调用的函数还是Base的Show函数，输出Base



    return 0;
}