#include "IAgoraService.h"
#include "NGIAgoraRtcConnection.h"
#include "NGIAgoraAudioTrack.h"
#include "NGIAgoraLocalUser.h"
#include "NGIAgoraMediaNodeFactory.h"
#include "NGIAgoraMediaNode.h"
#include "NGIAgoraVideoTrack.h"
#include "AgoraBase.h"
#include <functional>

class PcmFrameObserver : public agora::media::IAudioFrameObserverBase
{
public:
    PcmFrameObserver(void *pvt) : pvt_(pvt) {
    };

    using CallbackFunc = std::function<void(void *pvt, const char*, agora::media::base::user_id_t, agora::media::IAudioFrameObserver::AudioFrame&)>;

    void setCallback(CallbackFunc callback) {
        callback_ = callback;
    }

    bool onPlaybackAudioFrame(const char* channelId, agora::media::IAudioFrameObserver::AudioFrame& audioFrame) override;    
    // bool onPlaybackAudioFrame(const char* channelId, agora::media::IAudioFrameObserver::AudioFrame& audioFrame) override{ 
    //     return true; 
    // };
    
    bool onRecordAudioFrame(const char* channelId, agora::media::IAudioFrameObserver::AudioFrame& audioFrame) override { 
        return true; 
    };
    // bool onRecordAudioFrame(const char* channelId, agora::media::IAudioFrameObserver::AudioFrame& audioFrame) override;
    
    bool onMixedAudioFrame(const char* channelId, agora::media::IAudioFrameObserver::AudioFrame& audioFrame) override{
        return true;
    };
    // bool onMixedAudioFrame(const char* channelId, agora::media::IAudioFrameObserver::AudioFrame& audioFrame) override;

    // bool onPlaybackAudioFrameBeforeMixing(const char* channelId, agora::media::base::user_id_t userId, agora::media::IAudioFrameObserver::AudioFrame& audioFrame) override;
    bool onPlaybackAudioFrameBeforeMixing(const char* channelId, agora::media::base::user_id_t userId, agora::media::IAudioFrameObserver::AudioFrame& audioFrame){
        return true;
    };

    int getObservedAudioFramePosition() override {
        return 0;
    };

    AudioParams getEarMonitoringAudioParams()override {
        return  AudioParams();
    };

    bool onEarMonitoringAudioFrame(agora::media::IAudioFrameObserver::AudioFrame& audioFrame) override {
        return true;
    };

    AudioParams getPlaybackAudioParams() override {
        return  AudioParams();
    };

    AudioParams getRecordAudioParams()  override {
        return  AudioParams();
    };

    AudioParams getMixedAudioParams() override {
        return  AudioParams();
    };

private:
    /* data */
    void *pvt_;
    CallbackFunc callback_;
};


