#include "PcmFrameObserver.h"
#include "log.h"

bool PcmFrameObserver::onPlaybackAudioFrame(const char* channelId, AudioFrame& audioFrame) {
  // Write PCM samples
    AG_LOG(ERROR, "onPlaybackAudioFrame \n");

    if (callback_) {
        callback_(pvt_, channelId, 0, audioFrame);
    }
    return true;
}

// bool PcmFrameObserver::onPlaybackAudioFrameBeforeMixing(const char* channelId, agora::media::base::user_id_t userId, agora::media::IAudioFrameObserver::AudioFrame& audioFrame) {
//     // Write PCM samples
//     AG_LOG(ERROR, "onPlaybackAudioFrameBeforeMixing \n");
//     if (callback_) {
//         callback_(pvt_, channelId, userId, audioFrame);
//     }
//     return true;
// }

// bool PcmFrameObserver::onRecordAudioFrame(const char* channelId, agora::media::IAudioFrameObserver::AudioFrame& audioFrame) { 
    // AG_LOG(ERROR, "onRecordAudioFrame \n"); 
    // if (callback_) {
    //     callback_(pvt_, channelId, 0, audioFrame);
    // }  
    // return true; 
// };

// bool PcmFrameObserver::onMixedAudioFrame(const char* channelId, agora::media::IAudioFrameObserver::AudioFrame& audioFrame) {
//     AG_LOG(ERROR, "onMixedAudioFrame \n"); 
//     if (callback_) {
//         callback_(pvt_, channelId, 0, audioFrame);
//     }  
//     return true; 
// }
