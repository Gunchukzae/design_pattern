#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

struct ITexture {
    virtual void draw() = 0;
    virtual ~ITexture() = default;
};

class Texture : public ITexture {
    std::string path_;
public:
    explicit Texture(const std::string& path) : path_(path) {
        std::cout << "[Texture] '" << path_ << "' 파일에서 이미지 로딩\n";
    }
    void draw() override {
        std::cout << "[Texture] '" << path_ << "' 화면에 그리기\n";
    }
};

class TextureProxy : public ITexture {
    std::string            path_;
    std::unique_ptr<Texture> real_;
public:
    explicit TextureProxy(const std::string& path) : path_(path) {
    }
    void draw() override {
        if (!real_) {
            std::cout << "[Proxy] 해당 이미지 처음 요청!\n";
            real_ = std::make_unique<Texture>(path_);
        }
        real_->draw();
    }
};

class TextureProxyCache {
    std::unordered_map<std::string, std::shared_ptr<ITexture>> cache_;
public:
    std::shared_ptr<ITexture> get(const std::string& path) {
        if (cache_.count(path)) {
            std::cout << "[Cache] '" << path << "' hit!\n";
            return cache_[path];
        }
        std::cout << "[Cache] '" << path << "' miss!\n";
        return cache_[path] = std::make_shared<TextureProxy>(path);
    }
};

int main() {
    TextureProxyCache cache;

    auto t1 = cache.get("stone.png");
    auto t2 = cache.get("wood.png");
    auto t3 = cache.get("stone.png");

    std::cout << "\n=== 첫 번째 프레임 ===\n";
    t1->draw();
    t2->draw();
    t3->draw();

    std::cout << "\n=== 두 번째 프레임 ===\n";
    t1->draw();
    t2->draw();

    return 0;
}