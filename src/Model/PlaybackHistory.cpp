#include "PlaybackHistory.h"
#include <iostream>

// thêm bài vào stack lịch sử
void PlaybackHistory::pushSong(const Song& s) {
    st.push(s);
}

// lấy bài trước đó, ném ngoại lệ nếu rỗng
Song PlaybackHistory::playPreviousSong() {
    if (st.empty()) throw std::out_of_range("lich su dang rong");
    Song prev = st.top();
    st.pop();
    return prev;
}

// in lịch sử theo thứ tự từ mới đến cũ
void PlaybackHistory::displayHistory() const {
    std::cout << "\nlich su phat\n";
    if (st.empty()) {
        std::cout << "khong co lich su\n";
        return;
    }
    auto temp = st;
    int i = static_cast<int>(temp.size());
    while (!temp.empty()) {
        const Song& s = temp.top();
        std::cout << i-- << ". " << s.id << " " << s.title << " " << s.artist << "\n";
        temp.pop();
    }
}
