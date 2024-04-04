//
// Created by Andy on 4. 6. 2021.
//

#include "Position.h"

bool Position::operator==(const Position & sec) const{
    return (pos.first == sec.y() && pos.second == sec.x());
}

bool Position::operator!=(const Position & sec) const{
    return !(operator==(sec));
}

int Position::y() const{
    return pos.first;
}

int Position::x() const{
    return pos.second;
}