#include <iostream>
#include <thread>
#include <chrono>
#include <string>
using namespace std;

// =======================
// 싱글톤: 커피 머신
// =======================
class CoffeeMachine {
protected:
    // 생성자는 protected → 외부에서 new로 생성 불가
    CoffeeMachine(const std::string& name) : name_(name) {}

    static CoffeeMachine* instance_;  // 싱글톤 인스턴스
    std::string name_;

public:
    // 복사 생성 금지
    CoffeeMachine(CoffeeMachine& other) = delete;
    void operator=(const CoffeeMachine&) = delete;

    // 싱글톤 접근 메서드
    static CoffeeMachine* GetInstance(const std::string& name) {
        if (instance_ == nullptr) {
            instance_ = new CoffeeMachine(name);
        }
        return instance_;
    }

    // 비즈니스 로직: 커피 만들기
    void MakeCoffee(const std::string& type) {
        cout << "[" << name_ << "] " << type << " 커피 제조 중...\n";
    }

    std::string GetName() const { return name_; }
};

// 정적 멤버 초기화
CoffeeMachine* CoffeeMachine::instance_ = nullptr;

// =======================
// 스레드 예시
// =======================
void ThreadFoo() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    CoffeeMachine* machine = CoffeeMachine::GetInstance("MainMachine");
    machine->MakeCoffee("Espresso");
}

void ThreadBar() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    CoffeeMachine* machine = CoffeeMachine::GetInstance("MainMachine");
    machine->MakeCoffee("Latte");
}

// =======================
// main
// =======================
int Singleton() {
    cout << "커피 머신 싱글톤 테스트:\n";
    cout << "같은 이름이 출력되면 싱글톤이 제대로 재사용된 것!\n\n";

    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();

    CoffeeMachine* machine1 = CoffeeMachine::GetInstance("MainMachine");
    CoffeeMachine* machine2 = CoffeeMachine::GetInstance("AnotherName");

    cout << "\n테스트: 동일 인스턴스 주소 비교\n";
    cout << "machine1 주소: " << machine1 << "\n";
    cout << "machine2 주소: " << machine2 << "\n";
    cout << "이름: " << machine2->GetName() << " (처음 생성 시 이름 유지)\n";

    return 0;
}
