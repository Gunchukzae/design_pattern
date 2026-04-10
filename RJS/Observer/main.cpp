#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

struct IRenderer {
    virtual void update() = 0;
    virtual ~IRenderer() = default;
};

class ShadowRenderer : public IRenderer {
public:
    void update() override {
        std::cout << "[ShadowRenderer] 카메라 이동 감지 → 그림자 재계산\n";
    }
};

class FogRenderer : public IRenderer {
public:
    void update() override {
        std::cout << "[FogRenderer] 카메라 이동 감지 → 안개 밀도 갱신\n";
    }
};

class MiniMapRenderer : public IRenderer {
public:
    void update() override {
        std::cout << "[MiniMapRenderer] 카메라 이동 감지 → 미니맵 갱신\n";
    }
};

class Camera {
    float x_, y_, z_;
    std::vector<IRenderer*> subscribers_;

public:
    Camera() : x_(0), y_(0), z_(0) {}

    void subscribe(IRenderer* r) { subscribers_.push_back(r); }
    void unsubscribe(IRenderer* r) {
        subscribers_.erase(
            std::remove(subscribers_.begin(), subscribers_.end(), r),
            subscribers_.end()
        );
    }

    void moveTo(float x, float y, float z) {
        x_ = x; y_ = y; z_ = z;
        std::cout << "\n[Camera] 위치 변경 → (" << x_ << ", " << y_ << ", " << z_ << ")\n";
        notify();
    }

private:
    void notify() {
        for (auto* r : subscribers_)
            r->update();
    }
};

int main() {
    Camera camera;

    ShadowRenderer  shadow;
    FogRenderer     fog;
    MiniMapRenderer minimap;

    camera.subscribe(&shadow);
    camera.subscribe(&fog);
    camera.subscribe(&minimap);

    camera.moveTo(10, 0, 5);

    std::cout << "\n[미니맵 구독 취소]\n";
    camera.unsubscribe(&minimap);

    camera.moveTo(20, 3, 8);

    return 0;
}