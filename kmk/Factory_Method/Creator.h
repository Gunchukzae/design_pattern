#pragma once
#include "Product.h"
#include <memory>

// Abstract Creator
class Creator {
public:
    virtual ~Creator() = default;
    
    // Factory Method
    virtual std::unique_ptr<Product> createProduct() = 0;
    
    // 템플릿 메소드 - 팩토리 메소드를 사용하는 operation
    void someOperation() {
        auto product = createProduct();
        product->use();
    }
};

// Concrete Creator A
class ConcreteCreatorA : public Creator {
public:
    std::unique_ptr<Product> createProduct() override {
        return std::make_unique<ConcreteProductA>();
    }
};

// Concrete Creator B
class ConcreteCreatorB : public Creator {
public:
    std::unique_ptr<Product> createProduct() override {
        return std::make_unique<ConcreteProductB>();
    }
};
