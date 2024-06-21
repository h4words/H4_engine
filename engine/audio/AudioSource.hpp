#pragma once
#include <components/Transform.hpp>
#include <fmod.h>

namespace H4_engine
{
	class AudioSource : public Component
	{
		public:
			AudioSource(Entity *entity);
			void start();
			void tick();
            void init(std::string path, bool is3D = true, bool isPaused = true, bool loop = false);
            void set_paused(bool paused);
			void set_volume(float volume);
		private:
            Transform *m_transform;
            FMOD_SOUND *m_sound = NULL;
			FMOD_CHANNEL *m_channel = NULL;
            glm::vec3 m_last_position;
	};
	REGISTER_COMPONENT(AudioSource);
}
