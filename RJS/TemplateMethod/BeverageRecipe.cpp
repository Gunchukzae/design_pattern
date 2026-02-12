#include "BeverageRecipe.h"

void BeverageRecipe::makeBeverage() {
    prepareCup();
    addMainIngredient();
    pourLiquid();

    if (customerWantsSyrup()) {
        addSyrup();
    }

    addToppings();
    serve();
}

void BeverageRecipe::prepareCup() {
    std::cout << "컵을 깨끗이 닦아 준비합니다." << std::endl;
}

void BeverageRecipe::serve() {
    std::cout << "고객님께 음료를 전달합니다." << std::endl;
}

void BeverageRecipe::addSyrup() {
    std::cout << "[추가] 달콤한 시럽을 넣습니다." << std::endl;
}