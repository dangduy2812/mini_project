#include "ShuffleManager.h"
#include <ctime>
#include <iostream>
#include <chrono>

void ShuffleManager::setupShuffle(const std::vector<Song> &playlist)
{
	originalPlaylist = playlist;
	shuffledList = playlist;
	playedSongIDs.clear();
	currentShuffleIndex = 0;

	// P3.3: Xáo trộn danh sách
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(shuffledList.begin(), shuffledList.end(), std::default_random_engine(seed));
}

Song ShuffleManager::getNextShuffleSong()
{
	if (shuffledList.empty())
	{
		throw std::out_of_range("Shuffle playlist is empty.");
	}

	// P3.3: Kiểm tra và lặp lại chu kỳ nếu cần
	if (playedSongIDs.size() == shuffledList.size())
	{
		playedSongIDs.clear();
		currentShuffleIndex = 0; // Bắt đầu lại chu kỳ
		std::cout << "[SHUFFLE]: Starting new shuffle cycle." << std::endl;
	}

	// Tìm bài hát tiếp theo chưa được chơi
	while (playedSongIDs.count(shuffledList[currentShuffleIndex].id))
	{
		currentShuffleIndex = (currentShuffleIndex + 1) % shuffledList.size();
	}

	Song nextSong = shuffledList[currentShuffleIndex];

	// P3.3: Chèn ID vào set (O(log n)
	playedSongIDs.insert(nextSong.id);

	// Chuyển sang index tiếp theo cho lần gọi sau
	currentShuffleIndex = (currentShuffleIndex + 1) % shuffledList.size();

	return nextSong;
}