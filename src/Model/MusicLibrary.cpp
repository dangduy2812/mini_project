#include "MusicLibrary.h"
#include <iostream>

using namespace Model;

// thêm bài hát vào vector chính
void MusicLibrary::addSong(const Song& song) {
    allSongs.push_back(song);
}

// xây dựng lại toàn bộ chỉ mục dựa trên mảng allSongs
void MusicLibrary::buildIndexes() {
    songIndexByID.clear();
    songIndexByTitle.clear();
    artistIndex.clear();
    albumIndex.clear();

    // lặp một lần qua toàn bộ mảng để điền các chỉ mục
    for (auto& s : allSongs) {
        songIndexByID[s.id] = &s;
        songIndexByTitle[s.title] = &s;
        artistIndex[s.artist].push_back(&s);
        albumIndex[s.album].push_back(&s);
    }
}

// tra cứu theo id với độ phức tạp trung bình o mot
Song* MusicLibrary::findSongByID(int id) {
    auto it = songIndexByID.find(id);
    return it == songIndexByID.end() ? nullptr : it->second;
}

// tra cứu theo tiêu đề với o log n
Song* MusicLibrary::findSongByTitle(const std::string& title) {
    auto it = songIndexByTitle.find(title);
    return it == songIndexByTitle.end() ? nullptr : it->second;
}

// lấy toàn bộ bài theo nghệ sĩ, tra bảng băm rồi trả về danh sách con trỏ
std::vector<Song*> MusicLibrary::findSongsByArtist(const std::string& artistName) {
    auto it = artistIndex.find(artistName);
    return it == artistIndex.end() ? std::vector<Song*>{} : it->second;
}

// lấy toàn bộ bài theo album, dùng để add album vào queue và cho smart playlist
std::vector<Song*> MusicLibrary::findSongsByAlbum(const std::string& albumName) {
    auto it = albumIndex.find(albumName);
    return it == albumIndex.end() ? std::vector<Song*>{} : it->second;
}
