#include <audio/AudioSource.hpp>
#include <audio/AudioSystem.hpp>
#include <Application.hpp>

namespace H4_engine
{
	AudioSource::AudioSource(Entity *entity)
		: Component(entity) { }

	void AudioSource::start()
	{
		m_transform = m_entity->get_component<Transform>();
	}

	void AudioSource::tick()
	{
		if (m_transform && m_transform->get_position() != m_last_position)
        {
            glm::vec3 pos = m_transform->get_position();
            const FMOD_VECTOR fmod_pos{pos.x, pos.y, pos.z};
            FMOD_Channel_Set3DAttributes(m_channel, &fmod_pos, NULL);
            m_last_position = pos;
        }
	}

    void AudioSource::init(std::string path, bool is3D, bool isPaused, bool loop)
    {
        FMOD_SYSTEM *system = Application::get_instance()->get_audioSystem()->get_system();
        FMOD_RESULT result;
        result = FMOD_System_CreateSound(system, path.c_str(), (loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF) | (is3D ? FMOD_3D : FMOD_DEFAULT), NULL, &m_sound);
        if (result != FMOD_OK)
        {
            LOG_ERROR("FMOD error! {0}", FMOD_ErrorString(result));
            return;
        }
        result = FMOD_System_PlaySound(system, m_sound, NULL, isPaused, &m_channel);
        if (result != FMOD_OK)
        {
            LOG_ERROR("FMOD error! {0}", FMOD_ErrorString(result));
            return;
        }
    }
    
    void AudioSource::set_paused(bool paused)
    {
        FMOD_Channel_SetPaused(m_channel, paused);
    }

    void AudioSource::set_volume(float volume)
    {
        FMOD_Channel_SetVolume(m_channel, volume);
    }
}
