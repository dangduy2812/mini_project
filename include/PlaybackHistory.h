#pragma once
#include <stack>
#include <stdexcept>
#include "Song.h"

// KHOI LICH SU

// lớp lịch sử dùng stack để hỗ trợ quay lại theo nguyên tắc vào sau ra trước
class PlaybackHistory {
private:
    std::stack<Song> st;

public:
    // đẩy một bài vào lịch sử khi vừa phát xong
    void pushSong(const Song& s);

    // lấy bài trước đó để phát lại, ném ngoại lệ nếu rỗng
    Song playPreviousSong();

    // kiểm tra rỗng
    bool isEmpty() const { return st.empty(); }

    // in danh sách lịch sử
    void displayHistory() const;
};
