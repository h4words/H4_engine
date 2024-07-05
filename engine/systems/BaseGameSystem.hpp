#pragma once

namespace H4_engine
{
    class BaseGameSystem
    {
        public:
            BaseGameSystem();
            virtual void InitPreEntity();
            virtual void InitPostEntity();
            virtual void Tick();
            virtual void ShutdownPreEntity();
            virtual void ShutdownPostEntity();
    };
}