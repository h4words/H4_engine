#pragma once
#include <components/Transform.hpp>
#include <fmod.h>
#include <components/DataDesc.hpp>

namespace H4_engine
{
	class AudioSource : public Component
	{
		public:
			DECLARE_COMPONENT(AudioSource)
			DECLARE_DATADESC()
			AudioSource(Entity *entity);
			void start();
			void tick();
            void set_paused(bool paused);
			void set_volume(float volume);
		private:
            Transform *m_transform;
            FMOD_SOUND *m_sound = NULL;
			FMOD_CHANNEL *m_channel = NULL;
            glm::vec3 m_last_position;
			std::string m_audio_path;
			bool m_is3D;
			bool m_isPaused;
			bool m_isLooped;
	};
	REGISTER_COMPONENT(AudioSource);
}
