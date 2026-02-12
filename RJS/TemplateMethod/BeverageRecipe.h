#pragma once
#include <iostream>

using namespace std;

class BeverageRecipe {
public:
    virtual ~BeverageRecipe() {}

    void makeBeverage();

private:
    void prepareCup();
    void serve();
    void addSyrup();

protected:
    virtual void addMainIngredient() = 0;
    virtual void pourLiquid() = 0;
    virtual void addToppings() = 0;

    virtual bool customerWantsSyrup() {
        return false;
    }
};

