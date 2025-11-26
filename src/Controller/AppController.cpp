#include "AppController.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

void loadLibraryFromSource(Model::MusicLibrary &library, const std::string &filename)
{
	std::ifstream file("data/" + filename);
	if (!file.is_open())
	{
		std::cerr << "ERROR: Could not open file data/" << filename << std::endl;
		return;
	}

	std::string line;
	int songsLoaded = 0;
	std::string segment;

	while (std::getline(file, line))
	{
		// Bỏ qua các dòng trống hoặc quá ngắn
		if (line.empty() || line.length() < 10)
			continue;

		std::stringstream ss(line);
		Song newSong;

		// Dùng '|' làm dấu phân cách
		try
		{
			// 1. ID
			if (!std::getline(ss, segment, '|'))
				continue;
			newSong.id = std::stoi(segment);

			// 2. Title
			if (!std::getline(ss, newSong.title, '|'))
				continue;

			// 3. Artist
			if (!std::getline(ss, newSong.artist, '|'))
				continue;

			// 4. Album
			if (!std::getline(ss, newSong.album, '|'))
				continue;

			// 5. Duration
			if (!std::getline(ss, segment, '|'))
				continue;
			newSong.duration = std::stoi(segment);
		}
		catch (const std::exception &e)
		{
			std::cerr << "[WARNING] Failed to parse line: " << line << " (Error: " << e.what() << ")" << std::endl;
			continue; // Bỏ qua dòng bị lỗi
		}

		library.addSong(newSong);
		songsLoaded++;
	}

	// Phải xây dựng các chỉ mục sau khi tải tất cả bài hát
	library.bulidIndexes();

	std::cout << "SUCCESS: Loaded " << songsLoaded << " songs from " << filename << " and built indexes." << std::endl;
}

