#pragma once
#include "BeverageRecipe.h"

class MatchaLatte: public BeverageRecipe
{
protected:
    void addMainIngredient() override;
    void pourLiquid() override;
    void addToppings() override;
};

