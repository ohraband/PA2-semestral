//
// Created by Andy on 9. 5. 2021.
//
#include "CGame.h"
#pragma once

class CMainMenu{
public:
    CMainMenu()= default;

    void Start(){
        CGame(file savedGame);
    };

    void Wait(){};

    void Load(){};

    void Save(){};

    void Quit(){};
private:
    int playercount = 0 ;
};


