#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

// Flyweight
struct NPCModel {
    std::string typeName;
    std::vector<int> heavyTexture;

    NPCModel(const std::string& name) : typeName(name) {
        heavyTexture.resize(1000000, 255);
    }

    void render(float x, float y, int health) const {
        std::cout << "  -> [" << typeName << "] 위치:(" << x << ", " << y
            << "), HP:" << health << "로 NPC 모델 렌더링\n";
    }
};

// Flyweight Factory
class NPCFactory {
private:
    static std::unordered_map<std::string, std::shared_ptr<NPCModel>> pool;

public:
    static std::shared_ptr<NPCModel> getModel(const std::string& type) {
        if (pool.find(type) == pool.end()) {
            pool[type] = std::make_shared<NPCModel>(type);
        }
        return pool[type];
    }

    static size_t getModelCount() {
        return pool.size();
    }
};

std::unordered_map<std::string, std::shared_ptr<NPCModel>> NPCFactory::pool;

// Context. Extrinsic state
class NPC {
private:
    float x, y;
    int health;
    std::shared_ptr<NPCModel> model;

public:
    NPC(float x, float y, int hp, const std::string& type)
        : x(x), y(y), health(hp) {
        model = NPCFactory::getModel(type);
    }

    void draw() const {
        model->render(x, y, health);
    }
};

int main() {
    std::vector<NPC> crowd;

    std::cout << "=== NPC 생성 시작 ===\n";
    crowd.emplace_back(10.5f, 20.0f, 100, "Soldier");
    crowd.emplace_back(15.0f, 25.0f, 80, "Soldier");   // 재사용
    crowd.emplace_back(50.0f, 10.0f, 100, "Civilian");
    crowd.emplace_back(12.0f, 22.0f, 45, "Soldier");   // 재사용
    crowd.emplace_back(30.0f, 40.0f, 90, "Civilian");  // 재사용

    std::cout << "\n=== NPC 모델 렌더링 ===\n";
    for (const auto& npc : crowd) {
        npc.draw();
    }

    std::cout << "\n" << std::string(40, '=') << "\n";
    std::cout << " - 생성된 총 NPC 객체 수  : " << crowd.size() << " 개\n";
    std::cout << " - 메모리 내 실제 모델 수 : " << NPCFactory::getModelCount() << " 개\n";

    return 0;
}