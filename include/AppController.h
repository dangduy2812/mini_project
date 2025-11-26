#pragma once
#include <string>
#include "MusicLibrary.h"
#include "PlaybackQueue.h"

// KHOI DIEU KHIEN UNG DUNG

// nạp dữ liệu từ file văn bản vào thư viện và xây chỉ mục
void loadLibraryFromSource(Model::MusicLibrary& library, const std::string& filename);

// hàm tự do đúng chữ ký đề bài để thêm album vào queue
void addAlbumToQueue(const std::string& albumName,
                     const Model::MusicLibrary& library,
                     PlaybackQueue& queue);
