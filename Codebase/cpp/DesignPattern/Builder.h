//
// Created by zhangqianyi on 2017/7/6.
//

#ifndef DESIGNPATTERN_BUILDER_H
#define DESIGNPATTERN_BUILDER_H

#include <iostream>
#include <vector>
using namespace std;

/**
 * @author zhangqianyi
 * @date 2017/7/6
 * @brief 考虑实现一个建造者模式
我们假设一个快餐店的商业案例：
一个典型的套餐可以是一个汉堡和一杯冷饮。
汉堡可以是素食汉堡或鸡肉汉堡，它们是包在纸盒中；冷饮可以是可口可乐或百事可乐，它们是装在瓶子中。

可以分析出如下关系：由底向上分析
纸盒、瓶子继承打包方式；素食汉堡、鸡肉汉堡继承汉堡；可口可乐、百事可乐继承冷饮；汉堡和冷饮中有一个打包方式的组合形式；汉堡和冷饮继承食物；

上述的这些都是Builder，负责创建对象。然后在创建一个MealBuilder类来将这些对象组合起来
 */

class Packing {
public:
    virtual string Pack() = 0;
};
class Item {
public:
    virtual string Name() = 0;
    virtual Packing* Pack() = 0;
    virtual float Price() = 0;
};


class Meal {
public:
    void AddItem(Item* item) { m_item.push_back(item); }
    float GetCost() {
        float cost = 0;
        for (unsigned int i = 0; i < m_item.size(); ++i) {
            cost += m_item[i]->Price();
        }
        return cost;
    }
    void ShowItems() {
        for (unsigned int i = 0; i < m_item.size(); ++i) {
            cout << "Item : " << m_item[i]->Name() << "\t";
            cout << "Packing : " << m_item[i]->Pack()->Pack() << "\t";
            cout << "Price : " << m_item[i]->Price() << endl;
        }
    }

private:
    vector<Item*> m_item;
};

class MealBuilder {
public:
    Meal PrepareVegMeal ();
    Meal PrepareNonVegMeal();
};

#endif //DESIGNPATTERN_BUILDER_H
