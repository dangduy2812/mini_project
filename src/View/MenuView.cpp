#include "MenuView.h"
#include <limits>
#include <sstream>
#include <iomanip> 
#include <string>
#include <algorithm> 
#include "MusicPlayer.h" // Đảm bảo đã include để sử dụng enum PlaybackState

// --- HÀM CHÍNH: HIỂN THỊ TRẠNG THÁI (HEADER) ---


void View::MenuView::displayHeader(const Controller::MusicPlayer& player) {
    system("cls"); 

    std::string play_button;
    std::string status_text;

    // Sử dụng enum PlaybackState từ MusicPlayer.h
    if (player.getState() == Controller::PLAYING) {
        play_button = "||"; 
        status_text = ">> PLAYING <<";
    } else if (player.getState() == Controller::PAUSED) {
        play_button = "|>"; 
        status_text = "-- PAUSED --";
    } else { // STOPPED
        play_button = "[]"; 
        status_text = ".. STOPPED ..";
    }

    std::cout << "\n=======================================================================" << std::endl;
    std::cout << "  AUTOMOTIVE MUSIC PLAYER ENGINE CORE (MVC)   | Status: " << status_text << std::endl;
    std::cout << "=======================================================================" << std::endl;
    
    const Song& current = player.getCurrentTrack();
    
    if (current.id != 0) {
        std::cout << "| " << play_button
                  << " | Current Track: " << current.title << " - " << current.artist 
                  << " (Album: " << current.album << ")" << std::endl;
    } else {
        std::cout << "| " << play_button
                  << " | Current Track: (No Song Selected)" << std::endl;
    }
    std::cout << "=======================================================================" << std::endl; 
	
}

// --- HÀM CHÍNH: MENU CHÍNH ---

int View::MenuView::displayMainMenu() {
    int choice = -1;
    std::cout << "\nSelect a feature block:" << std::endl;
    std::cout << "1. Playback Controls (Play/Pause/Stop/Next/Prev)" << std::endl;
    std::cout << "2. Part 2: Accelerate Searches (Index Testing)" << std::endl;
    std::cout << "3. Part 3: Shuffle Manager (Set & Vector)" << std::endl;
    std::cout << "4. Part 4: Generate Smart Playlist (BFS & Set)" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Enter your choice: ";
    
    if (!(std::cin >> choice)) {
        clearInputBuffer();
        choice = -1;
    }
    return choice;
}

// --- HÀM XỬ LÝ: PLAYBACK (P1, P3.1, P4.1) ---

void View::MenuView::handlePlaybackMenu(Controller::MusicPlayer& player) {
    int sub_choice = -1;
    clearInputBuffer(); 

    while (sub_choice != 0) {
        displayHeader(player); 
        
        std::cout << "\n--- PLAYBACK & HISTORY MENU (Part 1 & 4) ---" << std::endl;
        std::cout << "1. Toggle Play/Pause (| > / || )" << std::endl;
        std::cout << "2. Stop Playback" << std::endl;
        std::cout << "3. Select and Play Song by ID (P4.1)" << std::endl;
        std::cout << "4. Play Next Song (Queue) (P1.2)" << std::endl;
        std::cout << "5. Play Previous Song (History) (P3.1)" << std::endl;
        std::cout << "6. Add Album to Queue (P1.3)" << std::endl;
        std::cout << "7. Display Queue & History" << std::endl;
        std::cout << "0. Back to Main Menu" << std::endl;
        std::cout << "Enter choice: ";
       
        if (!(std::cin >> sub_choice)) {
            clearInputBuffer();
            sub_choice = -1;
            continue;
        }

        switch (sub_choice) {
            case 1: player.togglePlayPause(); break;
            case 2: player.stopPlayback(); break;
            case 3: {
                int id;
                std::cout << "Enter Song ID to play: ";
                if (std::cin >> id) {
                    player.selectAndPlaySong(id); 
                } else { clearInputBuffer(); }
                system("pause"); break;
            }
            case 4: player.playNext(); system("pause"); break; 
            case 5: player.playPrevious(); system("pause"); break; 
            case 6: {
                std::string album_name;
                std::cout << "Enter Album Name: ";
                clearInputBuffer();
                std::getline(std::cin, album_name);
                player.addAlbumToQueue(album_name); // Gọi phương thức lớp MusicPlayer đã cập nhật
                system("pause"); break;
            }
            case 7: {
                player.getQueue().displayQueue();
                player.getHistory().displayHistory(); 
                system("pause"); break;
            }
            case 0: break;
            default: displayMessage("Lua chon khong hop le."); system("pause");
        }
    }
}

