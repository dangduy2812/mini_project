#pragma once

#include "MusicPlayer.h"
#include "MusicLibrary.h" 

#include <iostream>

namespace View
{
	class MenuView
	{
	public:
		// Hiển thị trạng thái hiện tại của Player
		static void displayHeader(const Controller::MusicPlayer &player);

		// Menu chính
		static int displayMainMenu();

		// Xử lý các menu chức năng
		static void handleSearchMenu(Model::MusicLibrary &library);	  // P2
		static void handlePlaybackMenu(Controller::MusicPlayer &player);	  // P1, P3.1, P4.1
		static void handleShuffleMenu(Controller::MusicPlayer &player);		  // P3.3
		static void handleSmartPlaylistMenu(Controller::MusicPlayer &player); // P4.2

		// Hàm tiện ích hiển thị thông báo
		static void displayMessage(const std::string &message)
		{
			std::cout << "\n[INFO] " << message << std::endl;
		}

		// Hàm tiện ích để xóa bộ đệm input
		static void clearInputBuffer()
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	};
}
