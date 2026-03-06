#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <string>
#include <vector>
using namespace std;

// ============================================================
// Prototype Interface: 복제 인터페이스 정의
// ============================================================
class GameUnit {
protected:
    string name;
    int    hp;
    int    attack;
    int    defense;
    string weapon;
    string armor;
    vector<string> skills;

public:
    GameUnit(const string& name, int hp, int attack, int defense,
             const string& weapon, const string& armor)
        : name(name), hp(hp), attack(attack), defense(defense),
          weapon(weapon), armor(armor) {}

    virtual ~GameUnit() {}

    // 핵심: 순수 가상 clone() 메서드 — 각 서브클래스가 자기 자신을 복제
    virtual GameUnit* clone() const = 0;

    void addSkill(const string& skill) { skills.push_back(skill); }

    // Setter: 복제 후 개별 수정에 사용
    void setName(const string& n)    { name    = n; }
    void setHp(int h)                { hp      = h; }
    void setAttack(int a)            { attack  = a; }
    void setDefense(int d)           { defense = d; }
    void setWeapon(const string& w)  { weapon  = w; }
    void setArmor(const string& ar)  { armor   = ar; }

    void display() const;
};

// ============================================================
// Concrete Prototype 1: 전사
// ============================================================
class Warrior : public GameUnit {
public:
    Warrior();
    GameUnit* clone() const override { return new Warrior(*this); }
};

// ============================================================
// Concrete Prototype 2: 마법사
// ============================================================
class Mage : public GameUnit {
private:
    int mana;

public:
    Mage();
    void setMana(int m) { mana = m; }
    int  getMana() const { return mana; }
    GameUnit* clone() const override { return new Mage(*this); }
    void display() const;
};

// ============================================================
// Concrete Prototype 3: 궁수
// ============================================================
class Archer : public GameUnit {
private:
    int arrowCount;

public:
    Archer();
    void setArrowCount(int c) { arrowCount = c; }
    int  getArrowCount() const { return arrowCount; }
    GameUnit* clone() const override { return new Archer(*this); }
    void display() const;
};

// ============================================================
// Prototype Registry: 원본 프로토타입을 관리하는 저장소
// ============================================================
class UnitRegistry {
private:
    static UnitRegistry* instance;
    vector<pair<string, GameUnit*>> registry;

    UnitRegistry() {}

public:
    static UnitRegistry* getInstance();

    void registerUnit(const string& key, GameUnit* prototype);
    GameUnit* spawn(const string& key) const;  // 복제본 반환

    ~UnitRegistry();
};

#endif // PROTOTYPE_H
