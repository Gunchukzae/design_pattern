#include <iostream>
using namespace std;

// =======================
// Abstract Class: 커피 템플릿
// =======================
class AbstractCoffee {
public:
    // 템플릿 메서드: 알고리즘 골격 정의
    void MakeCoffee() const {

        /*
		1, (Default) 물을 끓인다.
		2. (Default) 커피를 추출한다.
		3. (Abstract) 컵에 붓는다.
		4. (Hook/Default) 설탕을 추가한다. (선택 사항)
		5. (Hook/Default) 우유를 추가한다. (선택 사항)
		6. (Hook) 시럽을 추가한다. (선택 사항)
		7. (Default) 커피를 제공한다.
        */
        Serve();            // 기본 구현(Default)
        BoilWater();        // 기본 구현 단계(Default)
        BrewCoffee();       // 추상 단계(Abstract)
        PourInCup();        // 기본 구현 단계(Default)
        AddSugar();         // 훅(Hook) 또는 기본 구현(Default)
        AddMilk();          // 훅(Hook) 또는 기본 구현(Default)
        AddFlavor();        // 훅(Hook)
        Serve();            // 기본 구현(Default)
    }

protected:
    // =======================
    // 기본 구현 단계(Default)
    // =======================
    void BoilWater() const {
        cout << "물 끓이는 중..." << endl;
    }

    void PourInCup() const {
        cout << "컵에 커피 붓는 중..." << endl;
    }

    void Serve() const {
        cout << "커피 제공 완료!" << endl;
    }


    // =======================
    // 추상 단계(Abstract)
    // =======================
    virtual void BrewCoffee() const = 0;


    // =======================
    // 훅(Hook): 선택적 단계
    // =======================
    virtual void AddSugar() const {
        cout << "설탕 추가 안함" << endl;
    }

    virtual void AddMilk() const {
        cout << "우유 추가 안함" << endl;
    }

    virtual void AddFlavor() const {
        // 기본 빈 훅
    }

    virtual ~AbstractCoffee() {}
};

// =======================
// Concrete Class: Espresso
// =======================
class Espresso : public AbstractCoffee {
protected:
    void BrewCoffee() const override {
        cout << "Espresso: 원두 추출 (강하게)" << endl;
    }

    void AddSugar() const override {
        cout << "설탕 1스푼 추가" << endl;
    }
};

// =======================
// Concrete Class: Latte
// =======================
class Latte : public AbstractCoffee {
protected:
    void BrewCoffee() const override {
        cout << "Latte: 원두 추출 및 스팀 우유 추가" << endl;
    }

    void AddMilk() const override {
        cout << "우유 추가 (스팀 처리 완료)" << endl;
    }

    void AddFlavor() const override {
        cout << "바닐라 시럽 추가" << endl;
    }
};

// =======================
// Concrete Class: Mocha
// =======================
class Mocha : public AbstractCoffee {
protected:
    void BrewCoffee() const override {
        cout << "Mocha: 원두 추출" << endl;
    }

    void AddMilk() const override {
        cout << "우유 추가" << endl;
    }

    void AddFlavor() const override {
        cout << "초콜릿 시럽 추가" << endl;
    }

    void AddSugar() const override {
        cout << "설탕 1스푼 추가" << endl;
    }

};

// =======================
// Client Code
// =======================
void ClientCode(const AbstractCoffee* coffee) {
    coffee->MakeCoffee();
}


// -------------------
// 클라이언트 코드
// -------------------
void TemplateMethodPattern() {

    cout << "템플릿 메서드 단계 순서:\n";
    cout << "1. (Default) 물을 끓인다.\n";
    cout << "2. (Default) 커피를 추출한다.\n";
    cout << "3. (Abstract) 컵에 붓는다.\n";
    cout << "4. (Hook/Default) 설탕을 추가한다. (선택 사항)\n";
    cout << "5. (Hook/Default) 우유를 추가한다. (선택 사항)\n";
    cout << "6. (Hook) 시럽을 추가한다. (선택 사항)\n";
    cout << "7. (Default) 커피를 제공한다.\n\n";


    cout << "Espresso making:\n";
    AbstractCoffee* espresso = new Espresso();
    ClientCode(espresso);
    cout << "\n";

    cout << "Latte making:\n";
    AbstractCoffee* latte = new Latte();
    ClientCode(latte);
    cout << "\n";

    cout << "Mocha making:\n";
    AbstractCoffee* mocha = new Mocha();
    ClientCode(mocha);
    cout << "\n";

    /*delete espresso;
    delete latte;
    delete mocha;*/

    return;
}
