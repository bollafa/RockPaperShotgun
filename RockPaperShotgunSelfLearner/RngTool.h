#pragma once
#include <random>
namespace RngTool
{



    
    struct RandomAction
    {
        float iChance = 0;
        //void* Action;
    };
    // Chances have to sum up to 100!
    // Returns index
    // -1 if error occurred
    int GetRandomActionWithChance(RandomAction*,int, int = 100);
}