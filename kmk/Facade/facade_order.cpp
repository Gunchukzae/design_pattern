#include <iostream>
#include <string>
using namespace std;

// ============================================================
// 서브시스템들 — 복잡하고 각자 다른 인터페이스를 가짐
// Client는 이 클래스들을 직접 알 필요가 없다
// ============================================================

class InventorySystem {
public:
    bool checkStock(const string& productName, int quantity) {
        cout << "[재고시스템] '" << productName << "' " << quantity << "개 재고 확인 중..." << endl;
        // 실제로는 DB 조회
        if (productName == "품절상품") {
            cout << "[재고시스템] 재고 부족!" << endl;
            return false;
        }
        cout << "[재고시스템] 재고 확인 완료 (충분)" << endl;
        return true;
    }

    void reserveStock(const string& productName, int quantity) {
        cout << "[재고시스템] '" << productName << "' " << quantity << "개 재고 예약 완료" << endl;
    }

    void releaseStock(const string& productName, int quantity) {
        cout << "[재고시스템] '" << productName << "' " << quantity << "개 재고 예약 해제" << endl;
    }
};

class PaymentSystem {
public:
    bool authenticate(const string& cardNumber) {
        cout << "[결제시스템] 카드 인증 중... (" << cardNumber << ")" << endl;
        // 실제로는 카드사 API 호출
        cout << "[결제시스템] 카드 인증 완료" << endl;
        return true;
    }

    bool charge(const string& cardNumber, double amount) {
        cout << "[결제시스템] " << amount << "원 결제 요청 중..." << endl;
        cout << "[결제시스템] 결제 승인 완료 (승인번호: A123456)" << endl;
        return true;
    }

    void refund(const string& cardNumber, double amount) {
        cout << "[결제시스템] " << amount << "원 환불 처리 완료" << endl;
    }
};

class PackagingSystem {
public:
    string pack(const string& productName, int quantity) {
        cout << "[포장시스템] '" << productName << "' " << quantity << "개 포장 중..." << endl;
        cout << "[포장시스템] 포장 완료 (운송장번호: BOX-20260403)" << endl;
        return "BOX-20260403";
    }
};

class DeliverySystem {
public:
    string schedule(const string& boxId, const string& address) {
        cout << "[배송시스템] " << boxId << " → '" << address << "' 배송 예약 중..." << endl;
        cout << "[배송시스템] 배송 예약 완료 (예상 도착: 내일 오후 3시)" << endl;
        return "TRACK-789";
    }
};

class NotificationSystem {
public:
    void sendSMS(const string& phone, const string& message) {
        cout << "[알림시스템] SMS → " << phone << " : " << message << endl;
    }

    void sendEmail(const string& email, const string& message) {
        cout << "[알림시스템] 이메일 → " << email << " : " << message << endl;
    }
};

// ============================================================
// Facade: 복잡한 주문 과정을 단순한 메서드 하나로
// Client는 이것만 알면 된다
// ============================================================
class OrderFacade {
private:
    InventorySystem    inventory;
    PaymentSystem      payment;
    PackagingSystem    packaging;
    DeliverySystem     delivery;
    NotificationSystem notification;

public:
    // 주문 전체 흐름을 하나로 묶음
    bool placeOrder(const string& productName,
                    int           quantity,
                    double        price,
                    const string& cardNumber,
                    const string& address,
                    const string& phone,
                    const string& email)
    {
        cout << "\n===== 주문 시작: " << productName << " =====\n" << endl;

        // 1. 재고 확인
        if (!inventory.checkStock(productName, quantity)) {
            notification.sendSMS(phone, "죄송합니다. 재고가 부족하여 주문이 취소되었습니다.");
            return false;
        }

        // 2. 재고 예약
        inventory.reserveStock(productName, quantity);

        // 3. 결제 인증
        cout << endl;
        if (!payment.authenticate(cardNumber)) {
            inventory.releaseStock(productName, quantity);
            notification.sendSMS(phone, "카드 인증 실패로 주문이 취소되었습니다.");
            return false;
        }

        // 4. 결제 처리
        double totalPrice = price * quantity;
        if (!payment.charge(cardNumber, totalPrice)) {
            inventory.releaseStock(productName, quantity);
            notification.sendSMS(phone, "결제 실패로 주문이 취소되었습니다.");
            return false;
        }

        // 5. 포장
        cout << endl;
        string boxId = packaging.pack(productName, quantity);

        // 6. 배송 예약
        cout << endl;
        string trackingId = delivery.schedule(boxId, address);

        // 7. 고객 알림
        cout << endl;
        notification.sendSMS(phone,
            "주문 완료! 운송장번호: " + trackingId + " / 내일 오후 3시 도착 예정");
        notification.sendEmail(email,
            "'" + productName + "' 주문이 완료되었습니다. 결제금액: " + to_string((int)totalPrice) + "원");

        cout << "\n===== 주문 완료! =====\n" << endl;
        return true;
    }

    // 취소도 단순하게
    void cancelOrder(const string& productName,
                     int           quantity,
                     double        price,
                     const string& cardNumber,
                     const string& phone)
    {
        cout << "\n===== 주문 취소: " << productName << " =====\n" << endl;
        inventory.releaseStock(productName, quantity);
        payment.refund(cardNumber, price * quantity);
        notification.sendSMS(phone, "주문이 취소되었습니다. 환불은 3~5일 내 처리됩니다.");
        cout << "\n===== 취소 완료! =====\n" << endl;
    }
};

// ============================================================
// Client: OrderFacade만 알면 된다
// 재고/결제/포장/배송/알림 시스템을 전혀 몰라도 됨
// ============================================================
int main() {
    OrderFacade order;

    // 정상 주문
    order.placeOrder(
        "무선 키보드",   // 상품명
        2,               // 수량
        89000,           // 단가
        "1234-5678",     // 카드번호
        "서울시 강남구", // 배송지
        "010-1234-5678", // 전화번호
        "user@email.com" // 이메일
    );

    // 재고 없는 주문 (실패 케이스)
    order.placeOrder(
        "품절상품",
        1,
        50000,
        "1234-5678",
        "서울시 강남구",
        "010-1234-5678",
        "user@email.com"
    );

    // 주문 취소
    order.cancelOrder(
        "무선 키보드",
        2,
        89000,
        "1234-5678",
        "010-1234-5678"
    );

    return 0;
}
