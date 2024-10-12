#include <queue>
#include <mutex>
#include <condition_variable>
#include "IAgoraService.h"
#include "NGIAgoraRtcConnection.h"
#include "NGIAgoraAudioTrack.h"
#include "NGIAgoraLocalUser.h"
#include "NGIAgoraMediaNodeFactory.h"
#include "NGIAgoraMediaNode.h"
#include "NGIAgoraVideoTrack.h"
#include "AgoraBase.h"

#include <vector>
#include <mutex>
#include <condition_variable>
#include <atomic>

class AudioFrameQueue {
public:
    AudioFrameQueue(size_t capacity)
        : capacity_(capacity), write_index_(0), read_index_(0), size_(0) {
        // 预分配容量
        buffer_.reserve(capacity_);
    }

    void push(agora::media::IAudioFrameObserver::AudioFrame& audioFrame) {
        std::lock_guard<std::mutex> lock(mutex_);
        
        // 创建新的AudioFrame对象，并深拷贝内容
        agora::media::IAudioFrameObserver::AudioFrame newFrame;
        newFrame.buffer = new int16_t[audioFrame.samplesPerChannel * audioFrame.channels]; // 分配内存
        std::memcpy(newFrame.buffer, audioFrame.buffer, audioFrame.samplesPerChannel * audioFrame.channels * sizeof(int16_t)); // 深拷贝音频数据
        newFrame.samplesPerChannel = audioFrame.samplesPerChannel;
        newFrame.channels = audioFrame.channels;
        newFrame.samplesPerSec = audioFrame.samplesPerSec;
        
        buffer_[write_index_] = newFrame; // 写入当前音频帧
        write_index_ = (write_index_ + 1) % capacity_; // 更新写索引

        // 如果已满，更新读索引以覆盖旧数据
        if (size_ < capacity_) {
            size_++;
        } else {
            read_index_ = (read_index_ + 1) % capacity_; // 更新读索引
        }
    }

    bool pop(agora::media::IAudioFrameObserver::AudioFrame& audioFrame) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (size_ == 0) {
            return false; // 缓存为空
        }

    // 深拷贝buffer到audioFrame
        audioFrame.buffer = new int16_t[buffer_[read_index_].samplesPerChannel * buffer_[read_index_].channels];
        std::memcpy(audioFrame.buffer, buffer_[read_index_].buffer, buffer_[read_index_].samplesPerChannel * buffer_[read_index_].channels * sizeof(int16_t));

        audioFrame.samplesPerChannel = buffer_[read_index_].samplesPerChannel;
        audioFrame.channels = buffer_[read_index_].channels;
        audioFrame.samplesPerSec = buffer_[read_index_].samplesPerSec;

        // 释放旧的buffer
        delete[] buffer_[read_index_].buffer;
        buffer_[read_index_].buffer = nullptr; // 确保指针不再指向已释放的内存

        read_index_ = (read_index_ + 1) % capacity_; // 更新读索引
        size_--;
        return true;
    }

    size_t size() const {
        return size_;
    }

private:
    std::vector<agora::media::IAudioFrameObserver::AudioFrame> buffer_;
    size_t capacity_;
    mutable std::mutex mutex_;
    size_t write_index_;
    size_t read_index_;
    size_t size_;
};
