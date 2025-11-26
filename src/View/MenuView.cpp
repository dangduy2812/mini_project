#include "MenuView.h"
#include "AppController.h"
#include <string>

using namespace View;

// in trạng thái tiêu đề, không xóa màn hình theo yêu cầu
void MenuView::displayHeader(const Controller::MusicPlayer& player) {
    std::string status;
    if (player.getState() == Controller::PLAYING) status = "dang phat";
    else if (player.getState() == Controller::PAUSED) status = "tam dung";
    else status = "dung";

    std::cout << "\ntrang thai " << status << "\n";
    const Song& cur = player.getCurrentTrack();
    if (cur.id != 0) {
        std::cout << "bai hien tai " << cur.title << " - " << cur.artist << " album " << cur.album << "\n";
    } else {
        std::cout << "chua chon bai hat\n";
    }
    std::cout << "------------------------------\n";
}

// hiển thị menu chính
int MenuView::displayMainMenu() {
    int c = -1;
    std::cout << "\nchon chuc nang\n";
    std::cout << "1 dieu khien phat nhac\n";
    std::cout << "2 tim kiem chi muc\n";
    std::cout << "3 che do shuffle\n";
    std::cout << "4 smart playlist bfs\n";
    std::cout << "0 thoat\n";
    std::cout << "nhap lua chon ";
    if (!(std::cin >> c)) { clearInputBuffer(); c = -1; }
    return c;
}

// menu điều khiển phát nhạc
void MenuView::handlePlaybackMenu(Controller::MusicPlayer& player) {
    int c = -1; clearInputBuffer();
    while (c != 0) {
        displayHeader(player);
        std::cout << "\ndieu khien phat\n";
        std::cout << "1 chuyen doi play pause\n";
        std::cout << "2 dung phat\n";
        std::cout << "3 chon va phat theo id\n";
        std::cout << "4 phat bai tiep theo\n";
        std::cout << "5 phat bai truoc do\n";
        std::cout << "6 them album vao queue\n";
        std::cout << "7 hien thi queue va lich su\n";
        std::cout << "8 danh dau play next theo id\n";
        std::cout << "0 quay lai\n";
        std::cout << "nhap lua chon ";
        if (!(std::cin >> c)) { clearInputBuffer(); c = -1; continue; }

        switch (c) {
        case 1: player.togglePlayPause(); break;
        case 2: player.stopPlayback(); break;
        case 3: {
            int id; std::cout << "nhap id ";
            if (std::cin >> id) player.selectAndPlaySong(id);
            else clearInputBuffer();
            system("pause");
            break;
        }
        case 4:
            player.playNext();
            system("pause");
            break;
        case 5:
            player.playPrevious();
            system("pause");
            break;
        case 6: {
            std::string album;
            std::cout << "nhap ten album ";
            clearInputBuffer();
            std::getline(std::cin, album);
            addAlbumToQueue(album, player.getLibrary(), player.getQueue());
            system("pause");
            break;
        }
        case 7:
            player.getQueue().displayQueue();
            player.getHistory().displayHistory();
            system("pause");
            break;
        case 8: {
            int id; std::cout << "nhap id de play next ";
            if (std::cin >> id) player.markPlayNext(id);
            else clearInputBuffer();
            system("pause");
            break;
        }
        case 0: break;
        default: displayMessage("lua chon khong hop le");
        }
    }
}

// menu tìm kiếm các chỉ mục
void MenuView::handleSearchMenu(Model::MusicLibrary& library) {
    clearInputBuffer();
    std::string s;

    std::cout << "\nmenu tim kiem\n";

    std::cout << "nhap id ";
    std::getline(std::cin, s);
    try {
        int id = std::stoi(s);
        Song* p = library.findSongByID(id);
        std::cout << "ket qua " << (p ? p->title + " - " + p->artist : std::string("khong tim thay")) << "\n";
    } catch (...) {
        std::cout << "id khong hop le\n";
    }

    std::cout << "nhap tieu de ";
    std::getline(std::cin, s);
    if (auto* p = library.findSongByTitle(s))
        std::cout << "ket qua " << p->title << " by " << p->artist << "\n";
    else
        std::cout << "khong tim thay\n";

    std::cout << "nhap ten nghe si ";
    std::getline(std::cin, s);
    auto vec = library.findSongsByArtist(s);
    if (vec.empty()) {
        std::cout << "khong co bai nao\n";
    } else {
        int i = 1;
        for (auto* x : vec) {
            std::cout << i++ << ". " << x->id << " " << x->title << " " << x->album << "\n";
        }
    }
    system("pause");
}

// menu smart playlist bfs
void MenuView::handleSmartPlaylistMenu(Controller::MusicPlayer& player) {
    int c = -1;
    while (c != 0) {
        displayHeader(player);
        std::cout << "\nsmart playlist bfs\n";
        std::cout << "1 tao danh sach\n";
        std::cout << "0 quay lai\n";
        std::cout << "nhap lua chon ";
        if (!(std::cin >> c)) { clearInputBuffer(); c = -1; continue; }

        if (c == 1) {
            int startID; int maxSize = 5;
            std::cout << "nhap id bat dau ";
            if (std::cin >> startID) {
                clearInputBuffer();
                std::cout << "nhap kich thuoc toi da ";
                if (std::cin >> maxSize) {
                    if (auto* start = player.getLibrary().findSongByID(startID)) {
                        auto smartQ = player.generateSmartPlaylist(*start, maxSize);
                        smartQ.displayQueue();
                    } else {
                        displayMessage("khong tim thay id");
                    }
                }
            } else {
                clearInputBuffer();
            }
            system("pause");
        }
    }
}

// menu xáo trộn
void MenuView::handleShuffleMenu(Controller::MusicPlayer& player) {
    int c = -1;
    while (c != 0) {
        displayHeader(player);
        std::cout << "\nche do shuffle\n";
        std::cout << "1 bat shuffle tu toan bo thu vien\n";
        std::cout << "2 lay bai shuffle ke tiep\n";
        std::cout << "0 quay lai\n";
        std::cout << "nhap lua chon ";
        if (!(std::cin >> c)) { clearInputBuffer(); c = -1; continue; }

        switch (c) {
        case 1:
            player.startShuffle(player.getLibrary().allSongs);
            system("pause");
            break;
        case 2:
            try {
                {
                    Song s = player.playNextShuffled();
                    displayMessage(std::string("shuffle ") + s.title + " by " + s.artist);
                }
            } catch (const std::out_of_range& e) {
                displayMessage(e.what());
            }
            system("pause");
            break;
        case 0: break;
        default: displayMessage("lua chon khong hop le");
        }
    }
}
