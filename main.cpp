#include <iostream>
#include "AppController.h"
#include "MusicLibrary.h"
#include "MusicPlayer.h"
#include "MenuView.h"

// CHUONG TRINH CHINH

int main() {
    // nạp thư viện
    Model::MusicLibrary library;
    std::cout << "khoi dong engine nghe nhac\n";
    loadLibraryFromSource(library, "songs.txt");

    if (library.allSongs.empty()) {
        std::cout << "khong co du lieu bai hat, thoat chuong trinh\n";
        return 1;
    }

    // tạo trình phát
    Controller::MusicPlayer player(library);

    int choice = -1;
    while (choice != 0) {
        View::MenuView::displayHeader(player);
        std::cout << "da nap " << library.getSize() << " bai hat\n";
        choice = View::MenuView::displayMainMenu();

        switch (choice) {
        case 1: View::MenuView::handlePlaybackMenu(player); break;
        case 2: View::MenuView::handleSearchMenu(library);  break;
        case 3: View::MenuView::handleShuffleMenu(player);  break;
        case 4: View::MenuView::handleSmartPlaylistMenu(player); break;
        case 0: View::MenuView::displayMessage("thoat chuong trinh"); break;
        default: View::MenuView::displayMessage("lua chon khong hop le"); break;
        }
    }
    return 0;
}
