#include <iostream>
#include <string>

// Subsystems
class TV 
{
public:
    void on()              { std::cout << "TV 전원 ON\n"; }
    void off()             { std::cout << "TV 전원 OFF\n"; }
    void setInput(const std::string& src) {
        std::cout << "TV 입력 소스: " << src << "\n";
    }
};

class Amplifier 
{
public:
    void on()              { std::cout << "앰프 전원 ON\n"; }
    void off()             { std::cout << "앰프 전원 OFF\n"; }
    void setVolume(int v)  { std::cout << "앰프 볼륨: " << v << "\n"; }
};

class StreamingPlayer 
{
public:
    void on()              { std::cout << "스트리밍 플레이어 ON\n"; }
    void off()             { std::cout << "스트리밍 플레이어 OFF\n"; }
    void play(const std::string& movie) {
        std::cout << "재생 중: " << movie << "\n";
    }
    void stop()            { std::cout << "재생 중지\n"; }
};

// Facade
class HomeTheaterFacade 
{
    TV              tv_;
    Amplifier       amp_;
    StreamingPlayer player_;
public:
    void watchMovie(const std::string& movie) {
        std::cout << "=== 영화 모드 시작 ===\n";
        tv_.on();
        tv_.setInput("HDMI1");
        amp_.on();
        amp_.setVolume(20);
        player_.on();
        player_.play(movie);
    }

    void endMovie() {
        std::cout << "=== 영화 모드 종료 ===\n";
        player_.stop();
        player_.off();
        amp_.off();
        tv_.off();
    }
};
