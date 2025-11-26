#include <iostream>
#include <limits>
#include "AppController.h" // Chứa loadLibraryFromSource
#include "MusicLibrary.h"  // Model: Thư viện
#include "MusicPlayer.h"   // Controller/Model: Trình phát nhạc
#include "MenuView.h"	   // View: Giao diện người dùng

using namespace std;

// Tên file dữ liệu nhạc
const std::string SONG_DATA_FILE = "songs.txt";

int main()
{
	// 1. Khởi tạo Thư viện (Model)
	Model::MusicLibrary library;

	// 2. Tải dữ liệu và xây dựng chỉ mục (Controller Logic)
	cout << "--- Khoi dong He thong Nghe nhac ---" << endl;
	loadLibraryFromSource(library, SONG_DATA_FILE);
	cout << "-------------------------------------" << endl;

	if (library.allSongs.empty())
	{
		cerr << "FATAL ERROR: Khong tai duoc bai hat nao. Thoat ung dung." << endl;
		return 1;
	}

	// 3. Khởi tạo Trình phát (Controller/Model)
	Controller::MusicPlayer player(library);

	// Đặt bài hát mặc định (tùy chọn)
	// player.selectAndPlaySong(1001);

	int choice = -1;

	// Vòng lặp Menu chính
	while (choice != 0)
	{

		// Luôn hiển thị trạng thái hiện tại
		View::MenuView::displayHeader(player);
		std::cout << "Loaded " << library.getSize() << " songs." << std::endl;
		choice = View::MenuView::displayMainMenu();

		switch (choice)
		{
		case 1:
			View::MenuView::handlePlaybackMenu(player);
			break;
		case 2:
			View::MenuView::handleSearchMenu(library);
			break;
		case 3:
			// Để test Shuffle, ta khởi tạo danh sách xáo trộn từ tất cả bài hát
			// Chức năng này sẽ được gọi từ Menu/Controller, ta gọi thủ công ở đây cho chắc chắn
			// player.startShuffle(library.allSongs);
			View::MenuView::handleShuffleMenu(player);
			break;
		case 4:
			View::MenuView::handleSmartPlaylistMenu(player);
			break;
		case 0:
			View::MenuView::displayMessage("Da thoat ung dung. Tam biet!");
			break;
		default:
			View::MenuView::displayMessage("Lua chon khong hop le.");
			break;
		}

		// Ngăn không cho menu quay lại quá nhanh sau khi xử lý (tùy chọn)
		if (choice != 0 && choice >= 1 && choice <= 4)
		{
			// system("pause"); // Đã có pause trong các hàm handle...
		}
	}

	return 0;
}