// --- HÀM XỬ LÝ: TÌM KIẾM (P2) ---
// (Giữ nguyên)
void View::MenuView::handleSearchMenu(Model::MusicLibrary& library) {
    std::string temp_input;
    clearInputBuffer(); 
    
    std::cout << "\n--- Search Menu (Testing Indexes - P2) ---" << std::endl;
    
    // --- 1. Tìm kiếm theo ID (std::unordered_map - O(1)) ---
    std::cout << "1. Find by ID (e.g., 2001): ";
    std::getline(std::cin, temp_input);
    try {
        int id = std::stoi(temp_input);
        Song* song = library.findSongByID(id);
        std::cout << "   -> Result (O(1)): " << (song ? song->title + " - " + song->artist : "Not Found") << std::endl;
    } catch (...) {
        std::cout << "   -> ID khong hop le." << std::endl;
    }

    // --- 2. Tìm kiếm theo Tiêu đề (std::map - O(log n)) ---
    std::cout << "2. Find by Title (e.g., Yellow): ";
    std::getline(std::cin, temp_input);
    Song* song = library.findSongByTitle(temp_input);
    std::cout << "   -> Result (O(log n)): " << (song ? song->title + " by " + song->artist : "Not Found") << std::endl;

    // --- 3. Tìm kiếm theo Nghệ sĩ (std::unordered_map<string, vector<Song*>> - O(1) tra cứu) ---
    std::cout << "3. Find all by Artist (e.g., Coldplay): ";
    std::getline(std::cin, temp_input);
    std::vector<Song*> artistSongs = library.findSongsByArtist(temp_input);
    
    if (!artistSongs.empty()) {
        std::cout << "   -> Result (O(1) tra cuu): Found " << artistSongs.size() << " songs." << std::endl;
        std::cout << "   --- Tracklist ---" << std::endl;
        int index = 1;
        for (const Song* s : artistSongs) {
            std::cout << "   " << index++ << ". [" << s->id << "] " << s->title << " (" << s->album << ")" << std::endl;
        }
        std::cout << "   -------------------" << std::endl;
    } else {
        std::cout << "   -> Result: Artist Not Found or no songs available." << std::endl;
    }
    system("pause");
}

// --- HÀM XỬ LÝ: SMART PLAYLIST (P4.2 - BFS) ---
// (Giữ nguyên)
void View::MenuView::handleSmartPlaylistMenu(Controller::MusicPlayer& player) {
    int sub_choice = -1;
    
    while (sub_choice != 0) {
        displayHeader(player);
        std::cout << "\n--- Generate Smart Playlist (BFS) ---" << std::endl;
        std::cout << "1. Generate Playlist" << std::endl;
        std::cout << "0. Back to Main Menu" << std::endl;
        std::cout << "Enter choice: ";
        
        if (!(std::cin >> sub_choice)) {
            clearInputBuffer();
            sub_choice = -1;
            continue;
        }

        if (sub_choice == 1) {
            int startID;
            int maxSize = 5;
            std::cout << "Enter Start Song ID (e.g., 1001): ";
            if (std::cin >> startID) {
                clearInputBuffer();
                std::cout << "Enter Max Size (e.g., 5): ";
                if (std::cin >> maxSize) {
                    try {
                        Song* startSongPtr = player.getLibrary().findSongByID(startID);
                        if (startSongPtr) {
                            PlaybackQueue smartQueue = player.generateSmartPlaylist(*startSongPtr, maxSize);
                            smartQueue.displayQueue();
                        } else {
                             displayMessage("ID khong tim thay.");
                        }
                    } catch (const std::exception& e) {
                        displayMessage(std::string("Loi: ") + e.what());
                    }
                }
            } else {
                clearInputBuffer();
            }
            system("pause");
        }
    }
}

// --- HÀM XỬ LÝ: SHUFFLE (P3.3) ---
// (Giữ nguyên)
void View::MenuView::handleShuffleMenu(Controller::MusicPlayer& player) {
    int sub_choice = -1;
    
    while (sub_choice != 0) {
        displayHeader(player);
        std::cout << "\n--- Shuffle Manager (P3.3) ---" << std::endl;
        std::cout << "1. Activate Shuffle Mode (from all songs)" << std::endl;
        std::cout << "2. Get Next Shuffled Song" << std::endl;
        std::cout << "0. Back to Main Menu" << std::endl;
        std::cout << "Enter choice: ";
        
        if (!(std::cin >> sub_choice)) {
            clearInputBuffer();
            sub_choice = -1;
            continue;
        }

        switch (sub_choice) {
            case 1: {
                player.startShuffle(player.getLibrary().allSongs); 
                system("pause");
                break;
            }
            case 2: {
                try {
                    Song nextShuffle = player.playNextShuffled();
                    displayMessage("Next Shuffle: " + nextShuffle.title + " by " + nextShuffle.artist);
                } catch (const std::out_of_range& e) {
                    displayMessage(e.what());
                }
                system("pause");
                break;
            }
            case 0: break;
            default: displayMessage("Lua chon khong hop le."); system("pause");
        }
    }
}