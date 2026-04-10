#include <iostream>
#include <string>

// Complex Subsystems
class WindowSystem {
public:
    void createWindow(int w, int h) {
        std::cout << "[Window] " << w << "x" << h << " 윈도우 생성\n";
    }
};

class GraphicsDevice {
public:
    void initGPU() {
        std::cout << "[GPU] 디바이스 초기화\n";
    }
    void setViewport(int w, int h) {
        std::cout << "[GPU] 뷰포트 설정: " << w << "x" << h << "\n";
    }
};

class ShaderCompiler {
public:
    void compileDefault() {
        std::cout << "[Shader] 기본 셰이더 컴파일\n";
    }
};

class AudioSystem {
public:
    void init() {
        std::cout << "[Audio] 오디오 시스템 초기화\n";
    }
};

// Facade
class GameEngineFacade {
    WindowSystem   window;
    GraphicsDevice gpu;
    ShaderCompiler shader;
    AudioSystem    audio;

public:
    void initialize(int width, int height) {
        std::cout << "=== 게임 엔진 초기화 시작 ===\n";
        window.createWindow(width, height);
        gpu.initGPU();
        gpu.setViewport(width, height);
        shader.compileDefault();
        audio.init();
        std::cout << "=== 초기화 완료 ===\n";
    }
};

int main() {
    GameEngineFacade engine;
    engine.initialize(1920, 1080);
    return 0;
}