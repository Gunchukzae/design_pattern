#include <iostream>
#include "Creator.h"

int main() {
    std::cout << "=== Factory Method Pattern Example ===" << std::endl;
    
    // Creator A를 사용하여 Product A 생성
    std::unique_ptr<Creator> creatorA = std::make_unique<ConcreteCreatorA>();
    auto productA = creatorA->createProduct();
    std::cout << "Created: " << productA->getName() << std::endl;
    productA->use();
    
    std::cout << std::endl;
    
    // Creator B를 사용하여 Product B 생성
    std::unique_ptr<Creator> creatorB = std::make_unique<ConcreteCreatorB>();
    auto productB = creatorB->createProduct();
    std::cout << "Created: " << productB->getName() << std::endl;
    productB->use();
    
    std::cout << std::endl;
    
    // 템플릿 메소드 사용 예시
    std::cout << "Using template method:" << std::endl;
    creatorA->someOperation();
    creatorB->someOperation();
    
    return 0;
}
