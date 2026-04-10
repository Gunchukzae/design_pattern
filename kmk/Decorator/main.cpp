#include <iostream>
#include <string>
using namespace std;

// ============================================================
// Component: 피자 추상 클래스
// ============================================================
class Pizza {
public:
    virtual string getDescription() = 0;
    virtual int getPrice() = 0;
    virtual ~Pizza() {}
};

// ============================================================
// ConcreteComponent: 기본 도우 (핵심 객체)
// ============================================================
class ThinCrust : public Pizza {
public:
    string getDescription() override { return "씬 크러스트"; }
    int getPrice() override { return 8000; }
};

class ThickCrust : public Pizza {
public:
    string getDescription() override { return "두꺼운 크러스트"; }
    int getPrice() override { return 9000; }
};

// ============================================================
// Decorator: 토핑 추상 클래스
// Pizza를 상속하면서, Pizza를 멤버로 보유 (이중 관계)
// ============================================================
class ToppingDecorator : public Pizza {
protected:
    Pizza* pizza;  // 감싸는 대상
public:
    ToppingDecorator(Pizza* pizza) : pizza(pizza) {}
    ~ToppingDecorator() { delete pizza; }
};

// ============================================================
// ConcreteDecorator: 구체 토핑들
// ============================================================
class Cheese : public ToppingDecorator {
public:
    Cheese(Pizza* pizza) : ToppingDecorator(pizza) {}

    string getDescription() override {
        return pizza->getDescription() + ", 치즈";
    }
    int getPrice() override {
        return pizza->getPrice() + 1500;
    }
};

class Pepperoni : public ToppingDecorator {
public:
    Pepperoni(Pizza* pizza) : ToppingDecorator(pizza) {}

    string getDescription() override {
        return pizza->getDescription() + ", 페페로니";
    }
    int getPrice() override {
        return pizza->getPrice() + 2000;
    }
};

class Mushroom : public ToppingDecorator {
public:
    Mushroom(Pizza* pizza) : ToppingDecorator(pizza) {}

    string getDescription() override {
        return pizza->getDescription() + ", 버섯";
    }
    int getPrice() override {
        return pizza->getPrice() + 1000;
    }
};

class Olive : public ToppingDecorator {
public:
    Olive(Pizza* pizza) : ToppingDecorator(pizza) {}

    string getDescription() override {
        return pizza->getDescription() + ", 올리브";
    }
    int getPrice() override {
        return pizza->getPrice() + 800;
    }
};

// ============================================================
// 주문 출력 헬퍼
// ============================================================
void printOrder(Pizza* pizza) {
    cout << "구성: " << pizza->getDescription() << endl;
    cout << "가격: " << pizza->getPrice() << "원" << endl;
}

// ============================================================
// main: 피자 주문
// ============================================================
int main() {
    cout << "=== Decorator 패턴 - 피자 주문 ===" << endl << endl;

    // 주문 1: 씬 크러스트 + 치즈
    // 래핑 구조: Cheese -> ThinCrust
    cout << "[주문 1] 씬 크러스트 + 치즈" << endl;
    Pizza* order1 = new Cheese(
        new ThinCrust()
    );
    printOrder(order1);
    delete order1;

    cout << endl;

    // 주문 2: 두꺼운 크러스트 + 치즈 + 페페로니 + 버섯
    // 래핑 구조: Mushroom -> Pepperoni -> Cheese -> ThickCrust
    cout << "[주문 2] 두꺼운 크러스트 + 치즈 + 페페로니 + 버섯" << endl;
    Pizza* order2 = new Mushroom(
        new Pepperoni(
            new Cheese(
                new ThickCrust()
            )
        )
    );
    printOrder(order2);
    delete order2;

    cout << endl;

    // 주문 3: 씬 크러스트 + 치즈 두 장 + 올리브
    // 동일한 데코레이터를 중복 적용 가능
    cout << "[주문 3] 씬 크러스트 + 치즈 두 장 + 올리브" << endl;
    Pizza* order3 = new Olive(
        new Cheese(
            new Cheese(
                new ThinCrust()
            )
        )
    );
    printOrder(order3);
    delete order3;

    cout << endl;

    // 주문 4: 런타임에 동적으로 토핑 추가
    cout << "[주문 4] 런타임 동적 주문" << endl;
    Pizza* order4 = new ThickCrust();
    cout << "도우만: " << order4->getPrice() << "원" << endl;

    order4 = new Cheese(order4);
    cout << "치즈 추가: " << order4->getPrice() << "원" << endl;

    order4 = new Pepperoni(order4);
    cout << "페페로니 추가: " << order4->getPrice() << "원" << endl;

    order4 = new Mushroom(order4);
    cout << "버섯 추가: " << order4->getPrice() << "원" << endl;

    cout << "최종 -> ";
    printOrder(order4);
    delete order4;

    return 0;
}
