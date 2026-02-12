#include "CafeLatte.h"

void CafeLatte::addMainIngredient() {
    std::cout << "진한 에스프레소 1샷을 넣습니다." << std::endl;
}

void CafeLatte::pourLiquid() {
    std::cout << "부드러운 스팀 우유를 붓습니다." << std::endl;
}

void CafeLatte::addToppings() {
    std::cout << "우유 거품을 얇게 올립니다." << std::endl;
}

bool CafeLatte::customerWantsSyrup() {
    return true;
}
