//
// Created by Andy on 9. 5. 2021.
//

#include "CSymbol.h"
#pragma once


class COutpost : public CSymbol{
public:
    COutpost(CPlayer player int posx, int posy) : player(player), NumberOfForces(NumberOfForces), posx(posx), posy(posy)
    {};

    CreateRepresentative(int NumberOfForces);

    GetPlayer() const {
        return player;
    }

    void Show() = 0;
    bool Walkable() {
        return false;
    }

    string Type() {
        return "Outpost";
    }


private:
    CPlayer player;
    int NumberOfForces;
    vector<CRepresentatives> representatives;
    int posx;
    int posy;
};