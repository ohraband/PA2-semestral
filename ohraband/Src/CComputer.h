//
// Created by Andy on 9. 5. 2021.
//
#include "CPlayer.h"
#pragma once

#include <vector>

class CComputer : public CPlayer{
public:
    CComputer(string name, int difficulty, string color ) : CPlayer(name, color), difficulty(difficulty)
    {};

    CAction MakeMove() const override
    {

        if (difficulty == 1)
            EasyDifficulty( vector<ExistingOutposts> )

        else if (difficulty == 2)
            MediumDifficulty( vector<ExistingOutposts> )

        else if (difficulty == 3)
            HardDifficulty( vector<ExistingOutposts> )


            ....

        return CAction(Outpost MyOutpost, Outpost TargetOutpost, int NumberOfForces, CMap CurrentMap )
    };

    Outpost EasyDifficulty(vector<ExistingOutposts>);

    Outpost MediumDifficulty(vector<ExistingOutposts>);

    Outpost HardDifficulty(vector<ExistingOutposts>);

private:
    int difficulty;
};
