#pragma once
#include <list>
#include <unordered_map>
#include <stdexcept>
#include <iostream>
#include "Song.h"

// KHOI HANG DOI PHAT

// lớp hàng đợi phát dùng danh sách liên kết để chèn xóa o mot và giữ iterator ổn định
class PlaybackQueue {
private:
    // danh sách bài hát theo thứ tự sẽ phát
    std::list<Song> queue;

    // ánh xạ nhanh từ id sang iterator trong danh sách để xóa o mot
    std::unordered_map<int, std::list<Song>::iterator> idToIt;

    // iterator trỏ tới bài hiện tại trong danh sách
    std::list<Song>::iterator currentIt;

    // xóa nếu id đã tồn tại trong danh sách, hỗ trợ tránh trùng
    void removeIfExists(int songId);

public:
    PlaybackQueue();

    // thêm bài vào cuối hàng đợi
    void addSong(const Song& song);

    // xóa một bài theo id nếu có
    void removeSong(int songId);

    // lấy bản sao bài hiện tại, ném ngoại lệ nếu không có
    Song getCurrentSong() const;

    // chuyển sang bài kế tiếp trong danh sách
    void playNext();

    // thêm bài lên đầu hàng đợi và coi như bài hiện tại
    void addSongToFront(const Song& song);

    // in danh sách hàng đợi ra màn hình
    void displayQueue() const;

    // kiểm tra rỗng và lấy kích thước
    bool isEmpty() const { return queue.empty(); }
    size_t getSize() const { return queue.size(); }
};
