//
// Created by Andy on 9. 5. 2021.
//

#include "CSymbol.h"
#pragma once


class CRepresentative : public CSymbol{
public:

    CRepresentative( Outpost home, CPlayer MyPlayer );

    void Combat( CPerson OtherPerson );

    void Die();

    void Move(vector<pair<int,int>> path);

    void Show();

    bool Walkable() {
        return false;
    }

    string Type() {
        return "Representative";
    }


private:
    CPlayer MyPlayer;
    Outpost home;
    bool alive = true;
    int posx;
    int posy;
};
