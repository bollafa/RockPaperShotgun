#include "RngTool.h"
#include <iostream>
// dirty... i know.
enum Moves : unsigned char
{
    Stone = 0b001,
    Scissor = 0b010,
    Paper = 0b100
};
// return if lhs loses
bool inline LoseTest(Moves lhs, Moves rhs)
{
    /*if (lhs == Stone && rhs == Scissor)
        return false;
    if (lhs == Scissor && rhs == Stone)
        return true;*/
    if ((lhs ^ rhs) & Scissor && (lhs ^ rhs) & Stone)
        return lhs == Scissor;
    if ((lhs ^ rhs) & Paper && (lhs ^ rhs) & Scissor)
        return lhs == Paper;
    if ((lhs ^ rhs) & Stone && (lhs ^ rhs) & Paper)
        return lhs == Stone;
    /*if ((lhs ^ rhs) & (Scissor | Stone))
        return lhs == Scissor;
    if ((lhs ^ rhs) & (Paper | Scissor))
        return lhs == Paper;
    if ((lhs ^ rhs) & (Stone | Paper))
        return lhs == Stone;*/
    return (lhs ^ rhs);
}
int main()
{
    //  Setting up biased mofo
    RngTool::RandomAction BiasedActions[] = { {20},{10},{70} };
    int BiasedLog[] = {0,0,0};
    // Setting up unbiased dude, ( the learner ) 
    RngTool::RandomAction Learner[] = { { 30 },{ 30 },{ 30 } }; // yikes, what about the 1%?, set max as 90, et voila
    int LearnerLog[] = { 0,0,0 };
    for (int i = 0; i < 1000; i++)
    {
        BiasedLog[RngTool::GetRandomActionWithChance(BiasedActions, 3)]++;
        LearnerLog[RngTool::GetRandomActionWithChance(Learner, 3, 90)]++;
    }
    for (int i = 0; i < 3; i++)
    {
        std::cout << "Biased Chances: " << i << " " << ((float)BiasedLog[i] / 1000.0f)*100 << '\n';
        
    }
    for (int i = 0; i < 3; i++)
    {
        
        std::cout << "Learner Chances: " << i << " " << ((float)LearnerLog[i] / 1000.0f) * 100 << '\n';
    }
    Moves AllowedMoves[] = { Stone,Scissor,Paper };
    // Start playing:
    /*for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            
            std::cout << LoseTest(LetsPlay[i], LetsPlay[j]) <<" i "<< i << " j " << j << '\n';
        }
    }*/ // Testing game logic.

    constexpr const int NumberOfGames = 1000;
    for (int i = 0; i < NumberOfGames; i++)
    {
        using namespace RngTool;
        auto EnemyAction = GetRandomActionWithChance(BiasedActions, 3);
        auto LearnerAction = GetRandomActionWithChance(Learner, 3, 90);
        if (LearnerAction == -1)
        {
            std::cout << "FATAL ERROR";
        }
        if (LoseTest(AllowedMoves[LearnerAction], AllowedMoves[EnemyAction]))
        {
            // reduce chance of pickin' this action:
            
            Learner[LearnerAction].iChance *= 0.92f; // reduce by one?
            Learner[(LearnerAction + 1) % 3].iChance *= 1.04f; // gotta keep 90 as maximum.
            Learner[(LearnerAction + 2) % 3].iChance *= 1.04f; // gross module, i know.

        }
        else
        {
            // we didnt lose so do the crontary
            Learner[LearnerAction].iChance *= 1.02f; // reduce by one?
            Learner[(LearnerAction + 1) % 3].iChance *= 0.99f; // gotta keep 90 as maximum.
            Learner[(LearnerAction + 2) % 3].iChance *= 0.99f; // gross module, i know.
            // We reduce by the same amount as we increase, might be problematic.
        }
        // NEWNEWNEW
        for (int w = 0; w < 3; w++)
        {
            if (Learner[w].iChance > 75)
            {
                Learner[w].iChance = 75;
                Learner[(w + 1) % 3].iChance = 15 / 2;
                Learner[(w + 2) % 3].iChance *= 15 / 2;
            }
        }
        
        
        if (Learner[LearnerAction].iChance + Learner[(LearnerAction + 1) % 3].iChance + Learner[(LearnerAction + 2) % 3].iChance != 90)
            std::cout << "FATAL ERROR";
    }
   
    for (int i = 0; i < 3; i++)
    {

        std::cout << "Learner Chances: " << i << " " << (Learner[i].iChance) << '\n';
    }

    return 0;
}