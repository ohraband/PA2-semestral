#include <utility>

//
// Created by Andy on 9. 5. 2021.
//

#pragma once
using namespace std;

class CPlayer{
public:
    CPlayer(string name, string color): name(move(name)), color(move(color))
    {};


    virtual CAction MakeMove() const = 0;

private:
    string name;
    string color;

};
