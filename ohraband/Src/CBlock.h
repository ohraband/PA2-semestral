//
// Created by Andy on 9. 5. 2021.
//
#include "CSymbol.h"
#pragma once

class CBlock : public CSymbol{
public:
     void Show() = 0;
     bool Walkable() {
        return false;
    }

    string Walkable() {
        return "Block";
    }


private:
};
