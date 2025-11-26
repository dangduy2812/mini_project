#pragma once
#include <vector>
#include <set>
#include <algorithm>
#include <random>
#include "Song.h"

// KHOI SHUFFLE

// lớp xáo trộn không lặp tức thời
// ý tưởng thuật toán
// tạo bản sao vector bài hát rồi xáo trộn
// dùng set lưu các id đã phát trong chu kỳ hiện tại
// khi lấy bài tiếp theo nếu id đã có trong set thì bỏ qua và xét bài kế
// khi set có đủ số lượng bằng danh sách thì xóa để bắt đầu chu kỳ mới
class ShuffleManager {
private:
    std::vector<Song> shuffled;
    std::set<int> played;
    int idx = 0;

public:
    // thiết lập danh sách xáo trộn từ một playlist
    void setupShuffle(const std::vector<Song>& playlist);

    // trả về bài xáo trộn tiếp theo, ném ngoại lệ nếu rỗng
    Song getNextShuffleSong();
};
