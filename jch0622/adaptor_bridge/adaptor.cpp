#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <memory>
#include <io.h>
#include <fcntl.h>

class UsefulInfo
{
public:
    void PrintInfo(const std::wstring& strInfo)
    {
        std::wcout << strInfo << std::endl;
    }
};

class AnotherInfoInterface
{
public:
    virtual void ConvertAnotherInfo(const std::string& strInfo) = 0;
};

class AnotherInfoAdaptor : public AnotherInfoInterface
{
public:
    AnotherInfoAdaptor(std::unique_ptr<UsefulInfo>&& info)
    {
        usefulInfo = std::move(info);
    }

    void ConvertAnotherInfo(const std::string& strInfo) override
    {
        // utf8 -> utf16 변환
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
        std::wstring wstrInfo = convert.from_bytes(strInfo);

        usefulInfo->PrintInfo(wstrInfo);
    }

private:
    std::unique_ptr<UsefulInfo> usefulInfo;
};


int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    // UTF-16을 지원하는 출력기
    {
        UsefulInfo info;
        info.PrintInfo(L"좋은 아침");
    }

    // 우리도 UTF-16을 지원하는 출력기를 쓰고 싶어
    {
        auto usefulInfo = std::make_unique<UsefulInfo>();

        std::unique_ptr<AnotherInfoInterface> another;
        another = std::make_unique<AnotherInfoAdaptor>(std::move(usefulInfo));

        another->ConvertAnotherInfo("좋은 早晨");
    }
}