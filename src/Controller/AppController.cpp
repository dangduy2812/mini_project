#include "AppController.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace Model;

// đọc file dữ liệu dạng id|title|artist|album|duration và nạp vào library
void loadLibraryFromSource(MusicLibrary& library, const std::string& filename) {
    std::ifstream file("data/" + filename);
    if (!file.is_open()) {
        std::cerr << "khong mo duoc file du lieu\n";
        return;
    }

    std::string line, seg;
    int count = 0;

    while (std::getline(file, line)) {
        if (line.empty() || line.size() < 5) continue;

        std::stringstream ss(line);
        Song s;

        try {
            if (!std::getline(ss, seg, '|')) continue;
            s.id = std::stoi(seg);
            if (!std::getline(ss, s.title,  '|')) continue;
            if (!std::getline(ss, s.artist, '|')) continue;
            if (!std::getline(ss, s.album,  '|')) continue;
            if (!std::getline(ss, seg,     '|')) continue;
            s.duration = std::stoi(seg);
        } catch (...) {
            std::cerr << "dong du lieu khong hop le bi bo qua\n";
            continue;
        }

        library.addSong(s);
        count++;
    }

    library.buildIndexes();
    std::cout << "da nap " << count << " bai hat va xay chi muc\n";
}

// thêm toàn bộ bài của một album vào cuối queue phát
void addAlbumToQueue(const std::string& albumName,
                     const MusicLibrary& libraryConst,
                     PlaybackQueue& queue) {
    auto& library = const_cast<MusicLibrary&>(libraryConst);
    auto vec = library.findSongsByAlbum(albumName);
    if (vec.empty()) {
        std::cout << "khong tim thay album\n";
        return;
    }
    for (auto* p : vec) {
        if (!p) continue;
        queue.addSong(*p);
    }
    std::cout << "da them " << vec.size() << " bai tu album vao queue\n";
}
