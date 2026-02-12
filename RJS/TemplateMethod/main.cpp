#include <vector>

#include "Americano.h"
#include "BeverageRecipe.h"
#include "CafeLatte.h"
#include "MatchaLatte.h"

int main() {
    std::vector<BeverageRecipe*> menu;

    std::cout << "=== 오늘의 주문 들어갑니다 ===\n"<<std::endl;

    menu.push_back(new Americano());
    menu.push_back(new CafeLatte());
    menu.push_back(new MatchaLatte());

    for (BeverageRecipe* drink : menu) {
        drink->makeBeverage();
        std::cout << std::endl;
    }

    for (BeverageRecipe* drink : menu) {
        delete drink;
    }

    return 0;
}