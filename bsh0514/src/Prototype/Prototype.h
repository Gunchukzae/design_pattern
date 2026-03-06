#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

// 1) Prototype 인터페이스
class Shape 
{
public:
    virtual ~Shape() = default;
    virtual std::unique_ptr<Shape> Clone() const = 0;
    virtual void Draw() const = 0;
};

// 2) Concrete Prototype: Circle
class Circle : public Shape 
{
public:
    Circle(std::string color, double r) : color_(std::move(color)), radius_(r) {}

    std::unique_ptr<Shape> Clone() const override 
    {
        // 단순 값 타입이면 기본 복사로 충분 (깊은/얕은 문제 없음)
        return std::make_unique<Circle>(*this);
    }

    void Draw() const override 
    {
        std::cout << "[Circle] color=" << color_ << ", r=" << radius_ << "\n";
    }

    void SetRadius(double r) { radius_ = r; }

private:
    std::string color_;
    double radius_;
};

// 2) Concrete Prototype: Polygon
class Polygon : public Shape 
{
public:
    Polygon(std::string name, std::vector<int> points)
        : name_(std::move(name)), points_(std::make_unique<std::vector<int>>(std::move(points))) {}

    // 깊은 복사 생성자 (포인터가 가리키는 실제 데이터까지 복사)
    Polygon(const Polygon& other)
        : name_(other.name_), points_(std::make_unique<std::vector<int>>(*other.points_)) {}

    Polygon& operator=(const Polygon& other) 
    {
        if (this == &other) return *this;
        name_ = other.name_;
        points_ = std::make_unique<std::vector<int>>(*other.points_);
        return *this;
    }

    std::unique_ptr<Shape> Clone() const override 
    {
        // 깊은 복사가 구현되어 있으니 *this 복사로 안전하게 clone 가능
        return std::make_unique<Polygon>(*this);
    }

    void Draw() const override 
    {
        std::cout << "[Polygon] name=" << name_ << ", points={";
        for (size_t i = 0; i < points_->size(); ++i) 
        {
            std::cout << (*points_)[i] << (i + 1 < points_->size() ? "," : "");
        }
        std::cout << "}\n";
    }

    void PushPoint(int p) { points_->push_back(p); }

private:
    std::string name_;
    std::unique_ptr<std::vector<int>> points_;
};

// 3) Prototype Registry
class PrototypeRegistry 
{
public:
    void Register(const std::string& key, std::unique_ptr<Shape> proto) 
    {
        protos_[key] = std::move(proto);
    }

    std::unique_ptr<Shape> Create(const std::string& key) const 
    {
        auto it = protos_.find(key);
        if (it == protos_.end()) return nullptr;
        return it->second->Clone(); // 핵심: 등록된 원형을 복제해서 반환
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Shape>> protos_;
};