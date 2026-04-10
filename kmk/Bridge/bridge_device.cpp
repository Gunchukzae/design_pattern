#include <iostream>
#include <memory>
#include <string>
using namespace std;

// ============================================================
// Implementor: 기기 인터페이스
// 각 브랜드의 기기가 실제로 "어떻게" 동작하는지 구현
// ============================================================
class Device {
public:
    virtual ~Device() = default;
    virtual void powerOn() = 0;
    virtual void powerOff() = 0;
    virtual void setVolume(int level) = 0;
    virtual void setChannel(int channel) = 0;
    virtual string getName() const = 0;
};

// ============================================================
// Concrete Implementors: 실제 기기 브랜드별 구현
// ============================================================
class SamsungTV : public Device {
private:
    bool power = false;
    int volume = 10;
    int channel = 1;

public:
    void powerOn() override {
        power = true;
        cout << "[Samsung TV] 삼성 TV 켜짐 - 스마트 허브 로딩중..." << endl;
    }

    void powerOff() override {
        power = false;
        cout << "[Samsung TV] 삼성 TV 꺼짐" << endl;
    }

    void setVolume(int level) override {
        volume = level;
        cout << "[Samsung TV] 볼륨: " << volume << " (화면 우측 상단 표시)" << endl;
    }

    void setChannel(int ch) override {
        channel = ch;
        cout << "[Samsung TV] 채널 " << channel << " (채널 배너 표시)" << endl;
    }

    string getName() const override { return "Samsung TV"; }
};

class LGTV : public Device {
private:
    bool power = false;
    int volume = 10;
    int channel = 1;

public:
    void powerOn() override {
        power = true;
        cout << "[LG TV] LG TV 켜짐 - WebOS 부팅중..." << endl;
    }

    void powerOff() override {
        power = false;
        cout << "[LG TV] LG TV 꺼짐" << endl;
    }

    void setVolume(int level) override {
        volume = level;
        cout << "[LG TV] 볼륨: " << volume << " (Magic Remote 포인터 표시)" << endl;
    }

    void setChannel(int ch) override {
        channel = ch;
        cout << "[LG TV] 채널 " << channel << " (채널 정보 팝업)" << endl;
    }

    string getName() const override { return "LG TV"; }
};

class SamsungAircon : public Device {
private:
    bool power = false;
    int volume = 0;  // 에어컨은 온도로 사용
    int channel = 0; // 에어컨은 팬 속도로 사용

public:
    void powerOn() override {
        power = true;
        cout << "[Samsung 에어컨] 에어컨 켜짐 - 냉방 모드 시작" << endl;
    }

    void powerOff() override {
        power = false;
        cout << "[Samsung 에어컨] 에어컨 꺼짐" << endl;
    }

    void setVolume(int level) override {
        volume = level;
        cout << "[Samsung 에어컨] 온도 설정: " << volume << "°C" << endl;
    }

    void setChannel(int ch) override {
        channel = ch;
        cout << "[Samsung 에어컨] 팬 속도: " << channel << "단계" << endl;
    }

    string getName() const override { return "Samsung 에어컨"; }
};

// ============================================================
// Abstraction: 리모컨 기본 클래스
// "무엇을" 할지 정의 — 실제 동작은 Device에게 위임
// ============================================================
class RemoteControl {
protected:
    shared_ptr<Device> device;  // ← 이것이 Bridge (구성)

public:
    RemoteControl(shared_ptr<Device> d) : device(d) {}
    virtual ~RemoteControl() = default;

    virtual void togglePower() = 0;
    virtual void volumeUp() = 0;
    virtual void volumeDown() = 0;
    virtual void nextChannel() = 0;
};

// ============================================================
// Refined Abstractions: 리모컨 종류별 기능 확장
// ============================================================

// 기본 리모컨
class BasicRemote : public RemoteControl {
private:
    int currentVolume = 10;
    int currentChannel = 1;
    bool isOn = false;

public:
    BasicRemote(shared_ptr<Device> d) : RemoteControl(d) {}

