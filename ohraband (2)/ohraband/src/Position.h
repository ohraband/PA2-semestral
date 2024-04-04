//
// Created by Andy on 4. 6. 2021.
//

#ifndef SEMESTRAL_POSITION_H
#define SEMESTRAL_POSITION_H

#include <utility>
using namespace std;

/**
 * Structure handling coordinate positon.
 */
struct Position{
public:
    /**
     * Create a new position.
     * @param y - y coordinate
     * @param x - x coordinate
     */
    Position(int y, int x) : pos(y,x){
    }

    /**
     * Default destructor.
     */
    ~Position() = default;

    /**
     * Checks if two positions are equal.
     * @param second - second position
     * @return true if the two positions point to the same place, false otherwise.
     */
    bool operator==(const Position & second) const;

    /**
     * Checks if two positions are not equal.
     * @param second - second position
     * @return false if the two positions point to the same place, true otherwise.
     */
    bool operator!=(const Position & second) const;

    /**
     * @return y coordinate
     */
    int y() const;

    /**
     * @return x coordinate
     */
    int x() const;

private:
    // y,x positions
    pair<int, int> pos;
};

#endif //SEMESTRAL_POSITION_H