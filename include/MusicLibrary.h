#pragma once
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include "Song.h"

namespace Model {

// KHOI THU VIEN VA CHI MUC

// lớp quản lý thư viện nhạc và các chỉ mục tra cứu
class MusicLibrary {
public:
    // vector chứa toàn bộ bài hát, phù hợp truy cập tuần tự và ngẫu nhiên nhanh
    std::vector<Song> allSongs;

    // tra cứu theo id trung bình o mot
    std::unordered_map<int, Song*> songIndexByID;

    // tra cứu theo tiêu đề o log n và luôn có thứ tự chữ cái
    std::map<std::string, Song*> songIndexByTitle;

    // tra cứu nghệ sĩ và album theo dạng một nghệ sĩ nhiều bài
    std::unordered_map<std::string, std::vector<Song*>> artistIndex;
    std::unordered_map<std::string, std::vector<Song*>> albumIndex;

    // thêm một bài hát vào mảng gốc
    void addSong(const Song& song);

    // xây dựng lại toàn bộ chỉ mục sau khi đã nạp xong dữ liệu
    void buildIndexes();

    // trả về kích thước thư viện
    int getSize() const { return static_cast<int>(allSongs.size()); }

    // các hàm tra cứu
    Song* findSongByID(int id);
    Song* findSongByTitle(const std::string& title);
    std::vector<Song*> findSongsByArtist(const std::string& artistName);
    std::vector<Song*> findSongsByAlbum(const std::string& albumName);
};

} // namespace Model
