#include "GameTime.h"

namespace UE
{
    GameTime::GameTime()
    {
        deltaTime = 0.0f;

        currentTime = timer.now();
        lastTime = currentTime;
    }

    void GameTime::CalculateDeltaTime()
    {
        currentTime = timer.now();

        deltaTime = std::chrono::duration_cast<ms>(currentTime - lastTime).count() / 1000;
        lastTime = currentTime;
    }

    float GameTime::GetDeltaTime()
    {
        return deltaTime;
    }
}


