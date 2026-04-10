#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

// ============================================================
// Component: 수식 노드 추상 클래스
// ============================================================
class Expression {
public:
    virtual double evaluate() = 0;
    virtual string toString() = 0;
    virtual ~Expression() {}
};

// ============================================================
// Leaf: 숫자 (단말 노드)
// ============================================================
class Number : public Expression {
    double value;
public:
    Number(double value) : value(value) {}

    double evaluate() override {
        return value;
    }

    string toString() override {
        // 정수면 정수로, 소수면 소수로 출력
        if (value == (int)value)
            return to_string((int)value);
        return to_string(value);
    }
};

// ============================================================
// Composite: 이항 연산자 노드 (자식 2개 고정)
// ============================================================
class BinaryOp : public Expression {
    char op;
    Expression* left;
    Expression* right;
public:
    BinaryOp(char op, Expression* left, Expression* right)
        : op(op), left(left), right(right) {}

    double evaluate() override {
        double l = left->evaluate();
        double r = right->evaluate();
        switch (op) {
            case '+': return l + r;
            case '-': return l - r;
            case '*': return l * r;
            case '/':
                if (r == 0) throw runtime_error("Division by zero");
                return l / r;
            default:
                throw runtime_error("Unknown operator");
        }
    }

    string toString() override {
        return "(" + left->toString() + " " + op + " " + right->toString() + ")";
    }

    ~BinaryOp() {
        delete left;
        delete right;
    }
};

// ============================================================
// Composite: 단항 연산자 노드 (자식 1개, 부호 반전)
// ============================================================
class UnaryMinus : public Expression {
    Expression* operand;
public:
    UnaryMinus(Expression* operand) : operand(operand) {}

    double evaluate() override {
        return -operand->evaluate();
    }

    string toString() override {
        return "(-" + operand->toString() + ")";
    }

    ~UnaryMinus() {
        delete operand;
    }
};

// ============================================================
// main: 수식 트리 구성 및 평가
// ============================================================
int main() {
    cout << "=== Composite 패턴 - 수식 트리 ===" << endl << endl;

    // 예제 1: (3 + 4) * 2
    // 트리 구조:
    //        *
    //       / \
    //      +   2
    //     / \
    //    3   4
    Expression* expr1 = new BinaryOp('*',
        new BinaryOp('+',
            new Number(3),
            new Number(4)
        ),
        new Number(2)
    );

    cout << "[예제 1]" << endl;
    cout << "수식: " << expr1->toString() << endl;
    cout << "결과: " << expr1->evaluate() << endl << endl;

    // 예제 2: (10 - 2) / (1 + 3)
    // 트리 구조:
    //        /
    //       / \
    //      -   +
    //     / \ / \
    //    10 2 1  3
    Expression* expr2 = new BinaryOp('/',
        new BinaryOp('-',
            new Number(10),
            new Number(2)
        ),
        new BinaryOp('+',
            new Number(1),
            new Number(3)
        )
    );

    cout << "[예제 2]" << endl;
    cout << "수식: " << expr2->toString() << endl;
    cout << "결과: " << expr2->evaluate() << endl << endl;

    // 예제 3: -(5 * 3) + 20
    // 트리 구조:
    //        +
    //       / \
    //     (-)  20
    //      |
    //      *
    //     / \
    //    5   3
    Expression* expr3 = new BinaryOp('+',
        new UnaryMinus(
            new BinaryOp('*',
                new Number(5),
                new Number(3)
            )
        ),
        new Number(20)
    );

    cout << "[예제 3]" << endl;
    cout << "수식: " << expr3->toString() << endl;
    cout << "결과: " << expr3->evaluate() << endl << endl;

    // 클라이언트는 Number인지 BinaryOp인지 구분 없이
    // Expression* 인터페이스만으로 evaluate(), toString() 호출 가능
    cout << "=== 다형성 확인: Expression* 배열로 일괄 평가 ===" << endl;
    vector<Expression*> exprs = { expr1, expr2, expr3 };
    for (int i = 0; i < (int)exprs.size(); i++) {
        cout << "수식 " << i + 1 << ": "
             << exprs[i]->toString()
             << " = " << exprs[i]->evaluate() << endl;
    }

    delete expr1;
    delete expr2;
    delete expr3;

    return 0;
}
