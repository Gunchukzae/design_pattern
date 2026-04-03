#include <iostream>
#include <string>

/**
 * Facade 패턴
 *
 * 목적:
 * 복잡한 여러 서브시스템을 하나의 간단한 인터페이스로 묶어서
 * 클라이언트가 쉽게 사용할 수 있도록 하는 패턴
 *
 * 핵심:
 * - 클라이언트는 Facade만 사용
 * - 내부 복잡한 로직은 숨김
 */

 /**
  * Subsystem1
  * -> 그래픽 시스템 (렌더링 엔진)
  *
  * Facade를 통해 호출될 수도 있고,
  * 직접 클라이언트가 사용할 수도 있음
  */
class Subsystem1 {
public:
    std::string Operation1() const {
        return "그래픽 시스템: 초기화 완료!\n";
    }

    std::string OperationN() const {
        return "그래픽 시스템: 렌더링 시작!\n";
    }
};

/**
 * Subsystem2
 * -> 사운드 시스템
 */
class Subsystem2 {
public:
    std::string Operation1() const {
        return "사운드 시스템: 준비 완료!\n";
    }

    std::string OperationZ() const {
        return "사운드 시스템: 음악 재생!\n";
    }
};

/**
 * Facade 클래스
 *
 * 역할:
 * - 여러 서브시스템을 하나로 묶음
 * - 간단한 인터페이스 제공
 * - 내부적으로 어떤 순서로 호출할지 관리
 */
class Facade {
protected:
    Subsystem1* subsystem1_;
    Subsystem2* subsystem2_;

public:
    /**
     * 생성자
     * - 외부에서 시스템을 주입 받을 수도 있고
     * - 내부에서 직접 생성할 수도 있음
     */
    Facade(Subsystem1* subsystem1 = nullptr,Subsystem2* subsystem2 = nullptr) {

        this->subsystem1_ = subsystem1 ? subsystem1 : new Subsystem1;
        this->subsystem2_ = subsystem2 ? subsystem2 : new Subsystem2;
    }

    ~Facade() {
        delete subsystem1_;
        delete subsystem2_;
    }

    /**
     * 게임 시작 기능
     *
     * 클라이언트는 이 함수 하나만 호출하면 됨
     * 내부에서는 여러 시스템이 순서대로 실행됨
     */
    std::string Operation() {
        std::string result = "게임 시작 준비...\n";

        result += this->subsystem1_->Operation1(); // 그래픽 초기화
        result += this->subsystem2_->Operation1(); // 사운드 준비

        result += "게임 실행!\n";

        result += this->subsystem1_->OperationN(); // 렌더링 시작
        result += this->subsystem2_->OperationZ(); // 음악 재생

        return result;
    }
};

/**
 * 클라이언트 코드
 *
 * Facade만 사용하면 됨
 * (내부 시스템 몰라도 됨)
 */
void ClientCode(Facade* facade) {
    std::cout << facade->Operation();
}

int main() {
    // 서브시스템 직접 생성
    Subsystem1* subsystem1 = new Subsystem1;
    Subsystem2* subsystem2 = new Subsystem2;

    // Facade에 주입
    Facade* facade = new Facade(subsystem1, subsystem2);

    // 클라이언트는 Facade만 사용
    ClientCode(facade);

    delete facade;

    return 0;
}