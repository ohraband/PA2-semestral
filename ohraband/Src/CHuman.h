//
// Created by Andy on 9. 5. 2021.
//
#include "CPlayer.h"
#pragma once


class CHuman : public CPlayer{
public:

    CHuman(string name, int difficulty, string color ) : CPlayer(name, color), difficulty(difficulty)
    {};

    CAction MakeMove() const override{
        return CAction(Outpost MyOutpost, Outpost TargetOutpost, CMap CurrentMap );
    }


private:

};
