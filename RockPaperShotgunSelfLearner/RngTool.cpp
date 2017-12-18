#include "RngTool.h"

std::random_device rd;     // only used once to initialise (seed) engine
std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
//std::uniform_int_distribution<int> uni(0, 100); // guaranteed unbiased
int RngTool::GetRandomActionWithChance(RandomAction * rActions, int iSize, int max)
{
    std::uniform_int_distribution<int> uni(0, max); // guaranteed unbiased
    auto random_integer = uni(rng);
    auto iCurrentLapse = 0.0f;
    // Setting up real line number
    for (int i = 0; i < iSize; i++)
    {
        if (iCurrentLapse <= random_integer && random_integer <= (iCurrentLapse + rActions[i].iChance))
        {
            return i;
        }
        iCurrentLapse += rActions[i].iChance;

        
    }
    return -1;
}
