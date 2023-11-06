#include "Engine/Time.h"

namespace UE
{
    Time::Time()
    {
        deltaTime = 0.0f;

        currentTime = timer.now();
        lastTime = currentTime;
    }

    void Time::CalculateDeltaTime()
    {
        currentTime = timer.now();

        deltaTime = std::chrono::duration_cast<ms>(currentTime - lastTime).count() / 1000;
        lastTime = currentTime;
    }

    float Time::GetDeltaTime()
    {
        return deltaTime;
    }
}


