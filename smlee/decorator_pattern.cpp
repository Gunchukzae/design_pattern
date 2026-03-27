#include <iostream>
#include <string>

/**
 * 컴포넌트 인터페이스
 * → 모든 커피가 가져야 하는 기능
 */
class Coffee {
public:
    virtual ~Coffee() {}

    virtual std::string getDescription() const = 0;
    virtual int cost() const = 0;
};

/**
 * 기본 커피 (아메리카노)
 */
class Americano : public Coffee {
public:
    std::string getDescription() const override {
        return "아메리카노";
    }

    int cost() const override {
        return 3000;
    }
};

/**
 * 데코레이터 기본 클래스
 */
class CoffeeDecorator : public Coffee {
protected:
    Coffee* coffee_; // 감싸는 객체

public:
    CoffeeDecorator(Coffee* coffee) : coffee_(coffee) {}
};

/**
 * 우유 추가
 */
class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(Coffee* coffee) : CoffeeDecorator(coffee) {}

    std::string getDescription() const override {
        return coffee_->getDescription() + " + 우유";
    }

    int cost() const override {
        return coffee_->cost() + 500;
    }
};

/**
 * 샷 추가
 */
class ShotDecorator : public CoffeeDecorator {
public:
    ShotDecorator(Coffee* coffee) : CoffeeDecorator(coffee) {}

    std::string getDescription() const override {
        return coffee_->getDescription() + " + 샷";
    }

    int cost() const override {
        return coffee_->cost() + 1000;
    }
};

/**
 * 클라이언트 코드
 */
void PrintOrder(const Coffee* coffee) {
    std::cout << "주문: " << coffee->getDescription() << "\n";
    std::cout << "가격: " << coffee->cost() << "원\n\n";
}

int main() {

    /**
     * 기본 커피
     */
    Coffee* coffee = new Americano;
    PrintOrder(coffee);

    /**
     * 우유 추가
     */
    coffee = new MilkDecorator(coffee);
    PrintOrder(coffee);

    /**
     * 샷 추가
     */
    coffee = new ShotDecorator(coffee);
    PrintOrder(coffee);

    /**
     * 또 우유 추가 (중첩 가능!)
     */
    coffee = new MilkDecorator(coffee);
    PrintOrder(coffee);

    /**
     * 결과:
     * 아메리카노 + 우유 + 샷 + 우유
     */

    return 0;
}