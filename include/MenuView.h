#pragma once
#include "MusicPlayer.h"
#include "MusicLibrary.h"
#include <iostream>
#include <limits>

// KHOI GIAO DIEN DON GIAN

namespace View {

class MenuView {
public:
    // in phần đầu trạng thái hiện tại
    static void displayHeader(const Controller::MusicPlayer& player);

    // hiển thị menu chính và lấy lựa chọn
    static int displayMainMenu();

    // menu tìm kiếm chỉ mục
    static void handleSearchMenu(Model::MusicLibrary& library);

    // menu điều khiển phát nhạc và lịch sử
    static void handlePlaybackMenu(Controller::MusicPlayer& player);

    // menu xáo trộn
    static void handleShuffleMenu(Controller::MusicPlayer& player);

    // menu smart playlist bfs
    static void handleSmartPlaylistMenu(Controller::MusicPlayer& player);

    // tiện ích in thông báo
    static void displayMessage(const std::string& message) {
        std::cout << "\ninfo " << message << std::endl;
    }

    // xóa bộ đệm nhập để tránh kẹt dòng
    static void clearInputBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
};

} // namespace View
