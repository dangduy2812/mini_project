#include "PlaybackHistory.h"
#include <iostream>
// P3.1: Lý do Stack là tối ưu: O(1) cho push/pop
void PlaybackHistory::pushSong(const Song &song)
{
	historyStack.push(song); // O(1)
}

Song PlaybackHistory::playPreviousSong()
{
	if (historyStack.empty())
	{
		throw std::out_of_range("Playback history is empty.");
	}

	Song previousSong = historyStack.top(); // O(1)
	
	historyStack.pop();						// O(1)

	return previousSong;
}
void PlaybackHistory::displayHistory() const
{
	std::cout << "\n--- Playback History (Back Stack, LIFO) ---" << std::endl;
	if (historyStack.empty())
	{
		std::cout << "History is currently empty." << std::endl;
		return;
	}

	// Sao chép stack để duyệt
	std::stack<Song> tempStack = historyStack;
	int index = tempStack.size();

	// Duyệt từ trên xuống (Mới nhất -> Cũ nhất)
	while (!tempStack.empty())
	{
		const Song &song = tempStack.top();
		std::cout << index-- << ". ID: " << song.id << ", Title: " << song.title << " (" << song.artist << ")" << std::endl;
		tempStack.pop();
	}
	std::cout << "------------------------------------------" << std::endl;
}