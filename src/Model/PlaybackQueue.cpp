#include "PlaybackQueue.h"

// khởi tạo với iterator ở trạng thái end
PlaybackQueue::PlaybackQueue() : currentIt(queue.end()) {}

// xóa nếu id đã có trong danh sách, cập nhật iterator hiện tại nếu cần
void PlaybackQueue::removeIfExists(int songId) {
    auto f = idToIt.find(songId);
    if (f == idToIt.end()) return;

    auto it = f->second;
    if (it == currentIt) {
        currentIt = queue.erase(it);
        if (currentIt == queue.end() && !queue.empty()) currentIt = queue.begin();
    } else {
        queue.erase(it);
    }
    idToIt.erase(f);
}

// thêm bài vào cuối, nếu là phần tử đầu tiên thì đặt làm hiện tại
void PlaybackQueue::addSong(const Song& song) {
    queue.push_back(song);
    auto it = std::prev(queue.end());
    idToIt[song.id] = it;

    if (queue.size() == 1) currentIt = queue.begin();
}

// xóa bài theo id
void PlaybackQueue::removeSong(int songId) {
    removeIfExists(songId);
}

// trả về bài hiện tại, ném ngoại lệ nếu không có
Song PlaybackQueue::getCurrentSong() const {
    if (queue.empty() || currentIt == queue.end())
        throw std::out_of_range("khong co bai hien tai trong hang doi");
    return *currentIt;
}

// chuyển sang bài kế tiếp, xóa bài cũ khỏi danh sách và ánh xạ
void PlaybackQueue::playNext() {
    if (queue.empty() || currentIt == queue.end()) return;

    idToIt.erase(currentIt->id);
    currentIt = queue.erase(currentIt);

    if (currentIt == queue.end() && !queue.empty())
        currentIt = queue.begin();
}

// thêm bài lên đầu để phát ngay, tránh trùng id nếu đã có
void PlaybackQueue::addSongToFront(const Song& song) {
    removeIfExists(song.id);
    queue.push_front(song);
    currentIt = queue.begin();
    idToIt[song.id] = currentIt;
}

// in toàn bộ hàng đợi, đánh dấu bài hiện tại
void PlaybackQueue::displayQueue() const {
    std::cout << "hang doi phat size " << queue.size() << "\n";
    int idx = 1;
    for (auto it = queue.begin(); it != queue.end(); ++it, ++idx) {
        bool isCur = currentIt != queue.end() && it == currentIt;
        std::cout << (isCur ? " -> " : "    ") << idx << ". " << it->title << " - " << it->artist << "\n";
    }
}
