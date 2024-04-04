//
// Created by Andy on 4. 6. 2021.
//

#ifndef SEMESTRAL_COBSTACLE_H
#define SEMESTRAL_COBSTACLE_H

#include "CViewableItem.h"

/**
 * Implementation of CViewableItem as an obstacle.
 */
class CObstacle : public CViewableItem {
public:
    /**
     * Create a new CObstacle object
     * @param pos - position
     * @param name - playername
     */
    CObstacle(Position pos, char name) : CViewableItem(pos, name){
    };

    /**
     * Default CObstacle destructor.
     */
    ~CObstacle() override = default;

    /**
     * Checks if position is walkable.
     * @return  false
     */
    bool Walkable() const override {
        return false;
    }

    /**
     * Shows an obstacle.
     * @param src - display screen
     */
    void Show(CScreen *src) const override {
        src->QuickShow(pos.y(),pos.x(),Playername(),5);
    }

private:
};

#endif //SEMESTRAL_COBSTACLE_H