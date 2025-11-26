#include "MusicPlayer.h"
#include <iostream>
#include <queue>
#include <set>

using namespace Controller;

// chọn và phát bài theo id, nếu đang phát thì đẩy bài cũ vào lịch sử, đặt current và thêm vào queue
void MusicPlayer::selectAndPlaySong(int songID) {
    Song* p = library.findSongByID(songID);
    if (!p) {
        std::cout << "khong tim thay bai hat theo id\n";
        return;
    }

    if (current.id != 0 && state != STOPPED) {
        history.pushSong(current);
    }

    current = *p;
    state = PLAYING;

    queue.addSong(*p);

    std::cout << "dang phat " << current.title << "\n";
}

// tạo smart playlist bằng bfs đơn giản theo nghệ sĩ
// thuật toán
// dùng hàng đợi lưu các hạt giống để mở rộng
// dùng tập id đã thêm để tránh trùng
// hàng xóm của một bài là các bài cùng nghệ sĩ
PlaybackQueue MusicPlayer::generateSmartPlaylist(const Song& startSong, int maxSize) {
    PlaybackQueue out;

    std::queue<Song> q;
    std::set<int> seen;

    q.push(startSong);
    seen.insert(startSong.id);
    out.addSong(startSong);

    while (!q.empty() && static_cast<int>(out.getSize()) < maxSize) {
        Song cur = q.front(); q.pop();

        auto neighbors = library.findSongsByArtist(cur.artist);

        for (Song* nb : neighbors) {
            if (!nb) continue;
            if (static_cast<int>(out.getSize()) >= maxSize) break;

            if (!seen.count(nb->id)) {
                seen.insert(nb->id);
                out.addSong(*nb);
                q.push(*nb);
            }
        }
    }
    return out;
}

// chuyển đổi giữa phát và tạm dừng, nếu chưa có bài thì đưa về trạng thái dừng
void MusicPlayer::togglePlayPause() {
    if (current.id == 0) {
        state = STOPPED;
        std::cout << "chua chon bai de phat\n";
        return;
    }
    if (state == PLAYING) {
        state = PAUSED;
        std::cout << "tam dung " << current.title << "\n";
    } else {
        state = PLAYING;
        std::cout << "tiep tuc " << current.title << "\n";
    }
}

// dừng phát hoàn toàn
void MusicPlayer::stopPlayback() {
    state = STOPPED;
    std::cout << "da dung phat\n";
}

// phát bài trước đó nếu có lịch sử
void MusicPlayer::playPrevious() {
    if (history.isEmpty()) {
        std::cout << "lich su rong\n";
        return;
    }
    try {
        Song prev = history.playPreviousSong();
        current = prev;
        state = PLAYING;
        queue.addSongToFront(current);
        std::cout << "tro lai " << current.title << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << "loi " << e.what() << "\n";
        stopPlayback();
    }
}

// phát bài kế tiếp, ưu tiên hàng play next trước rồi mới tới hàng phát chính
void MusicPlayer::playNext() {
    if (!playNextQueue.isEmpty()) {
        if (current.id != 0 && state != STOPPED) history.pushSong(current);

        Song next = playNextQueue.dequeue();
        current = next;
        state = PLAYING;
        queue.addSongToFront(next);
        std::cout << "phat tu play next " << current.title << "\n";
        return;
    }

    if (queue.isEmpty()) {
        std::cout << "hang doi rong, dung phat\n";
        stopPlayback();
        return;
    }

    if (current.id != 0 && state != STOPPED) {
        history.pushSong(current);
    }

    queue.playNext();

    try {
        current = queue.getCurrentSong();
        state = PLAYING;
        std::cout << "phat tiep " << current.title << "\n";
    } catch (...) {
        current = {0, "", "", "", 0};
        stopPlayback();
        std::cout << "da het hang doi\n";
    }
}

// thêm một bài theo id vào hàng play next
void MusicPlayer::markPlayNext(int songID) {
    Song* s = library.findSongByID(songID);
    if (!s) {
        std::cout << "khong tim thay id de play next\n";
        return;
    }
    playNextQueue.enqueue(*s);
    std::cout << "da them vao play next " << s->title << "\n";
}

// bật chế độ xáo trộn từ một playlist
void MusicPlayer::startShuffle(const std::vector<Song>& playlist) {
    shuffleManager.setupShuffle(playlist);
    std::cout << "bat shuffle voi " << playlist.size() << " bai\n";
}

// lấy bài xáo trộn tiếp theo
Song MusicPlayer::playNextShuffled() {
    return shuffleManager.getNextShuffleSong();
}
