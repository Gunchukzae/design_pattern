#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// ============================================================
// 공통 데이터 구조
// ============================================================
struct Row {
    map<string, string> fields;  // { "name": "Alice", "age": "30" }
};

// ============================================================
// Target: 우리 시스템이 원하는 인터페이스
// Client는 이 인터페이스만 알고 있다
// ============================================================
class DataReader {
public:
    virtual ~DataReader() = default;
    virtual void open(const string& source) = 0;
    virtual vector<Row> readAll() = 0;
    virtual void close() = 0;
};

// ============================================================
// Adaptee 1: 기존 JSON 라이브러리 (외부, 바꿀 수 없음)
// 실제 프로젝트에서는 nlohmann/json 같은 외부 라이브러리
// ============================================================
class JsonLibrary {
public:
    void loadFile(const string& path) {
        cout << "[JsonLibrary] " << path << " 파일 로드" << endl;
    }

    // JSON 특유의 인터페이스: 배열 순회
    int getArraySize() { return 3; }

    map<string, string> getObjectAt(int index) {
        // 실제로는 JSON 파싱 결과를 반환
        if (index == 0) return { {"name", "Alice"}, {"age", "30"}, {"city", "Seoul"} };
        if (index == 1) return { {"name", "Bob"},   {"age", "25"}, {"city", "Busan"} };
        if (index == 2) return { {"name", "Carol"},  {"age", "28"}, {"city", "Incheon"} };
        return {};
    }

    void release() {
        cout << "[JsonLibrary] 리소스 해제" << endl;
    }
};

// ============================================================
// Adaptee 2: 기존 Excel 라이브러리 (외부, 바꿀 수 없음)
// 실제 프로젝트에서는 libxlsxwriter 같은 외부 라이브러리
// Excel 특유의 인터페이스: 행(row)/열(col) 기반
// ============================================================
class ExcelLibrary {
public:
    void openWorkbook(const string& path) {
        cout << "[ExcelLibrary] " << path << " 워크북 오픈" << endl;
    }

    // Excel 특유의 인터페이스: 행/열 인덱스로 접근
    int getRowCount()    { return 4; }  // 1행은 헤더
    int getColumnCount() { return 3; }

    string getCellValue(int row, int col) {
        // 0행: 헤더
        if (row == 0) {
            if (col == 0) return "name";
            if (col == 1) return "age";
            if (col == 2) return "city";
        }
        // 1~3행: 데이터
        vector<vector<string>> data = {
            {"David", "35", "Daegu"},
            {"Eve",   "22", "Daejeon"},
            {"Frank", "40", "Gwangju"}
        };
        return data[row - 1][col];
    }

    void closeWorkbook() {
        cout << "[ExcelLibrary] 워크북 닫기" << endl;
    }
};

// ============================================================
// Adaptee 3: 기존 CSV 라이브러리 (외부, 바꿀 수 없음)
// CSV 특유의 인터페이스: 라인 기반 파싱
// ============================================================
class CsvLibrary {
public:
    void read(const string& path) {
        cout << "[CsvLibrary] " << path << " 읽기 시작" << endl;
    }

    // CSV 특유의 인터페이스: 라인 단위로 반환
    vector<string> getHeaders() {
        return { "name", "age", "city" };
    }

    int getLineCount() { return 2; }

    vector<string> getLine(int index) {
        if (index == 0) return { "Grace", "27", "Suwon" };
        if (index == 1) return { "Henry", "33", "Ulsan" };
        return {};
    }

    void finish() {
        cout << "[CsvLibrary] 읽기 완료" << endl;
    }
};

// ============================================================
// Adapter 1: JsonLibrary → DataReader 변환
// ============================================================
class JsonAdapter : public DataReader {
private:
    JsonLibrary json;

public:
    void open(const string& source) override {
        json.loadFile(source);
    }

    vector<Row> readAll() override {
        vector<Row> rows;
        int size = json.getArraySize();
        for (int i = 0; i < size; i++) {
            Row row;
            row.fields = json.getObjectAt(i);  // JSON 객체를 Row로 변환
            rows.push_back(row);
        }
        return rows;
    }

    void close() override {
        json.release();
    }
};

// ============================================================
// Adapter 2: ExcelLibrary → DataReader 변환
// ============================================================
class ExcelAdapter : public DataReader {
private:
    ExcelLibrary excel;

public:
    void open(const string& source) override {
        excel.openWorkbook(source);
    }

    vector<Row> readAll() override {
        vector<Row> rows;

        // 0행에서 헤더 추출
        int colCount = excel.getColumnCount();
        vector<string> headers;
        for (int col = 0; col < colCount; col++) {
            headers.push_back(excel.getCellValue(0, col));
        }

        // 1행부터 데이터 추출 — 행/열을 key/value로 변환
        int rowCount = excel.getRowCount();
        for (int row = 1; row < rowCount; row++) {
            Row r;
            for (int col = 0; col < colCount; col++) {
                r.fields[headers[col]] = excel.getCellValue(row, col);
            }
            rows.push_back(r);
        }
        return rows;
    }

    void close() override {
        excel.closeWorkbook();
    }
};

// ============================================================
// Adapter 3: CsvLibrary → DataReader 변환
// ============================================================
class CsvAdapter : public DataReader {
private:
    CsvLibrary csv;

public:
    void open(const string& source) override {
        csv.read(source);
    }

    vector<Row> readAll() override {
        vector<Row> rows;
        vector<string> headers = csv.getHeaders();

        // 라인 단위 데이터를 key/value로 변환
        int lineCount = csv.getLineCount();
        for (int i = 0; i < lineCount; i++) {
            vector<string> line = csv.getLine(i);
            Row row;
            for (int j = 0; j < (int)headers.size(); j++) {
                row.fields[headers[j]] = line[j];
            }
            rows.push_back(row);
        }
        return rows;
    }

    void close() override {
        csv.finish();
    }
};

// ============================================================
// Client: DataReader 인터페이스만 사용
// JSON인지 Excel인지 CSV인지 전혀 모름
// ============================================================
void processData(DataReader& reader, const string& source) {
    reader.open(source);

    vector<Row> rows = reader.readAll();
    for (const Row& row : rows) {
        cout << "  이름: " << row.fields.at("name")
             << " | 나이: " << row.fields.at("age")
             << " | 도시: " << row.fields.at("city") << endl;
    }

    reader.close();
}

// ============================================================
// main
// ============================================================
int main() {
    cout << "==========================================" << endl;
    cout << "  JSON 파일 읽기" << endl;
    cout << "==========================================" << endl;
    JsonAdapter jsonAdapter;
    processData(jsonAdapter, "employees.json");

    cout << "\n==========================================" << endl;
    cout << "  Excel 파일 읽기" << endl;
    cout << "==========================================" << endl;
    ExcelAdapter excelAdapter;
    processData(excelAdapter, "employees.xlsx");

    cout << "\n==========================================" << endl;
    cout << "  CSV 파일 읽기" << endl;
    cout << "==========================================" << endl;
    CsvAdapter csvAdapter;
    processData(csvAdapter, "employees.csv");

    return 0;
}
