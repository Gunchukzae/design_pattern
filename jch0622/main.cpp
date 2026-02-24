
// template method
// 부모클래스에서 구조 정의, 자식클래스에서 재정의

// Observer
// 인스턴스 하나, 전역 접근 지점 제공
// default construction : private

// g++ main.cpp -std=c++17 -o main.exe

#include <iostream>
#include <string>
#include <memory>


class CPrintUtil
{
public:
    CPrintUtil(const CPrintUtil&) = delete;
    CPrintUtil& operator=(const CPrintUtil&) = delete;

    void Print(const std::string& msg)
    {
        std::cout << msg << std::endl;
    }

    void Print(const std::wstring& msg)
    {
        std::wcout << msg << std::endl;
    }

    static CPrintUtil& GetInstance()
    {
        static CPrintUtil instance;
        // std::cout << &instance << std::endl;
        
        return instance;
    }

private:
    CPrintUtil() = default;
};


class CCivilBase
{
public:
    void StartCivilProduct()
    {
        MakeTitle();
        MakeController();
        MakeData();
        MakeView();
        CheckLockOption();
    }

    void EndCivilProduct()
    {
        CPrintUtil::GetInstance().Print("End.");
        CPrintUtil::GetInstance().Print("---------------");
    }

private:
    virtual void MakeTitle() = 0;

    virtual void MakeController()
    {
        CPrintUtil::GetInstance().Print("MakeController");
    }

    virtual void MakeData()
    {
        CPrintUtil::GetInstance().Print("MakeData - 1st DataBase");
    }
    
    virtual void MakeView()
    {
        CPrintUtil::GetInstance().Print("MakeView - default style");
    }

    virtual void CheckLockOption() = 0;
};

class CCivilMODS : public CCivilBase
{
private:
    void MakeTitle() override
    {
        CPrintUtil::GetInstance().Print("<Civil MODS>");
    }

    void CheckLockOption() override
    {
        CPrintUtil::GetInstance().Print("Check MODS Lock");
    }

    virtual void MakeData()
    {
        CPrintUtil::GetInstance().Print("MakeData - 2nd DataBase");
    }
};

class CCivilNX : public CCivilBase
{
private:

    void MakeTitle() override
    {
        CPrintUtil::GetInstance().Print("<CIVIL NX>");
    }

    void CheckLockOption() override
    {
        CPrintUtil::GetInstance().Print("Check NX Lock");
    }

    void MakeData() override
    {
        CPrintUtil::GetInstance().Print("MakeData - 5th DataBase");
    }

    void MakeView() override
    {
        CPrintUtil::GetInstance().Print("MakeView - NX style");
    }
};

int main()
{
    std::shared_ptr<CCivilBase> civil;
    
    civil = std::make_shared<CCivilMODS>();
    civil->StartCivilProduct();
    civil->EndCivilProduct();

    civil = std::make_shared<CCivilNX>();
    civil->StartCivilProduct();
    civil->EndCivilProduct();

    // CPrintUtil util = CPrintUtil();
}