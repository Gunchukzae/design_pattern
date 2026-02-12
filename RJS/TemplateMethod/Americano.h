#pragma once
#include "BeverageRecipe.h"

class Americano : public BeverageRecipe
{
protected:
    void addMainIngredient() override;
    void pourLiquid() override;
    void addToppings() override;
};

