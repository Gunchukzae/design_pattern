#ifndef ROBOT_BUILDER_H
#define ROBOT_BUILDER_H

#include <string>
using namespace std;

// Product: 최종 생성 객체
class Robot {
private:
    string head;
    string body;
    string leftArm;
    string rightArm;
    string leftLeg;
    string rightLeg;
    string battery;

    Robot();
    friend class RobotBuilder;

public:
    void display() const;
};

// Builder: 복잡한 객체를 단계적으로 구성
class RobotBuilder {
private:
    Robot* robot;

public:
    RobotBuilder();
    ~RobotBuilder();

    RobotBuilder& buildHead(const string& headType);
    RobotBuilder& buildBody(const string& bodyType);
    RobotBuilder& buildLeftArm(const string& armType);
    RobotBuilder& buildRightArm(const string& armType);
    RobotBuilder& buildLeftLeg(const string& legType);
    RobotBuilder& buildRightLeg(const string& legType);
    RobotBuilder& installBattery(const string& batteryType);

    Robot* build();
};

// Director: 로봇 생성 프로세스 관리
class RobotDirector {
public:
    static Robot* constructIndustrialRobot();
    static Robot* constructHomeRobot();
    static Robot* constructWarRobot();
};

#endif
