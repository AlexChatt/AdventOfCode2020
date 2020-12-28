
#include "GameManager.h"

int main()
{
    GameManager MyGameManger;
    if (!MyGameManger.FillDecks("input.txt"))
    {
        return -1;
    }

    std::cout << "P1: Answer = " << MyGameManger.GetFinalPlayerScore() <<std::endl;
}