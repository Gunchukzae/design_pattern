#include <iostream>
#include <string>
#include <map>
using namespace std;

// ============================================================
// Subject 인터페이스
// RealVideo와 ProxyVideo가 동일하게 구현
// → Client는 Proxy인지 Real인지 구분 못 함
// ============================================================
class Video {
public:
    virtual ~Video() = default;
    virtual void play()     = 0;
    virtual void pause()    = 0;
    virtual void showInfo() = 0;
};

// ============================================================
// RealSubject: 실제 영상 객체
// 생성 시 서버에서 다운로드 → 비용이 매우 큼
// ============================================================
class RealVideo : public Video {
private:
    string videoId;
    string title;
    int    duration;   // 초 단위
    long   fileSize;   // bytes

public:
    RealVideo(const string& videoId, const string& title,
              int duration, long fileSize)
        : videoId(videoId), title(title),
          duration(duration), fileSize(fileSize)
    {
        // 객체 생성 시 서버에서 다운로드 (느리고 비쌈)
        cout << "[서버] '" << title << "' 다운로드 중..."
             << " (" << fileSize / 1024 / 1024 << " MB)" << endl;
        cout << "[서버] 다운로드 완료 ✓" << endl;
    }

    void play() override {
        cout << "[플레이어] ▶  재생: " << title
             << " (" << duration / 60 << "분 "
             << duration % 60 << "초)" << endl;
    }

    void pause() override {
        cout << "[플레이어] ⏸  일시정지: " << title << endl;
    }

    void showInfo() override {
        cout << "[영상 정보]"
             << " ID: "       << videoId
             << " | 제목: "   << title
             << " | 길이: "   << duration / 60 << "분 " << duration % 60 << "초"
             << " | 크기: "   << fileSize / 1024 / 1024 << " MB" << endl;
    }

    string getVideoId() const { return videoId; }
};

// ============================================================
// Proxy: Virtual Proxy + Caching Proxy 결합
//
// Virtual Proxy  → 실제로 play()가 불릴 때까지 다운로드 미룸
// Caching Proxy  → 한 번 다운로드한 영상은 캐시에 보관,
//                  같은 영상 재요청 시 서버 요청 없이 반환
// ============================================================
class ProxyVideo : public Video {
private:
    // 캐시: videoId → RealVideo 객체
    // static → 모든 ProxyVideo 인스턴스가 캐시 공유
    static map<string, RealVideo*> cache;

    string videoId;
    string title;
    int    duration;
    long   fileSize;

    RealVideo* getRealVideo() {
        if (cache.find(videoId) == cache.end()) {
            // 캐시에 없으면 처음 다운로드
            cout << "[Proxy] 캐시 미스 → 서버에서 다운로드" << endl;
            cache[videoId] = new RealVideo(videoId, title, duration, fileSize);
        } else {
            // 캐시에 있으면 즉시 반환
            cout << "[Proxy] 캐시 히트 → 즉시 재생 (서버 요청 없음)" << endl;
        }
        return cache[videoId];
    }

public:
    ProxyVideo(const string& videoId, const string& title,
               int duration, long fileSize)
        : videoId(videoId), title(title),
          duration(duration), fileSize(fileSize)
    {
        // ← 아직 다운로드 안 함! (Virtual Proxy 핵심)
        cout << "[Proxy] '" << title << "' 프록시 생성 (다운로드 대기 중)" << endl;
    }

    ~ProxyVideo() {
        // 캐시는 static이라 별도 관리
    }

    static void clearCache() {
        for (auto& pair : cache)
            delete pair.second;
        cache.clear();
        cout << "[Proxy] 캐시 전체 삭제" << endl;
    }

    void play() override {
        // play() 호출 시점에 처음으로 다운로드
        getRealVideo()->play();
    }

    void pause() override {
        if (cache.find(videoId) != cache.end())
            cache[videoId]->pause();
        else
            cout << "[Proxy] 재생 중인 영상 없음" << endl;
    }

    void showInfo() override {
        // showInfo는 다운로드 없이 프록시가 직접 처리
        cout << "[영상 정보 (캐시됨)]"
             << " ID: "     << videoId
             << " | 제목: " << title
             << " | 길이: " << duration / 60 << "분 " << duration % 60 << "초"
             << " | 크기: " << fileSize / 1024 / 1024 << " MB" << endl;
    }
};

// static 멤버 초기화
map<string, RealVideo*> ProxyVideo::cache;

// ============================================================
// Client: Video 인터페이스만 사용
// Proxy인지 Real인지 전혀 모름
// ============================================================
void clientPlay(Video& video) {
    video.showInfo();
    video.play();
    video.pause();
}

int main() {
    cout << "============================================" << endl;
    cout << "  영상 목록 불러오기 (프록시만 생성)" << endl;
    cout << "============================================\n" << endl;

    // 영상 목록 표시 단계 — 아직 다운로드 없음
    ProxyVideo video1("V001", "C++ 디자인패턴 완전정복", 3600, 1024LL * 1024 * 800);
    ProxyVideo video2("V002", "객체지향 프로그래밍 입문", 2400, 1024LL * 1024 * 500);
    ProxyVideo video3("V003", "알고리즘 마스터 클래스",   5400, 1024LL * 1024 * 1200);

    cout << "\n[영상 목록]" << endl;
    video1.showInfo();  // 다운로드 없이 정보만 표시
    video2.showInfo();
    video3.showInfo();

    cout << "\n============================================" << endl;
    cout << "  video1 첫 번째 재생 (서버 다운로드)" << endl;
    cout << "============================================\n" << endl;

    video1.play();   // ← 이 시점에 처음 다운로드

    cout << "\n============================================" << endl;
    cout << "  video1 두 번째 재생 (캐시 히트)" << endl;
    cout << "============================================\n" << endl;

    video1.play();   // ← 캐시에서 즉시 재생

    cout << "\n============================================" << endl;
    cout << "  video2 재생 (서버 다운로드)" << endl;
    cout << "============================================\n" << endl;

    video2.play();

    cout << "\n============================================" << endl;
    cout << "  video2 다시 재생 (캐시 히트)" << endl;
    cout << "============================================\n" << endl;

    video2.play();   // ← 캐시에서 즉시 재생

    cout << "\n============================================" << endl;
    cout << "  캐시 초기화 후 video1 재재생" << endl;
    cout << "============================================\n" << endl;

    ProxyVideo::clearCache();
    video1.play();   // ← 캐시 없으니 다시 다운로드

    ProxyVideo::clearCache();
    return 0;
}
