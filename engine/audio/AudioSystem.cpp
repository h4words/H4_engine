#include <audio/AudioSystem.hpp>
#include <Log.hpp>

namespace H4_engine
{
    AudioSystem::AudioSystem()
    {
        FMOD_RESULT result;
        result = FMOD_System_Create(&m_system, FMOD_VERSION);
        if (result != FMOD_OK)
        {
            LOG_ERROR("FMOD Initialization error! {0}", FMOD_ErrorString(result));
            return;
        }

        result = FMOD_System_Init(m_system, 512, FMOD_INIT_NORMAL, 0);
        if (result != FMOD_OK)
        {
            LOG_ERROR("FMOD Initialization error! {0}", FMOD_ErrorString(result));
            return;
        }
        LOG_INFO("Audio System is initialized.");
    }
    
    void AudioSystem::set_master_volume(float volume)
    {
        FMOD_CHANNELGROUP *channel_group;
        FMOD_System_GetMasterChannelGroup(m_system, &channel_group);
        FMOD_ChannelGroup_SetVolume(channel_group, volume);
    }
}