#pragma once
#include "MusicLibrary.h"
#include "PlaybackQueue.h"
#include "PlaybackHistory.h"
#include "ShuffleManager.h"
#include "PlayNextQueue.h"

// KHOI TRINH PHAT

// lớp điều khiển phát nhạc, quản lý trạng thái, lịch sử, queue, play next, shuffle
namespace Controller {

enum PlaybackState { STOPPED = 0, PLAYING = 1, PAUSED = 2 };

class MusicPlayer {
private:
    Model::MusicLibrary& library;
    PlaybackQueue queue;
    PlaybackHistory history;
    ShuffleManager shuffleManager;
    PlayNextQueue playNextQueue;

    Song current{0, "", "", "", 0};
    PlaybackState state = STOPPED;

public:
    // khởi tạo với tham chiếu thư viện nhạc
    MusicPlayer(Model::MusicLibrary& lib) : library(lib) {}

    // chọn và phát bài theo id, đồng thời thêm vào queue
    void selectAndPlaySong(int songID);

    // tạo danh sách thông minh bằng bfs theo nghệ sĩ
    PlaybackQueue generateSmartPlaylist(const Song& startSong, int maxSize);

    // điều khiển phát tạm dừng
    void togglePlayPause();

    // dừng phát
    void stopPlayback();

    // phát bài trước đó theo lịch sử
    void playPrevious();

    // phát bài kế tiếp ưu tiên play next queue trước
    void playNext();

    // khởi động chế độ shuffle trên một playlist
    void startShuffle(const std::vector<Song>& playlist);

    // lấy bài shuffle kế tiếp
    Song playNextShuffled();

    // đánh dấu một id sẽ phát ngay khi bấm next
    void markPlayNext(int songID);

    // các getter tiện ích
    const Song& getCurrentTrack() const { return current; }
    PlaybackState getState() const { return state; }
    PlaybackQueue& getQueue() { return queue; }
    PlaybackHistory& getHistory() { return history; }
    Model::MusicLibrary& getLibrary() { return library; }
};

} // namespace Controller
