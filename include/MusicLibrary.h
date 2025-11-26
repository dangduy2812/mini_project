#pragma once
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include "Song.h" 
namespace Model
{
	class MusicLibrary
	{
	public:
		// P1: Thư viện chính dùng std::vector (truy cập nhanh, ít thay đổi)
		std::vector<Song> allSongs;

		// P2.1: Chỉ mục theo ID dùng std::unordered_map (O(1) trung bình)
		std::unordered_map<int, Song *> songIndexByID;

		// P2.2: Chỉ mục theo Tiêu đề dùng std::map (O(log n), duy trì sắp xếp)
		std::map<std::string, Song *> songIndexByTitle;

		// P2.3: Chỉ mục theo Nghệ sĩ dùng std::unordered_map<string, vector<Song*>> (O(1) trung bình)
		std::unordered_map<std::string, std::vector<Song *>> artistIndex;

		// Bổ sung: Chỉ mục Album (Cần cho Smart Playlist BFS)
		std::unordered_map<std::string, std::vector<Song *>> albumIndex;

		// Phương thức thêm bài hát
		void addSong(const Song &song);

		// Phương thức xây dựng tất cả các chỉ mục
		void bulidIndexes();

		int getSize();
		// P2: Các phương thức tìm kiếm

		Song *findSongByID(int id);
		Song *findSongByTitle(const std::string &title);

		std::vector<Song *> findSongsByArtist(const std::string &artistName);
		std::vector<Song *> findSongsByAlbum(const std::string &albumName);
	};
}