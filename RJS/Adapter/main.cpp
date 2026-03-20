#include <iostream>
#include <memory>

class Renderer
{
public:
	virtual ~Renderer() = default;
	virtual void draw(float x, float y) = 0;
};

class VulkanEngine {
public:
    void recordDrawCommand(float posX, float posY) {
        std::cout << "Vulkan 엔진으로 (" << posX << ", " << posY << ")에 그리기\n";
    }
};

class DirectX12Engine {
public:
    void executeDraw(float coordX, float coordY) {
        std::cout << "DX12 엔진으로 (" << coordX << ", " << coordY << ")에 그리기\n";
    }
};

class VulkanAdapter : public Renderer {
private:
    std::unique_ptr<VulkanEngine> vulkanEngine;

public:
    VulkanAdapter(std::unique_ptr<VulkanEngine> engine)
        : vulkanEngine(std::move(engine)) {
    }

    void draw(float x, float y) override {
        vulkanEngine->recordDrawCommand(x, y); // Vulkan의 메소드로 변환
    }
};

class DX12Adapter : public Renderer {
private:
    std::unique_ptr<DirectX12Engine> dx12Engine;

public:
    DX12Adapter(std::unique_ptr<DirectX12Engine> engine)
        : dx12Engine(std::move(engine)) {
    }

    void draw(float x, float y) override {
        dx12Engine->executeDraw(x, y); // DX12의 메소드로 변환
    }
};

class GraphicsDisplay {
public:
    void renderToScreen(Renderer* renderer, float x, float y) {
        renderer->draw(x, y);
    }
};

int main() {
    GraphicsDisplay display;

    auto vkEngine = std::make_unique<VulkanEngine>();
    auto vkAdapter = std::make_unique<VulkanAdapter>(std::move(vkEngine));

    auto dxEngine = std::make_unique<DirectX12Engine>();
    auto dxAdapter = std::make_unique<DX12Adapter>(std::move(dxEngine));

    std::cout << "=== 고사양 그래픽 렌더링을 시작합니다 ===\n" << std::endl;

    display.renderToScreen(vkAdapter.get(), 100.f, 20.f);
    display.renderToScreen(dxAdapter.get(), 50.f, 80.f);

    return 0;
}