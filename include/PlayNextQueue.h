#pragma once
#include <queue>
#include <stdexcept>
#include "Song.h"

// KHOI PLAY NEXT

// hàng đợi play next theo nguyên tắc vào trước ra trước
class PlayNextQueue {
private:
    std::queue<Song> q;

public:
    // thêm bài vào cuối hàng
    void enqueue(const Song& s) { q.push(s); }

    // lấy bài ở đầu hàng và loại khỏi hàng, ném ngoại lệ nếu rỗng
    Song dequeue() {
        if (q.empty()) throw std::out_of_range("hang play next rong");
        Song s = q.front(); q.pop(); return s;
    }

    // xem bài ở đầu hàng mà không loại khỏi hàng, ném ngoại lệ nếu rỗng
    const Song& front() const {
        if (q.empty()) throw std::out_of_range("hang play next rong");
        return q.front();
    }

    // tiện ích trạng thái
    bool isEmpty() const { return q.empty(); }
    size_t size() const { return q.size(); }
    void clear() { while (!q.empty()) q.pop(); }

    // các alias để tương thích nếu bạn từng dùng theo phong cách std queue
    bool empty() const { return q.empty(); }
    void push(const Song& s) { q.push(s); }
    void pop() {
        if (q.empty()) throw std::out_of_range("hang play next rong");
        q.pop();
    }
    Song& front() {
        if (q.empty()) throw std::out_of_range("hang play next rong");
        return q.front();
    }
};
