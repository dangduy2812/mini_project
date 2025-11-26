#pragma once

#include "MusicLibrary.h"
#include "PlaybackQueue.h"
#include "PlaybackHistory.h"
#include "ShuffleManager.h"
namespace Controller
{
	enum PlaybackState
	{
		STOPPED = 0,
		PLAYING = 1,
		PAUSED = 2
	};

	class MusicPlayer
	{
	private:
		Model::MusicLibrary &library;
		PlaybackQueue queue;
		PlaybackHistory history;
		ShuffleManager shuffleManager;
		Song currentPlayingSong; // Bài hát đang phát (hoặc mới được chọn)
		PlaybackState playbackState;

	public:
		// P4.1: Phương thức chính để chọn và phát bài hát
		void selectAndPlaySong(int songID);

		// P4.2: Thuật toán Smart Playlist (BFS)
		PlaybackQueue generateSmartPlaylist(const Song &startSong, int maxSize);

		// Phương thức tiện ích
		void displayCurrentQueue() const { queue.displayQueue(); }

		// Giả định một hàm để khởi tạo chế độ shuffle
		void startShuffle(const std::vector<Song> &playlist);

		MusicPlayer(Model::MusicLibrary &lib)
			: library(lib),
			  playbackState(STOPPED),
			  currentPlayingSong({0, "", "", "", 0}) {}

		// GETTER

		PlaybackHistory &getHistory()
		{
			return history;
		}

		PlaybackQueue &getQueue()
		{
			return queue;
		}
		Song playNextShuffled();

		Model::MusicLibrary &getLibrary() { return library; }

		// BỔ SUNG: Getter cho bài hát hiện tại
		const Song &getCurrentTrack() const;

		// BỔ SUNG: Setter cho bài hát hiện tại (được gọi bởi selectAndPlaySong hoặc playNext)
		void setCurrentTrack(const Song &song);
		// BỔ SUNG: Phương thức chuyển đổi trạng thái phát
		void togglePlayPause();
		void stopPlayback();

		// Getter cho trạng thái
		PlaybackState getState() const { return playbackState; }

		void playPrevious();

		void addAlbumToQueue(const std::string &albumName);

		void playNext();
	};
}