#pragma once
#include <vector>
#include <set>
#include <algorithm> 
#include <random>    
#include "Song.h"

class ShuffleManager {
private:
    std::vector<Song> originalPlaylist;
    // P3.3: Danh sách đã xáo trộn
    std::vector<Song> shuffledList;
    // P3.3: Dùng std::set để lưu trữ ID của các bài đã chơi (kiểm tra hiệu quả O(log n))
    std::set<int> playedSongIDs; 
    int currentShuffleIndex;
public:
    ShuffleManager() : currentShuffleIndex(0) {}

    void setupShuffle(const std::vector<Song>& playlist);
    Song getNextShuffleSong();
};