#pragma once
#include <stack>
#include <stdexcept>
#include "Song.h"

class PlaybackHistory {
private:
    // P3.1: Sử dụng std::stack cho LIFO (Last-In, First-Out).
    // Phù hợp hoàn hảo cho nút "Back" vì bài hát mới nhất (Last-In) sẽ được phát lại đầu tiên (First-Out).
    // Các thao tác push/pop đều có độ phức tạp O(1).
    std::stack<Song> historyStack;
	std::stack<Song> forwardStack; // xử lý tình huống mất bài
public:
    // Thao tác chính: push (khi bài hát kết thúc) -> Độ phức tạp O(1)
    void pushSong(const Song& song); 
    // Thao tác chính: pop (khi nhấn nút Back) -> Độ phức tạp O(1)
    Song playPreviousSong(); 
    bool isEmpty() const { return historyStack.empty(); }

    void displayHistory() const;
};