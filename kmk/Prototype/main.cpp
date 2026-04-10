#include "prototype.h"
#include <iostream>
using namespace std;

// ============================================================
// 출력 헬퍼
// ============================================================
void printUnit(const string& label, const GameUnit* unit) {
    cout << "\n[" << label << "]" << endl;
    cout << "  Object Address : " << unit << endl;
    unit->display();
}

// ============================================================
// main
// ============================================================
int main() {
    cout << "========== Prototype Pattern — Game Unit Example ==========" << endl;

    // -----------------------------------------------------------
    // Step 1. 프로토타입 원본을 Registry에 등록
    // -----------------------------------------------------------
    cout << "\n--- Step 1: Register Prototypes ---" << endl;

    UnitRegistry* registry = UnitRegistry::getInstance();
    registry->registerUnit("warrior", new Warrior());
    registry->registerUnit("mage",    new Mage());
    registry->registerUnit("archer",  new Archer());

    // -----------------------------------------------------------
    // Step 2. 원본 출력 (참고용)
    // -----------------------------------------------------------
    cout << "\n--- Step 2: Original Prototypes ---" << endl;

    GameUnit* protoWarrior = registry->spawn("warrior");
    GameUnit* protoMage    = registry->spawn("mage");
    GameUnit* protoArcher  = registry->spawn("archer");

    printUnit("Original Warrior", protoWarrior);
    printUnit("Original Mage",    protoMage);
    printUnit("Original Archer",  protoArcher);

    // -----------------------------------------------------------
    // Step 3. 복제 후 개별 커스터마이징
    //         원본은 변경되지 않음을 확인
    // -----------------------------------------------------------
    cout << "\n--- Step 3: Clone & Customize ---" << endl;

    // 전사 복제 → 이름과 스탯 변경
    GameUnit* eliteWarrior = registry->spawn("warrior");
    eliteWarrior->setName("Elite Warrior");
    eliteWarrior->setAttack(120);
    eliteWarrior->setWeapon("Dragon Slayer");

    // 마법사 복제 → 다크 버전으로 변경
    GameUnit* darkMage = registry->spawn("mage");
    darkMage->setName("Dark Mage");
    darkMage->setAttack(180);
    darkMage->setArmor("Shadow Robe");
    static_cast<Mage*>(darkMage)->setMana(300);

    // 궁수 복제 → 스나이퍼로 변경
    GameUnit* sniper = registry->spawn("archer");
    sniper->setName("Sniper");
    sniper->setAttack(150);
    sniper->setWeapon("Sniper Bow");
    static_cast<Archer*>(sniper)->setArrowCount(10);

    printUnit("Elite Warrior (clone)", eliteWarrior);
    printUnit("Dark Mage (clone)",     darkMage);
    printUnit("Sniper (clone)",        sniper);

    // -----------------------------------------------------------
    // Step 4. 원본이 변경되지 않았음을 확인
    // -----------------------------------------------------------
    cout << "\n--- Step 4: Verify Originals Are Unchanged ---" << endl;

    GameUnit* checkWarrior = registry->spawn("warrior");
    GameUnit* checkMage    = registry->spawn("mage");
    GameUnit* checkArcher  = registry->spawn("archer");

    printUnit("Warrior (should be original)", checkWarrior);
    printUnit("Mage    (should be original)", checkMage);
    printUnit("Archer  (should be original)", checkArcher);

    // -----------------------------------------------------------
    // Step 5. 대량 유닛 스폰 시연 (복제 비용이 낮음을 보여줌)
    // -----------------------------------------------------------
    cout << "\n--- Step 5: Mass Spawn (x5 Warriors) ---" << endl;

    GameUnit* squad[5];
    for (int i = 0; i < 5; ++i) {
        squad[i] = registry->spawn("warrior");
        squad[i]->setHp(200 - i * 10);   // 각 유닛마다 HP 차등
        cout << "  Warrior[" << i << "] address: " << squad[i]
             << " | HP: " << 200 - i * 10 << endl;
    }

    // -----------------------------------------------------------
    // 메모리 해제
    // -----------------------------------------------------------
    cout << "\n--- Cleanup ---" << endl;

    delete protoWarrior;
    delete protoMage;
    delete protoArcher;
    delete eliteWarrior;
    delete darkMage;
    delete sniper;
    delete checkWarrior;
    delete checkMage;
    delete checkArcher;
    for (int i = 0; i < 5; ++i) delete squad[i];
    delete UnitRegistry::getInstance();

    cout << "All units destroyed. Done!" << endl;

    return 0;
}
