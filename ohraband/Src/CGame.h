//
// Created by Andy on 9. 5. 2021.
//
#include "CMap.h"
#include "CPlayer.h"
#pragma once

using namespace std;

class CGame{
public:
    CGame(string Loadgame);

    void ProcessTurn();

    void ShowHelp();

    bool SaveGame();

private:
    string SaveLocation;
    vector<CPlayer> Players;
    CMap currentMap;

};

