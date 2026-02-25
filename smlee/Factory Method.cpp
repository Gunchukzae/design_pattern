#include <iostream>
#include <string>
using namespace std;


class Transport {
public:
    virtual void Deliver() = 0;  
    virtual ~Transport() {}
};


class Truck : public Transport {
public:
    void Deliver() override {
        cout << "트럭이 육로로 화물을 배달합니다." << endl;
    }
};

class Ship : public Transport {
public:
    void Deliver() override {
        cout << "선박이 해상으로 화물을 배달합니다." << endl;
    }
};


// Creator 
class Logistics {
public:
    // 어떤 운송 수단을 생성할지는 자식 클래스가 결정
    virtual Transport* CreateTransport() = 0;

    void PlanDelivery() {
        cout << "\n[배송 계획 수립]" << endl;

        // 직접 new Truck() 하지 않음
        Transport* transport = CreateTransport();

        transport->Deliver();

        delete transport;
    }

    virtual ~Logistics() {}
};


// 생성될 객체 유형을 결정
class RoadLogistics : public Logistics {
public:
    Transport* CreateTransport() override {
        return new Truck();
    }
};

class SeaLogistics : public Logistics {
public:
    Transport* CreateTransport() override {
        return new Ship();
    }
};


int main() {
    Logistics* logistics = nullptr;

    string type;
    cout << "운송 방식 선택 (road / sea): ";
    cin >> type;

    if (type == "road") {
        logistics = new RoadLogistics();
    }
    else if (type == "sea") {
        logistics = new SeaLogistics();
    }
    else {
        cout << "잘못된 입력입니다." << endl;
        return 1;
    }

    // 클라이언트는 구체 제품을 모름
    logistics->PlanDelivery();

    delete logistics;

    return 0;
}