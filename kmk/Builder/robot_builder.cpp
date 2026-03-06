#include <iostream>
#include <string>
using namespace std;

// Product 클래스: 최종적으로 생성되는 복잡한 객체
class Robot {
private:
    string head;
    string body;
    string leftArm;
    string rightArm;
    string leftLeg;
    string rightLeg;
    string battery;

    // private 생성자: Builder를 통해서만 생성 가능
    Robot() {}

    // Builder가 Robot을 생성할 수 있도록 friend 선언
    friend class RobotBuilder;

public:
    void display() const {
        cout << "\n===== Robot Created =====" << endl;
        cout << "Head: " << head << endl;
        cout << "Body: " << body << endl;
        cout << "Left Arm: " << leftArm << endl;
        cout << "Right Arm: " << rightArm << endl;
        cout << "Left Leg: " << leftLeg << endl;
        cout << "Right Leg: " << rightLeg << endl;
        cout << "Battery: " << battery << endl;
        cout << "==========================\n" << endl;
    }
};

// Builder 클래스: 복잡한 객체를 단계적으로 구성
class RobotBuilder {
private:
    Robot* robot;

public:
    RobotBuilder() {
        robot = new Robot();
    }

    ~RobotBuilder() {
        if (robot != nullptr) {
            delete robot;
            robot = nullptr;
        }
    }

    // 각 부품을 구성하는 메서드들 (Fluent Interface 패턴)
    RobotBuilder& buildHead(const string& headType) {
        robot->head = headType;
        cout << "✓ Head installed: " << headType << endl;
        return *this;
    }

    RobotBuilder& buildBody(const string& bodyType) {
        robot->body = bodyType;
        cout << "✓ Body installed: " << bodyType << endl;
        return *this;
    }

    RobotBuilder& buildLeftArm(const string& armType) {
        robot->leftArm = armType;
        cout << "✓ Left Arm installed: " << armType << endl;
        return *this;
    }

    RobotBuilder& buildRightArm(const string& armType) {
        robot->rightArm = armType;
        cout << "✓ Right Arm installed: " << armType << endl;
        return *this;
    }

    RobotBuilder& buildLeftLeg(const string& legType) {
        robot->leftLeg = legType;
        cout << "✓ Left Leg installed: " << legType << endl;
        return *this;
    }

    RobotBuilder& buildRightLeg(const string& legType) {
        robot->rightLeg = legType;
        cout << "✓ Right Leg installed: " << legType << endl;
        return *this;
    }

    RobotBuilder& installBattery(const string& batteryType) {
        robot->battery = batteryType;
        cout << "✓ Battery installed: " << batteryType << endl;
        return *this;
    }

    // 최종 로봇 반환
    Robot* build() {
        Robot* completedRobot = robot;
        robot = nullptr;
        return completedRobot;
    }
};

// Director 클래스: 로봇 생성 프로세스를 관리
class RobotDirector {
public:
    // 산업용 로봇 생성
    static Robot* constructIndustrialRobot() {
        cout << "\n[Creating Industrial Robot]\n";
        RobotBuilder builder;
        return builder
            .buildHead("Industrial Head")
            .buildBody("Metal Alloy Body")
            .buildLeftArm("Hydraulic Arm")
            .buildRightArm("Hydraulic Arm")
            .buildLeftLeg("Heavy Duty Leg")
            .buildRightLeg("Heavy Duty Leg")
            .installBattery("2000mAh Industrial Battery")
            .build();
    }

    // 가정용 로봇 생성
    static Robot* constructHomeRobot() {
        cout << "\n[Creating Home Robot]\n";
        RobotBuilder builder;
        return builder
            .buildHead("Smart Head with Camera")
            .buildBody("Plastic Body")
            .buildLeftArm("Standard Arm")
            .buildRightArm("Standard Arm")
            .buildLeftLeg("Mobile Wheel")
            .buildRightLeg("Mobile Wheel")
            .installBattery("500mAh Lithium Battery")
            .build();
    }

    // 전투용 로봇 생성
    static Robot* constructWarRobot() {
        cout << "\n[Creating War Robot]\n";
        RobotBuilder builder;
        return builder
            .buildHead("Combat Head with Targeting System")
            .buildBody("Reinforced Steel Body")
            .buildLeftArm("Cannon Arm")
            .buildRightArm("Machine Gun Arm")
            .buildLeftLeg("Reinforced Leg")
            .buildRightLeg("Reinforced Leg")
            .installBattery("5000mAh Military Grade Battery")
            .build();
    }
};

int main() {
    cout << "========== Robot Builder Pattern Example ==========" << endl;

    // 방법 1: Director를 사용한 로봇 생성 (복잡한 프로세스 추상화)
    Robot* industrialRobot = RobotDirector::constructIndustrialRobot();
    industrialRobot->display();

    Robot* homeRobot = RobotDirector::constructHomeRobot();
    homeRobot->display();

    Robot* warRobot = RobotDirector::constructWarRobot();
    warRobot->display();

    // 방법 2: Builder를 직접 사용한 커스텀 로봇 생성
    cout << "\n[Creating Custom Robot]\n";
    RobotBuilder customBuilder;
    Robot* customRobot = customBuilder
        .buildHead("AI Head")
        .buildBody("Carbon Fiber Body")
        .buildLeftArm("Precision Robotic Arm")
        .buildRightArm("Multi-tool Arm")
        .buildLeftLeg("Articulated Leg")
        .buildRightLeg("Articulated Leg")
        .installBattery("3000mAh Advanced Battery")
        .build();
    customRobot->display();

    // 메모리 해제
    delete industrialRobot;
    delete homeRobot;
    delete warRobot;
    delete customRobot;

    cout << "All robots created and destroyed successfully!" << endl;

    return 0;
}
