#include "prototype.h"
#include <iostream>
using namespace std;

// ============================================================
// GameUnit::display() 구현
// ============================================================
void GameUnit::display() const {
    cout << "  Name    : " << name    << endl;
    cout << "  HP      : " << hp      << endl;
    cout << "  Attack  : " << attack  << endl;
    cout << "  Defense : " << defense << endl;
    cout << "  Weapon  : " << weapon  << endl;
    cout << "  Armor   : " << armor   << endl;
    if (!skills.empty()) {
        cout << "  Skills  : ";
        for (size_t i = 0; i < skills.size(); ++i) {
            cout << skills[i];
            if (i + 1 < skills.size()) cout << ", ";
        }
        cout << endl;
    }
}

// ============================================================
// Warrior 구현
// ============================================================
Warrior::Warrior()
    : GameUnit("Warrior", 200, 85, 70, "Longsword", "Plate Armor") {
    addSkill("Shield Bash");
    addSkill("Whirlwind");
    addSkill("Battle Cry");
}

// ============================================================
// Mage 구현
// ============================================================
Mage::Mage()
    : GameUnit("Mage", 80, 120, 20, "Magic Staff", "Robe"), mana(150) {
    addSkill("Fireball");
    addSkill("Ice Spike");
    addSkill("Teleport");
}

void Mage::display() const {
    GameUnit::display();
    cout << "  Mana    : " << mana << endl;
}

// ============================================================
// Archer 구현
// ============================================================
Archer::Archer()
    : GameUnit("Archer", 120, 95, 40, "Longbow", "Leather Armor"), arrowCount(30) {
    addSkill("Power Shot");
    addSkill("Multi Arrow");
    addSkill("Eagle Eye");
}

void Archer::display() const {
    GameUnit::display();
    cout << "  Arrows  : " << arrowCount << endl;
}

// ============================================================
// UnitRegistry 구현 (Singleton + Prototype Registry)
// ============================================================
UnitRegistry* UnitRegistry::instance = nullptr;

UnitRegistry* UnitRegistry::getInstance() {
    if (instance == nullptr)
        instance = new UnitRegistry();
    return instance;
}

void UnitRegistry::registerUnit(const string& key, GameUnit* prototype) {
    registry.push_back({key, prototype});
    cout << "[Registry] '" << key << "' prototype registered." << endl;
}

GameUnit* UnitRegistry::spawn(const string& key) const {
    for (const auto& entry : registry) {
        if (entry.first == key) {
            cout << "[Registry] Spawning clone of '" << key << "'..." << endl;
            return entry.second->clone();  // 원본을 복제하여 반환
        }
    }
    cout << "[Registry] ERROR: '" << key << "' not found!" << endl;
    return nullptr;
}

UnitRegistry::~UnitRegistry() {
    for (auto& entry : registry)
        delete entry.second;
    registry.clear();
}
