#include "PlaybackQueue.h"

PlaybackQueue::PlaybackQueue() : currentSong(queue.end()) {}

void PlaybackQueue::addSong(const Song &song)
{
	queue.push_back(song);
	auto it = std::prev(queue.end());
	songMap[song.id] = it;

	if (queue.size() == 1)
	{
		currentSong = queue.begin();
	}
}

void PlaybackQueue::removeSong(int songId)
{
	auto found = songMap.find(songId);
	if (found == songMap.end())
		return;

	auto it = found->second;
	if (it == currentSong)
	{
		currentSong = queue.erase(it);
		if (currentSong == queue.end() && !queue.empty())
		{
			currentSong = queue.begin();
		}
	}
	else
	{
		queue.erase(it);
	}
	songMap.erase(found);
}

Song PlaybackQueue::getCurrentSong() const
{
	if (currentSong != queue.end() && !queue.empty())
	{
		return *currentSong;
	}
	throw std::out_of_range("No current song in the playback queue.");
}

void PlaybackQueue::playNextFinish()
{
	if (currentSong == queue.end() || queue.empty())
		return;

	songMap.erase(currentSong->id);
	currentSong = queue.erase(currentSong);

	if (currentSong == queue.end() && !queue.empty())
	{
		currentSong = queue.begin();
	}
}
void PlaybackQueue::addSongToFront(const Song &song)
{

	queue.push_front(song);


	currentSong = queue.begin();

	songMap[song.id] = currentSong;
}
void PlaybackQueue::displayQueue() const
{
	std::cout << "Playback Queue (" << queue.size() << " songs):" << std::endl;
	int index = 1;
	for (const auto &song : queue)
	{
		// So sánh địa chỉ để xác định bài hát hiện tại
		bool isCurrent = (currentSong != queue.end() && &song == &(*currentSong));
		std::cout << (isCurrent ? " -> " : "    ")
				  << index++ << ". " << song.title << " (" << song.artist << ")" << std::endl;
	}
}
