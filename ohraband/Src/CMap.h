//
// Created by Andy on 9. 5. 2021.
//
#include <vector>
#include "CSymbol.h"


#pragma once




class CMap{
public:
    CMap (size_t width, size_t height) : width(width), height(height)
    {};

    void DisplaySymbol(CSymbol symbol){};

    explicit CMap ( size_t height = 0, size_t width = 0, size_t mines = 0 );

    size_t GetHeight () const;

    size_t GetWidth () const;

    void ClearMap ();

private:
    size_t width;
    size_t height;
    vector<vector<CSymbol>> coordinates;
};
