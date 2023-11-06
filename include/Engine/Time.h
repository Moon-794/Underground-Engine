#ifndef __TIME
#define __TIME

#include <memory>
#include <chrono>

namespace UE 
{
    class Time
    {
        public:
            Time();
            void StartTime();
            void StopTime();
            void CalculateDeltaTime();
            float GetDeltaTime();

        private:
            float deltaTime;

            std::chrono::high_resolution_clock::time_point lastTime;
            std::chrono::high_resolution_clock::time_point currentTime;

            using ms = std::chrono::duration<float, std::milli>;
            std::chrono::high_resolution_clock timer;
    };
};



#endif