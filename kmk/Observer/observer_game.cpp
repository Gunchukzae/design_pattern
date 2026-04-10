#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ============================================================
// Observer 인터페이스
// 플레이어 상태 변화를 통보받는 모든 구독자의 공통 인터페이스
// ============================================================
class PlayerObserver {
public:
    virtual ~PlayerObserver() = default;
    virtual void onHpChanged(int currentHp, int maxHp) = 0;
    virtual void onPlayerDead() = 0;
};

// ============================================================
// Subject: 플레이어 — 상태가 변하면 구독자들에게 알림
// ============================================================
class Player {
private:
    string        name;
    int           hp;
    int           maxHp;
    vector<PlayerObserver*> observers;

    void notify() {
        for (auto* obs : observers)
            obs->onHpChanged(hp, maxHp);
    }

    void notifyDead() {
        for (auto* obs : observers)
            obs->onPlayerDead();
    }

public:
    Player(const string& name, int maxHp)
        : name(name), hp(maxHp), maxHp(maxHp) {}

    // 구독 등록 / 해제
    void subscribe(PlayerObserver* obs) {
        observers.push_back(obs);
    }

    void unsubscribe(PlayerObserver* obs) {
        observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
        cout << "[Player] 구독자 제거 완료" << endl;
    }

    // 데미지 받기 — 상태 변화 → 자동 알림
    void takeDamage(int damage) {
        cout << "\n[" << name << "] " << damage << " 데미지 받음!" << endl;
        hp = max(0, hp - damage);
        notify();

        if (hp == 0)
            notifyDead();
    }

    // 힐 받기 — 상태 변화 → 자동 알림
    void heal(int amount) {
        cout << "\n[" << name << "] " << amount << " HP 회복!" << endl;
        hp = min(maxHp, hp + amount);
        notify();
    }

    int getHp()    const { return hp; }
    int getMaxHp() const { return maxHp; }
    string getName() const { return name; }
};

// ============================================================
// ConcreteObserver 1: HP 바 UI
// 화면에 HP 바를 시각적으로 표시
// ============================================================
class HpBarUI : public PlayerObserver {
public:
    void onHpChanged(int currentHp, int maxHp) override {
        int barLength  = 20;
        int filled     = (currentHp * barLength) / maxHp;
        int empty      = barLength - filled;

        cout << "[HP바] [";
        cout << string(filled, '#') << string(empty, '-');
        cout << "] " << currentHp << "/" << maxHp << endl;
    }

    void onPlayerDead() override {
        cout << "[HP바] [--------------------] DEAD" << endl;
    }
};

// ============================================================
// ConcreteObserver 2: 사운드 시스템
// HP 상태에 따라 다른 효과음 재생
// ============================================================
class SoundSystem : public PlayerObserver {
public:
    void onHpChanged(int currentHp, int maxHp) override {
        float ratio = (float)currentHp / maxHp;

        if (ratio <= 0.0f)
            return;
        else if (ratio <= 0.25f)
            cout << "[사운드] 심박수 경고음 재생 (두근두근...)" << endl;
        else if (ratio <= 0.5f)
            cout << "[사운드] 위험 BGM으로 전환" << endl;
        else
            cout << "[사운드] 일반 BGM 유지" << endl;
    }

    void onPlayerDead() override {
        cout << "[사운드] 사망 효과음 재생 (Game Over 음악 시작)" << endl;
    }
};

// ============================================================
// ConcreteObserver 3: 게임오버 시스템
// 플레이어 사망 시 게임오버 처리
// ============================================================
class GameOverSystem : public PlayerObserver {
public:
    void onHpChanged(int currentHp, int maxHp) override {
        // HP 변화에는 반응 안 함 (사망만 처리)
    }

    void onPlayerDead() override {
        cout << "[게임오버] 게임오버 화면 표시" << endl;
        cout << "[게임오버] 저장 데이터 불러오기 버튼 활성화" << endl;
        cout << "[게임오버] 플레이 시간 기록 중..." << endl;
    }
};

// ============================================================
// ConcreteObserver 4: 업적 시스템
// 특정 조건 달성 시 업적 해금
// ============================================================
class AchievementSystem : public PlayerObserver {
private:
    bool nearDeathAchieved = false;

public:
    void onHpChanged(int currentHp, int maxHp) override {
        float ratio = (float)currentHp / maxHp;

        if (!nearDeathAchieved && ratio > 0.0f && ratio <= 0.1f) {
            cout << "[업적] ★ '아슬아슬' 업적 달성! (HP 10% 이하 생존)" << endl;
            nearDeathAchieved = true;
        }
    }

    void onPlayerDead() override {
        cout << "[업적] ★ '첫 번째 죽음' 업적 달성!" << endl;
    }
};

// ============================================================
// main
// ============================================================
int main() {
    // 플레이어 생성
    Player player("용사 김민기", 100);

    // 구독자 등록
    HpBarUI          hpBar;
    SoundSystem      sound;
    GameOverSystem   gameOver;
    AchievementSystem achievement;

    player.subscribe(&hpBar);
    player.subscribe(&sound);
    player.subscribe(&gameOver);
    player.subscribe(&achievement);

    cout << "======================================" << endl;
    cout << "  게임 시작!" << endl;
    cout << "======================================" << endl;

    // 일반 데미지
    player.takeDamage(20);

    // 큰 데미지 — 위험 구간 진입
    player.takeDamage(35);

    // 힐 아이템 사용
    player.heal(15);

    // 치명타 — 업적 구간 진입
    player.takeDamage(50);

    cout << "\n--------------------------------------" << endl;
    cout << "  사운드 시스템 구독 해제 후" << endl;
    cout << "--------------------------------------" << endl;

    // 런타임에 구독 해제
    player.unsubscribe(&sound);

    // 사망 — GameOver, Achievement만 반응 (Sound 제외)
    player.takeDamage(10);

    return 0;
}
