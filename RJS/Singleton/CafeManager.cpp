#include "CafeManager.h"

CafeManager& CafeManager::getInstance() {
    static CafeManager instance;
    return instance;
}

CafeManager::CafeManager() : orderCount(0) {
    std::cout << "=== 카페 시스템 가동 ===" << std::endl;
}

CafeManager::~CafeManager() {
    std::cout << "=== 카페 시스템 종료 ===" << std::endl;
}

void CafeManager::processOrder(std::string menu) {
    std::lock_guard<std::mutex> lock(mtx);
    orderCount++;
    std::cout << "[주문] " << menu << " 처리 중... (현재 누적 주문: "
        << orderCount << ")" << std::endl;
}
