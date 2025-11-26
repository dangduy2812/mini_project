#include "MusicLibrary.h" // Bao gồm chính header của nó
#include <iostream>

void Model::MusicLibrary::addSong(const Song &song)
{
	allSongs.push_back(song);
}

void Model::MusicLibrary::bulidIndexes()
{
	// Logic P2: Xây dựng các chỉ mục
	songIndexByID.clear();
	songIndexByTitle.clear();
	artistIndex.clear();
	albumIndex.clear();

	// Lặp qua tất cả bài hát và thêm vào các map (chỉ mục)
	for (auto &song : allSongs)
	{
		songIndexByID[song.id] = &song;
		songIndexByTitle[song.title] = &song;
		artistIndex[song.artist].push_back(&song);
		albumIndex[song.album].push_back(&song);
	}
}

// Logic P2.1: O(1) trung bình
Song *Model::MusicLibrary::findSongByID(int id)
{
	auto it = songIndexByID.find(id);
	return (it != songIndexByID.end()) ? it->second : nullptr;
}

// Logic P2.2: O(log n)
Song *Model::MusicLibrary::findSongByTitle(const std::string &title)
{
	auto it = songIndexByTitle.find(title);
	return (it != songIndexByTitle.end()) ? it->second : nullptr;
}

// Logic P2.3: O(1) trung bình
std::vector<Song *> Model::MusicLibrary::findSongsByArtist(const std::string &artistName)
{
	auto it = artistIndex.find(artistName);
	return (it != artistIndex.end()) ? it->second : std::vector<Song *>{};
}
int Model::MusicLibrary::getSize()
{
	return allSongs.size();
}
//  O(1) trung bình - Sử dụng albumIndex
std::vector<Song *> Model::MusicLibrary::findSongsByAlbum(const std::string &albumName)
{
	auto it = albumIndex.find(albumName);
	return (it != albumIndex.end()) ? it->second : std::vector<Song *>{};
}