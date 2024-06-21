#pragma once
#include <fmod.h>
#include <fmod_errors.h>
#include <fmod_common.h>
#include <cstddef>

namespace H4_engine {

    class AudioSystem
    {
        public:
            AudioSystem();
            FMOD_SYSTEM* get_system()
            {
                return m_system;
            }
            void set_master_volume(float volume);
        private:
            FMOD_SYSTEM *m_system;
    };
}
