#pragma once
#include "BeverageRecipe.h"

class CafeLatte : public BeverageRecipe
{
protected:
    void addMainIngredient() override;
    void pourLiquid() override;
    void addToppings() override;
    bool customerWantsSyrup() override;
};

