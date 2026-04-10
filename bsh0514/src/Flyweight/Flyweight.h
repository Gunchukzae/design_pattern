#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

// Flyweight (공유되는 내재 상태)
class TreeType 
{
    std::string name_;
    std::string color_;
    std::string texture_;
public:
    TreeType(std::string name, std::string color, std::string texture)
        : name_(std::move(name)), color_(std::move(color)), texture_(std::move(texture)) {}

    void draw(double x, double y) const 
    {
        std::cout << "  [" << name_ << "] "
                  << "color=" << color_
                  << "  pos=(" << x << ", " << y << ")\n";
    }

    const std::string& name() const { return name_; }
};

// Flyweight Factory
class TreeTypeFactory 
{
    std::unordered_map<std::string, std::shared_ptr<TreeType>> cache_;
public:
    std::shared_ptr<TreeType> get(const std::string& name, const std::string& color, const std::string& texture) 
    {
        std::string key = name + "_" + color + "_" + texture;
        auto it = cache_.find(key);
        if (it != cache_.end())
            return it->second;

        auto type = std::make_shared<TreeType>(name, color, texture);
        cache_[key] = type;
        std::cout << "[Factory] 새 TreeType 생성: " << name << "\n";
        return type;
    }

    std::size_t typeCount() const { return cache_.size(); }
};

// Context (외재 상태를 보유)
struct Tree 
{
    double x, y;
    std::shared_ptr<TreeType> type;   // 공유 flyweight

    void draw() const { type->draw(x, y); }
};

// 클라이언트: 숲
class Forest
{
    TreeTypeFactory       factory_;
    std::vector<Tree>     trees_;
public:
    void plantTree(double x, double y, const std::string& name, const std::string& color, const std::string& texture) 
    {
        auto type = factory_.get(name, color, texture);
        trees_.push_back({x, y, type});
    }

    void render() const 
    {
        std::cout << "\n=== 숲 렌더링 ===\n";
        for (auto& t : trees_) t.draw();
    }

    void printStats() const 
    {
        std::cout << "\n[Stats] 나무 총 개수: " << trees_.size()
                  << " | 공유 TreeType 수: " << factory_.typeCount()
                  << "\n";
    }
};
