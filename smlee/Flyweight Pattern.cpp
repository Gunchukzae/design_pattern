#include <iostream>
#include <string>
#include <unordered_map>

/**
 * Flyweight 패턴
 *
 * 목적:
 * 많은 객체를 생성해야 할 때, 공통되는 데이터를 공유하여
 * 메모리 사용량을 줄이기 위한 패턴이다.
 *
 * 핵심 개념:
 * - SharedState: 여러 객체가 공유하는 데이터
 * - UniqueState: 객체마다 다른 데이터
 */

 /**
  * Shared State
  * -> 팀의 "공통 정보"
  * (팀 이름, 부서, 위치)
  */
struct SharedState
{
    std::string team_name_;
    std::string department_;
    std::string location_;

    SharedState(const std::string& team, const std::string& dept, const std::string& loc)
        : team_name_(team), department_(dept), location_(loc)
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const SharedState& ss)
    {
        return os << "[ " << ss.team_name_ << " , " << ss.department_ << " , " << ss.location_ << " ]";
    }
};

/**
 * Unique State
 * -> 직원마다 다른 정보
 * (이름, 사번)
 */
struct UniqueState
{
    std::string employee_name_;
    std::string employee_id_;

    UniqueState(const std::string& name, const std::string& id)
        : employee_name_(name), employee_id_(id)
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const UniqueState& us)
    {
        return os << "[ " << us.employee_name_ << " , " << us.employee_id_ << " ]";
    }
};

/**
 * Flyweight 클래스
 *
 * - SharedState를 저장
 * - UniqueState는 함수 호출 시 전달받음
 */
class Flyweight
{
private:
    SharedState* shared_state_;

public:
    // 생성자: 공유 상태를 복사해서 저장
    Flyweight(const SharedState* shared_state)
        : shared_state_(new SharedState(*shared_state))
    {
    }

    // 복사 생성자
    Flyweight(const Flyweight& other)
        : shared_state_(new SharedState(*other.shared_state_))
    {
    }

    // 소멸자
    ~Flyweight()
    {
        delete shared_state_;
    }

    /**
     * 실제 동작
     * - 공유 상태 + 고유 상태를 함께 사용
     */
    void Operation(const UniqueState& unique_state) const
    {
        std::cout << "조직 DB 기록\n";
        std::cout << "공통 정보(팀): " << *shared_state_ << "\n";
        std::cout << "개별 정보(직원): " << unique_state << "\n";
        std::cout << "-----------------------------\n";
    }
};

/**
 * FlyweightFactory
 *
 * 역할:
 * - Flyweight 객체를 생성하고 관리
 * - 동일한 SharedState를 가진 객체는 재사용
 */
class FlyweightFactory
{
private:
    std::unordered_map<std::string, Flyweight> flyweights_;

    /**
     * key 생성 (공유 상태 기반)
     */
    std::string GetKey(const SharedState& ss) const
    {
        return ss.team_name_ + "_" + ss.department_ + "_" + ss.location_;
    }

public:
    /**
     * 초기 Flyweight 등록
     */
    FlyweightFactory(std::initializer_list<SharedState> shared_states)
    {
        for (const SharedState& ss : shared_states)
        {
            flyweights_.insert({ GetKey(ss), Flyweight(&ss) });
        }
    }

    /**
     * Flyweight 요청
     * - 있으면 재사용
     * - 없으면 생성
     */
    Flyweight GetFlyweight(const SharedState& shared_state)
    {
        std::string key = GetKey(shared_state);

        if (flyweights_.find(key) == flyweights_.end())
        {
            std::cout << "새로운 팀 생성\n";
            flyweights_.insert({ key, Flyweight(&shared_state) });
        }
        else
        {
            std::cout << "기존 팀 재사용\n";
        }

        return flyweights_.at(key);
    }

    /**
     * 현재 Flyweight 목록 출력
     */
    void ListFlyweights() const
    {
        std::cout << "\n현재 저장된 팀 수: " << flyweights_.size() << "\n";
        for (auto& pair : flyweights_)
        {
            std::cout << pair.first << "\n";
        }
        std::cout << "-----------------------------\n";
    }
};

/**
 * 클라이언트 함수
 *
 * 직원을 조직 DB에 등록
 */
void AddEmployeeToDatabase(
    FlyweightFactory& factory,
    const std::string& id,
    const std::string& name,
    const std::string& team,
    const std::string& dept,
    const std::string& loc)
{
    std::cout << "\n직원 등록 요청\n";

    // 공유 상태 기준으로 Flyweight 가져오기
    const Flyweight& flyweight = factory.GetFlyweight({ team, dept, loc });

    // 외재 상태 전달
    flyweight.Operation({ name, id });
}

int main()
{
    FlyweightFactory factory({
        {"Backend Team", "Engineering", "Seoul"},
        {"Frontend Team", "Engineering", "Seoul"},
        {"HR Team", "HR", "Seoul"}
        });

    factory.ListFlyweights();

    AddEmployeeToDatabase(factory,
        "E001",
        "홍길동",
        "Backend Team",
        "Engineering",
        "Seoul");

    AddEmployeeToDatabase(factory,
        "E002",
        "김철수",
        "Backend Team",
        "Engineering",
        "Seoul");

    AddEmployeeToDatabase(factory,
        "E003",
        "이영희",
        "AI Team",
        "Research",
        "Seoul"); // 새로운 shared state

    factory.ListFlyweights();



    /*
        현재 저장된 팀 수 : 3
        Backend Team_Engineering_Seoul
        Frontend Team_Engineering_Seoul
        HR Team_HR_Seoul
        ---------------------------- -

        ? ? 직원 등록 요청
        ? 기존 팀 재사용
        ? ? 조직 DB 기록
        공통 정보(팀) : [Backend Team, Engineering, Seoul]
        개별 정보(직원) : [홍길동, E001]
        ---------------------------- -

        ? ? 직원 등록 요청
        ? 기존 팀 재사용
        ? ? 조직 DB 기록
        공통 정보(팀) : [Backend Team, Engineering, Seoul]
        개별 정보(직원) : [김철수, E002]
        ---------------------------- -

        ? ? 직원 등록 요청
        ? ? 새로운 팀 생성
        ? ? 조직 DB 기록
        공통 정보(팀) : [AI Team, Research, Seoul]
        개별 정보(직원) : [이영희, E003]
        ---------------------------- -

        현재 저장된 팀 수 : 4
        Backend Team_Engineering_Seoul
        Frontend Team_Engineering_Seoul
        HR Team_HR_Seoul
        AI Team_Research_Seoul
        ---------------------------- -
    */

    return 0;
}

