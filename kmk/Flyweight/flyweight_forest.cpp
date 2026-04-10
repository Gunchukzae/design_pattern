#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// ============================================================
// Flyweight: Intrinsic 상태만 보관 (공유되는 데이터)
// 나무의 "종류" — 변하지 않고 모든 같은 종 나무가 공유
// ============================================================
class TreeType {
private:
    string name;     // 나무 이름 (소나무, 참나무, 벚나무...)
    string color;    // 잎 색깔
    string texture;  // 텍스처 파일 경로 (용량이 큰 데이터)

public:
    TreeType(const string& name, const string& color, const string& texture)
        : name(name), color(color), texture(texture)
    {
        // 실제 게임에서 texture 로드는 매우 비싼 작업
        cout << "[TreeType 생성] " << name
             << " (색: " << color << ", 텍스처: " << texture << ")" << endl;
    }

    // Extrinsic 상태(x, y)는 외부에서 받아서 사용
    void draw(int x, int y) const {
        cout << "  [" << name << "] 색:" << color
             << " | 위치: (" << x << ", " << y << ")" << endl;
    }

    string getName() const { return name; }
};

// ============================================================
// Flyweight Factory: TreeType 객체를 관리하고 재사용
// 같은 종류의 나무는 절대 두 번 생성하지 않음
// ============================================================
class TreeFactory {
private:
    map<string, TreeType*> pool;  // 생성된 TreeType 보관

public:
    ~TreeFactory() {
        for (auto& pair : pool)
            delete pair.second;
    }

    TreeType* getTreeType(const string& name,
                          const string& color,
                          const string& texture)
    {
        string key = name + "_" + color;

        if (pool.find(key) == pool.end()) {
            // 처음 요청 시에만 생성
            pool[key] = new TreeType(name, color, texture);
        } else {
            cout << "[TreeFactory] '" << name << "' 재사용 (새 객체 생성 안 함)" << endl;
        }

        return pool[key];
    }

    int getTypeCount() const { return pool.size(); }
};

// ============================================================
// Tree: 개별 나무 — Extrinsic 상태만 직접 보관
// TreeType은 공유 객체를 포인터로 참조
// ============================================================
struct Tree {
    int x, y;           // Extrinsic: 나무마다 다른 위치
    int age;            // Extrinsic: 나무마다 다른 나이
    TreeType* type;     // Intrinsic: 공유 객체 참조 (포인터만 저장)

    Tree(int x, int y, int age, TreeType* type)
        : x(x), y(y), age(age), type(type) {}

    void draw() const {
        type->draw(x, y);
        cout << "    └─ 나이: " << age << "년" << endl;
    }
};

// ============================================================
// Forest: 나무들을 관리하는 컨테이너
// ============================================================
class Forest {
private:
    vector<Tree>  trees;
    TreeFactory   factory;

public:
    void plantTree(int x, int y, int age,
                   const string& name,
                   const string& color,
                   const string& texture)
    {
        TreeType* type = factory.getTreeType(name, color, texture);
        trees.push_back(Tree(x, y, age, type));
    }

    void draw() const {
        cout << "\n[숲 렌더링 - 나무 " << trees.size() << "그루]" << endl;
        for (const Tree& tree : trees)
            tree.draw();
    }

    void printMemoryInfo() const {
        int treeCount     = trees.size();
        int typeCount     = factory.getTypeCount();

        // 메모리 절약 효과 계산 (단순화된 예시)
        int sizePerType   = 500;  // TreeType 하나당 약 500 bytes (텍스처 포함)
        int sizePerTree   = 20;   // Tree 하나당 약 20 bytes (좌표, 나이, 포인터)

        int withFlyweight    = (typeCount * sizePerType) + (treeCount * sizePerTree);
        int withoutFlyweight = treeCount * (sizePerType + sizePerTree);

        cout << "\n[메모리 사용량 비교]" << endl;
        cout << "  나무 총 개수     : " << treeCount << "그루" << endl;
        cout << "  TreeType 종류 수 : " << typeCount << "종 (실제 생성된 객체)" << endl;
        cout << "  플라이웨이트 적용: " << withFlyweight    << " bytes" << endl;
        cout << "  적용 안 했을 때  : " << withoutFlyweight << " bytes" << endl;
        cout << "  절약한 메모리    : " << withoutFlyweight - withFlyweight << " bytes" << endl;
    }
};

// ============================================================
// main
// ============================================================
int main() {
    Forest forest;

    cout << "===== 나무 심기 시작 =====" << endl;

    // 소나무 5그루 — TreeType은 1개만 생성, 나머지는 재사용
    forest.plantTree(10, 20, 15, "소나무", "진초록", "pine.png");
    forest.plantTree(30, 50, 22, "소나무", "진초록", "pine.png");
    forest.plantTree(55, 10, 8,  "소나무", "진초록", "pine.png");
    forest.plantTree(80, 70, 30, "소나무", "진초록", "pine.png");
    forest.plantTree(25, 90, 12, "소나무", "진초록", "pine.png");

    cout << endl;

    // 참나무 4그루 — TreeType은 1개만 생성
    forest.plantTree(15, 40, 40, "참나무", "갈색",   "oak.png");
    forest.plantTree(60, 30, 55, "참나무", "갈색",   "oak.png");
    forest.plantTree(45, 85, 62, "참나무", "갈색",   "oak.png");
    forest.plantTree(90, 15, 33, "참나무", "갈색",   "oak.png");

    cout << endl;

    // 벚나무 3그루 — TreeType은 1개만 생성
    forest.plantTree(35, 60, 7,  "벚나무", "분홍",   "cherry.png");
    forest.plantTree(70, 45, 9,  "벚나무", "분홍",   "cherry.png");
    forest.plantTree(50, 75, 5,  "벚나무", "분홍",   "cherry.png");

    // 렌더링
    forest.draw();

    // 메모리 절약 효과 출력
    forest.printMemoryInfo();

    return 0;
}
