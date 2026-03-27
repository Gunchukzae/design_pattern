#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>

class IOrganization {
public:
    virtual std::string getName() const = 0;
    virtual int getSalary() const = 0;
    virtual int getCount() const = 0;
    virtual void print(int depth = 0) const = 0;
    virtual ~IOrganization() = default;
};

class Employee : public IOrganization {
    std::string name_;
    std::string position_;
    int salary_;

public:
    Employee(std::string name, std::string position, int salary)
        : name_(std::move(name))
        , position_(std::move(position))
        , salary_(salary) {
    }

    std::string getName()  const override { return name_; }
    int getSalary()        const override { return salary_; }
    int getCount()         const override { return 1; }

    void print(int depth = 0) const override {
        std::string indent(depth * 2, ' ');
        std::cout << indent << name_
            << " [" << position_ << "]"
            << " - " << salary_ << "만\n";
    }
};

class Department : public IOrganization {
    std::string name_;
    std::vector<std::shared_ptr<IOrganization>> members_;

public:
    explicit Department(std::string name)
        : name_(std::move(name)) {
    }

    void add(std::shared_ptr<IOrganization> member) {
        members_.push_back(std::move(member));
    }

    void remove(const std::string& name) {
        members_.erase(
            std::remove_if(members_.begin(), members_.end(),
                [&name](const auto& m) { return m->getName() == name; }),
            members_.end()
        );
    }

    std::string getName() const override { return name_; }

    int getSalary() const override {
        int total = 0;
        for (const auto& member : members_)
            total += member->getSalary();
        return total;
    }

    int getCount() const override {
        int total = 0;
        for (const auto& member : members_)
            total += member->getCount();
        return total;
    }

    void print(int depth = 0) const override {
        std::string indent(depth * 2, ' ');
        std::cout << indent << "[" << name_ << "]"
            << "  인원: " << getCount() << "명"
            << "  인건비: " << getSalary() << "만\n";
        for (const auto& member : members_)
            member->print(depth + 1);
    }
};

int main() {
    auto ceo = std::make_shared<Employee>("류지승", "CEO", 800);
    auto lee = std::make_shared<Employee>("이수민", "백엔드개발자", 500);
    auto moon = std::make_shared<Employee>("문성혁", "백엔드개발자", 450);
    auto bae = std::make_shared<Employee>("배상현", "프론트개발자", 480);
    auto jang = std::make_shared<Employee>("장창현", "프론트개발자", 430);
    auto kim = std::make_shared<Employee>("김민기", "HR매니저", 400);

    auto backendTeam = std::make_shared<Department>("백엔드팀");
    backendTeam->add(lee);
    backendTeam->add(moon);

    auto frontendTeam = std::make_shared<Department>("프론트엔드팀");
    frontendTeam->add(bae);
    frontendTeam->add(jang);

    auto devDiv = std::make_shared<Department>("개발본부");
    devDiv->add(backendTeam);
    devDiv->add(frontendTeam);

    auto bizDiv = std::make_shared<Department>("경영지원본부");
    bizDiv->add(kim);

    auto company = std::make_shared<Department>("MIDASCorp");
    company->add(ceo);
    company->add(devDiv);
    company->add(bizDiv);

    std::cout << "\n========== 전체 조직도 ==========\n";
    company->print();

    return 0;
}