//
// Created by zhangqianyi on 2017/7/6.
//

#include "Builder.h"

class Wrapper : public Packing {
public:
    string Pack() { return "Wapper"; }
};

class Bottle : public Packing {
public:
    string Pack() { return "Bottle"; }
};


class Burger : public Item {
public:
    Packing* Pack() { return new Wrapper; }
    virtual float Price() = 0;
};

class VegBuger : public Burger {
public:
    float Price() { return 25; }
    string Name() { return "Veg Burger"; }
};

class ChickenBuger : public Burger {
public:
    float Price() { return 50; }
    string Name() { return "Chicken Burger"; }
};


class ColdDrink : public Item {
public:
    Packing* Pack() { return new Bottle; }
    virtual float Price() = 0;
};

class Coke : public ColdDrink {
public:
    float Price() { return 20; }
    string Name() { return "Coke"; }
};

class Pepsi : public ColdDrink {
public:
    float Price() { return 15; }
    string Name() { return "Pepsi"; }
};


Meal MealBuilder::PrepareVegMeal () {
    Meal meal;
    meal.AddItem(new VegBuger());
    meal.AddItem(new Coke());
    return meal;
}
Meal MealBuilder::PrepareNonVegMeal() {
    Meal meal;
    meal.AddItem(new ChickenBuger());
    meal.AddItem(new Pepsi());
    return meal;
}