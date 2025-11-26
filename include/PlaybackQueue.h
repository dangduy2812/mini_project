#ifndef PLAYBACKQUEUE_H
#define PLAYBACKQUEUE_H

#include <list>
#include <unordered_map>
#include <stdexcept>
#include <iostream>
#include "Song.h"

class PlaybackQueue
{
private:
	std::list<Song> queue;
	std::unordered_map<int, std::list<Song>::iterator> songMap;
	std::list<Song>::iterator currentSong;

public:
	PlaybackQueue();

	void addSong(const Song &song);
	void removeSong(int songId);
	Song getCurrentSong() const;
	void playNextFinish();
	void displayQueue() const;

	//Hàm tiện ích để kiểm tra rỗng (Cần cho MusicPlayer::playNext)
	bool isEmpty() const { return queue.empty(); }

	// Hàm tiện ích để lấy kích thước (Cần cho MusicPlayer::generateSmartPlaylist - BFS)
	size_t getSize() const { return queue.size(); }

	// Trong PlaybackQueue.cpp:
	void addSongToFront(const Song &song);
};

#endif // PLAYBACKQUEUE_H