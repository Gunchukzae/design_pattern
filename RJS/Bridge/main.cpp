#include <iostream>
#include <memory>
#include <string>

class GraphicsAPI {
public:
    virtual ~GraphicsAPI() = default;
    virtual void drawPoint(float x, float y) = 0;
    virtual void clearScreen() = 0;
};

class VulkanAPI : public GraphicsAPI {
public:
    void drawPoint(float x, float y) override {
        std::cout << "Vulkan: (" << x << ", " << y << ") 좌표에 점 생성\n";
    }
    void clearScreen() override {
        std::cout << "Vulkan: 화면 초기화\n";
    }
};

class DirectX12API : public GraphicsAPI {
public:
    void drawPoint(float x, float y) override {
        std::cout << "DX12: (" << x << ", " << y << ") 좌표에 점 생성\n";
    }
    void clearScreen() override {
        std::cout << "DX12: 화면 초기화\n";
    }
};

class Renderer {
protected:
	std::unique_ptr<GraphicsAPI> api; // Bridge 역할

public:
    Renderer(std::unique_ptr<GraphicsAPI> api) : api(std::move(api)) {}
    virtual ~Renderer() = default;

    virtual void render(float x, float y) {
        api->clearScreen();
        api->drawPoint(x, y);
    }
};

class ShapeRenderer : public Renderer {
public:
    ShapeRenderer(std::unique_ptr<GraphicsAPI> api) : Renderer(std::move(api)) {}

    void drawSquare(float x, float y, float size) {
        std::cout << "--- 사각형 렌더링 시작 ---\n";
        api->drawPoint(x, y);
        api->drawPoint(x + size, y);
        api->drawPoint(x, y + size);
        api->drawPoint(x + size, y + size);
        std::cout << "--- 사각형 렌더링 완료 ---\n";
    }
};

int main() {
    std::cout << "=== 고사양 그래픽 렌더링을 시작합니다 ===\n" << std::endl;

    auto vkApi = std::make_unique<VulkanAPI>();
    Renderer basicRenderer(std::move(vkApi));
    basicRenderer.render(30.f, 120.f);

    std::cout << "\n";

    auto dxApi = std::make_unique<DirectX12API>();
    ShapeRenderer advancedRenderer(std::move(dxApi));
    advancedRenderer.render(70.f, 95.f);
    advancedRenderer.drawSquare(10, 10, 50);

    return 0;
}