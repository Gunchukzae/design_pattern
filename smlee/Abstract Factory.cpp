#include <iostream>
using namespace std;


class Burger {
public:
    virtual void Make() = 0;
    virtual ~Burger() {}
};

class Fries {
public:
    virtual void Fry() = 0;
    virtual ~Fries() {}
};

class Drink {
public:
    virtual void Pour() = 0;
    virtual ~Drink() {}
};



class McBurger : public Burger {
public:
    void Make() override {
        cout << "맥도날드 버거 제작" << endl;
    }
};

class McFries : public Fries {
public:
    void Fry() override {
        cout << "맥도날드 감자튀김" << endl;
    }
};

class McDrink : public Drink {
public:
    void Pour() override {
        cout << "맥도날드 콜라" << endl;
    }
};


class LotteBurger : public Burger {
public:
    void Make() override {
        cout << "롯데리아 버거 제작" << endl;
    }
};

class LotteFries : public Fries {
public:
    void Fry() override {
        cout << "롯데리아 감자튀김" << endl;
    }
};

class LotteDrink : public Drink {
public:
    void Pour() override {
        cout << "롯데리아 콜라" << endl;
    }
};


class FastFoodFactory {
public:
    virtual Burger* CreateBurger() = 0;
    virtual Fries* CreateFries() = 0;
    virtual Drink* CreateDrink() = 0;
    virtual ~FastFoodFactory() {}
};


class McFactory : public FastFoodFactory {
public:
    Burger* CreateBurger() override { return new McBurger(); }
    Fries* CreateFries() override { return new McFries(); }
    Drink* CreateDrink() override { return new McDrink(); }
};

class LotteFactory : public FastFoodFactory {
public:
    Burger* CreateBurger() override { return new LotteBurger(); }
    Fries* CreateFries() override { return new LotteFries(); }
    Drink* CreateDrink() override { return new LotteDrink(); }
};


class SetMenu {
private:
    Burger* burger;
    Fries* fries;
    Drink* drink;

public:
    SetMenu(FastFoodFactory* factory) {
        burger = factory->CreateBurger();
        fries = factory->CreateFries();
        drink = factory->CreateDrink();
    }

    void Serve() {
        cout << "\n[세트 메뉴 준비 완료]" << endl;
        burger->Make();
        fries->Fry();
        drink->Pour();
    }

    ~SetMenu() {
        delete burger;
        delete fries;
        delete drink;
    }
};



int main() {

    FastFoodFactory* factory = nullptr;

    int choice;
    cout << "브랜드 선택 (1: 맥도날드, 2: 롯데리아): ";
    cin >> choice;

    if (choice == 1)
        factory = new McFactory();
    else if (choice == 2)
        factory = new LotteFactory();
    else {
        cout << "잘못된 입력입니다." << endl;
        return 1;
    }

    SetMenu set(factory);
    set.Serve();

    delete factory;

    return 0;
}