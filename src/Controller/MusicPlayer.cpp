#include "MusicPlayer.h"
#include <iostream>
#include <queue> // Cần cho thuật toán BFS
#include <set>	 // Cần cho thuật toán BFS

// P4.1: selectAndPlaySong
void Controller::MusicPlayer::selectAndPlaySong(int songID)
{
	Song *foundSongPtr = library.findSongByID(songID); // O(1) trung bình

	if (!foundSongPtr)
	{
		std::cerr << "ERROR: Song ID " << songID << " not found in library." << std::endl;
		return;
	}

	// 1. Nếu có bài hát đang phát, đẩy vào lịch sử
	if (currentPlayingSong.id != 0)
	{
		history.pushSong(currentPlayingSong); // O(1)
		std::cout << "[HISTORY] Pushed: " << currentPlayingSong.title << std::endl;
	}

	// 2. Cập nhật bài hát hiện tại
	currentPlayingSong = *foundSongPtr;
	playbackState = PLAYING; // Đảm bảo trạng thái là Playing
	std::cout << "[PLAYER] Now playing: " << currentPlayingSong.title << std::endl;
}

// Hàm khởi tạo Shuffle
void Controller::MusicPlayer::startShuffle(const std::vector<Song> &playlist)
{
	shuffleManager.setupShuffle(playlist);
	std::cout << "[SHUFFLE] Shuffle mode activated with " << playlist.size() << " songs." << std::endl;
}

// Phát bài hát Shuffle tiếp theo
Song Controller::MusicPlayer::playNextShuffled()
{
	return shuffleManager.getNextShuffleSong();
}

// Định nghĩa hàm setCurrentTrack()
void Controller::MusicPlayer::setCurrentTrack(const Song &song)
{
	currentPlayingSong = song;
}

// Định nghĩa hàm getCurrentTrack()
const Song& Controller::MusicPlayer::getCurrentTrack() const
{
	return currentPlayingSong;
}

// --- P4.2: Thuật toán Smart Playlist (BFS)  ---
PlaybackQueue Controller::MusicPlayer::generateSmartPlaylist(const Song &startSong, int maxSize)
{
	PlaybackQueue smartQueue;

	// 1. Cấu trúc dữ liệu cho BFS
	std::queue<Song> explorationQueue;
	std::set<int> addedSongIDs;

	// 2. Bắt đầu BFS
	explorationQueue.push(startSong);
	addedSongIDs.insert(startSong.id);
	smartQueue.addSong(startSong);

	std::cout << "--- Generating Smart Playlist (BFS) starting with " << startSong.title << " ---" << std::endl;

	while (!explorationQueue.empty() && smartQueue.getSize() < maxSize)
	{
		Song current = explorationQueue.front();
		explorationQueue.pop();

		// 3. Tìm Neighbors (Sử dụng chỉ mục Artist)
		std::vector<Song *> allNeighbors = library.findSongsByArtist(current.artist);

		for (Song *neighborPtr : allNeighbors)
		{
			if (smartQueue.getSize() >= maxSize)
				break;

			// 4. Kiểm tra trùng lặp bằng Set (O(log n))
			if (addedSongIDs.find(neighborPtr->id) == addedSongIDs.end())
			{

				// 5. Thêm vào Queue và Set
				addedSongIDs.insert(neighborPtr->id);
				smartQueue.addSong(*neighborPtr);
				explorationQueue.push(*neighborPtr);
				std::cout << " [BFS Added]: " << neighborPtr->title << std::endl;
			}
		}
	}
	std::cout << "--- Smart Playlist generated: " << smartQueue.getSize() << " songs ---" << std::endl;
	return smartQueue;
}

// Các hàm điều khiển khác
void Controller::MusicPlayer::togglePlayPause()
{
	if (currentPlayingSong.id == 0)
	{
		playbackState = STOPPED;
		std::cout << "[CONTROL] Cannot toggle state: No song selected." << std::endl;
		return;
	}

	if (playbackState == PLAYING)
	{
		playbackState = PAUSED;
		std::cout << "[CONTROL] Paused: " << currentPlayingSong.title << std::endl;
	}
	else
	{
		playbackState = PLAYING;
		std::cout << "[CONTROL] Playing: " << currentPlayingSong.title << std::endl;
	}
}

void Controller::MusicPlayer::stopPlayback()
{
	playbackState = STOPPED;
	std::cout << "[CONTROL] Stopped playback." << std::endl;
}

// P1.3: 
void Controller::MusicPlayer::addAlbumToQueue(const std::string &albumName)
{
	std::cout << "--- Adding Album '" << albumName << "' to Playback Queue ---" << std::endl;

	// Sử dụng findSongsByAlbum (O(1) trung bình) thay vì duyệt tuyến tính toàn bộ
	std::vector<Song *> albumSongs = library.findSongsByAlbum(albumName);

	if (!albumSongs.empty())
	{
		for (Song *songPtr : albumSongs)
		{
			queue.addSong(*songPtr);
			std::cout << " [ADDED]: " << songPtr->title << " by " << songPtr->artist << std::endl;
		}
		std::cout << "Successfully added " << albumSongs.size() << " songs." << std::endl;
		if (currentPlayingSong.id == 0 && playbackState == STOPPED && !queue.isEmpty())
		{
			std::cout << "[CONTROL] Queue populated. Auto-starting playback with the first song (A)..." << std::endl;

			// 1. Lấy Bài hát A từ Queue (KHÔNG XÓA)
			currentPlayingSong = queue.getCurrentSong();

			// 2. Cập nhật trạng thái
			playbackState = PLAYING;
			std::cout << "[CONTROL] Now playing: " << currentPlayingSong.title << std::endl;
		}
	}
	else
	{
		std::cout << "[INFO] Album '" << albumName << "' not found in library index." << std::endl;
	}
}

void Controller::MusicPlayer::playPrevious()
{
	if (history.isEmpty())
	{
		std::cout << "[HISTORY] History is empty. Cannot go back." << std::endl;
		return;
	}

	try
	{
		Song previousSong = history.playPreviousSong(); // O(1)
		currentPlayingSong = previousSong;
		playbackState = PLAYING;
		queue.addSongToFront(currentPlayingSong);
		std::cout << "[CONTROL] Previous song: " << currentPlayingSong.title << std::endl;
	}
	catch (const std::out_of_range &e)
	{
		std::cout << "[ERROR] " << e.what() << std::endl;
		stopPlayback();
	}
}

void Controller::MusicPlayer::playNext()
{
	if (queue.isEmpty())
	{
		std::cout << "[QUEUE] Queue is empty. Stopping." << std::endl;
		stopPlayback();
		return;
	}

	// 1. Đẩy bài hát hiện tại vào lịch sử

	if (currentPlayingSong.id != 0 && playbackState != STOPPED)
	{
		history.pushSong(currentPlayingSong);
		std::cout << "[HISTORY] Pushed to history: " << currentPlayingSong.title << std::endl;
	}

	// 2. Chuyển sang bài tiếp theo trong Queue
	queue.playNextFinish();

	// 3. Cập nhật trạng thái Player
	try // Xử lý trường hợp Queue rỗng sau khi Next
	{
		currentPlayingSong = queue.getCurrentSong();
		playbackState = PLAYING;
		std::cout << "[CONTROL] Next song: " << currentPlayingSong.title << std::endl;
	}
	catch (const std::out_of_range &e)
	{
		// Xử lý trường hợp Queue rỗng sau khi Next
		currentPlayingSong = {0, "", "", "", 0};
		stopPlayback();
		std::cout << "[QUEUE] Finished playback queue." << std::endl;
	}
}