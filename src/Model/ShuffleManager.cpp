#include "ShuffleManager.h"
#include <chrono>
#include <stdexcept>

// khởi tạo danh sách xáo trộn và reset trạng thái
void ShuffleManager::setupShuffle(const std::vector<Song>& playlist) {
    shuffled = playlist;
    played.clear();
    idx = 0;

    // dùng seed theo thời gian để xáo ngẫu nhiên
    unsigned seed = static_cast<unsigned>(
        std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(shuffled.begin(), shuffled.end(), std::default_random_engine(seed));
}

// lấy bài xáo trộn tiếp theo, đảm bảo không lặp trong cùng chu kỳ
Song ShuffleManager::getNextShuffleSong() {
    if (shuffled.empty())
        throw std::out_of_range("danh sach shuffle rong");

    if (played.size() == shuffled.size()) {
        played.clear();
        idx = 0;
    }

    // bỏ qua các phần tử đã phát trong chu kỳ
    while (played.count(shuffled[idx].id)) {
        idx = (idx + 1) % shuffled.size();
    }

    Song next = shuffled[idx];
    played.insert(next.id);
    idx = (idx + 1) % shuffled.size();
    return next;
}