    void togglePower() override {
        if (!isOn) {
            device->powerOn();
            isOn = true;
        } else {
            device->powerOff();
            isOn = false;
        }
    }

    void volumeUp() override {
        device->setVolume(++currentVolume);
    }

    void volumeDown() override {
        device->setVolume(--currentVolume);
    }

    void nextChannel() override {
        device->setChannel(++currentChannel);
    }
};

// 고급 리모컨 (즐겨찾기, 음소거 기능 추가)
class AdvancedRemote : public RemoteControl {
private:
    int currentVolume = 10;
    int currentChannel = 1;
    bool isOn = false;
    bool isMuted = false;
    int savedVolume = 10;

public:
    AdvancedRemote(shared_ptr<Device> d) : RemoteControl(d) {}

    void togglePower() override {
        if (!isOn) {
            device->powerOn();
            isOn = true;
        } else {
            device->powerOff();
            isOn = false;
        }
    }

    void volumeUp() override {
        isMuted = false;
        device->setVolume(++currentVolume);
    }

    void volumeDown() override {
        isMuted = false;
        device->setVolume(--currentVolume);
    }

    void nextChannel() override {
        device->setChannel(++currentChannel);
    }

    // 고급 기능: 음소거
    void mute() {
        if (!isMuted) {
            savedVolume = currentVolume;
            currentVolume = 0;
            device->setVolume(0);
            isMuted = true;
            cout << "[고급 리모컨] 음소거 ON" << endl;
        } else {
            currentVolume = savedVolume;
            device->setVolume(currentVolume);
            isMuted = false;
            cout << "[고급 리모컨] 음소거 OFF" << endl;
        }
    }

    // 고급 기능: 즐겨찾기 채널 이동
    void favoriteChannel(int ch) {
        currentChannel = ch;
        device->setChannel(ch);
        cout << "[고급 리모컨] 즐겨찾기 채널 " << ch << "번으로 이동" << endl;
    }
};

// ============================================================
// main: 리모컨과 기기의 자유로운 조합
// ============================================================
int main() {
    cout << "============================================" << endl;
    cout << "  기본 리모컨 + Samsung TV" << endl;
    cout << "============================================" << endl;
    auto samsungTV = make_shared<SamsungTV>();
    BasicRemote basicWithSamsung(samsungTV);

    basicWithSamsung.togglePower();
    basicWithSamsung.volumeUp();
    basicWithSamsung.volumeUp();
    basicWithSamsung.nextChannel();
    basicWithSamsung.togglePower();

    cout << "\n============================================" << endl;
    cout << "  기본 리모컨 + LG TV" << endl;
    cout << "============================================" << endl;
    auto lgTV = make_shared<LGTV>();
    BasicRemote basicWithLG(lgTV);

    basicWithLG.togglePower();
    basicWithLG.volumeUp();
    basicWithLG.nextChannel();
    basicWithLG.togglePower();

    cout << "\n============================================" << endl;
    cout << "  고급 리모컨 + Samsung TV" << endl;
    cout << "============================================" << endl;
    auto samsungTV2 = make_shared<SamsungTV>();
    AdvancedRemote advancedWithSamsung(samsungTV2);

    advancedWithSamsung.togglePower();
    advancedWithSamsung.volumeUp();
    advancedWithSamsung.mute();
    advancedWithSamsung.favoriteChannel(11);
    advancedWithSamsung.mute();
    advancedWithSamsung.togglePower();

    cout << "\n============================================" << endl;
    cout << "  고급 리모컨 + Samsung 에어컨" << endl;
    cout << "============================================" << endl;
    auto aircon = make_shared<SamsungAircon>();
    AdvancedRemote advancedWithAircon(aircon);

    advancedWithAircon.togglePower();
    advancedWithAircon.volumeUp();  // 온도 올리기
    advancedWithAircon.volumeUp();
    advancedWithAircon.nextChannel(); // 팬 속도 증가
    advancedWithAircon.togglePower();

    return 0;
}
